#pragma once

#include <Qsci/qsciscintilla.h>
#include <Qsci/qsciapis.h>
#include <Qsci/qscilexercustom.h>

#include "themes/tman.h"

namespace lc3kit::ide
{

    inline const QSet<QString> DIRECTIVES   = {"ORIG", "END", "FILL", "BLKW", "STRINGZ"};
    inline const QSet<QString> MNEMONICS    = {
        "ADD", "AND", "NOT",
        "BR", "BRN", "BRZ", "BRP", "BRNZ", "BRNP", "BRZP", "BRNZP",
        "LD", "LDI", "LDR", "LEA",
        "ST", "STI", "STR",
        "JMP", "JSR", "JSRR", "RET", "RTI", "TRAP",
        "GETC", "OUT", "PUTS", "IN", "PUTSP", "HALT",
        "SHL", "SHR", "MUL", "DIV"
    };
    inline const QSet<QString> TRAP_ALIASES = {"GETC","OUT","PUTS","IN","PUTSP","HALT"};
    inline const QSet<QString> REGISTERS = {"R0","R1","R2","R3","R4","R5","R6","R7","PC","PSR"};
    
    class AsmLexer : public QsciLexerCustom {
        Q_OBJECT

        public:
            // style indices
            enum Style {
                S_DEFAULT   = 0,
                S_COMMENT   = 1,
                S_MNEMONIC  = 2,
                S_DIRECTIVE = 3,
                S_REGISTER  = 4,
                S_LABEL     = 5,
                S_NUMBER    = 6,
                S_STRING    = 7,
                S_TRAP      = 8,   // trap aliases: HALT, GETC, PUTS...
            };

            explicit AsmLexer(QObject* parent = nullptr)
                : QsciLexerCustom(parent)
            {
                init_styles();
            }

            int autoIndentStyle() {
                return QsciScintilla::AiMaintain;
            }

            // NOTE: QsciLexer defines returns as this 
            const char* language() const { return "LC-3 ASM"; }

            QString description(int style) const {
                switch (style) {
                    case S_DEFAULT:   return "Default";
                    case S_COMMENT:   return "Comment";
                    case S_MNEMONIC:  return "Mnemonic";
                    case S_DIRECTIVE: return "Directive";
                    case S_REGISTER:  return "Register";
                    case S_LABEL:     return "Label";
                    case S_NUMBER:    return "Number";
                    case S_STRING:    return "String";
                    case S_TRAP:      return "Trap Alias";
                    default:          return "";
                }
            }

            // apply theme colors
            void load_theme() {
                setDefaultPaper(edpalette.editor_background);
                setDefaultColor(edpalette.editor_foreground);
                setColor(edpalette.editor_foreground, S_DEFAULT);
                
                set(S_DEFAULT,   edpalette.syntax_default_foreground, false, false);
                set(S_COMMENT,   edpalette.syntax_comment_foreground, false, edpalette.syntax_comment_italic);
                set(S_MNEMONIC,  edpalette.syntax_mnemonic_foreground, edpalette.syntax_mnemonic_bold,  false);
                set(S_DIRECTIVE, edpalette.syntax_directive_foreground, false, false);
                set(S_REGISTER,  edpalette.syntax_register_foreground, false, false);
                set(S_LABEL,     edpalette.syntax_label_foreground, false, false);
                set(S_NUMBER,    edpalette.syntax_number_foreground, false, false);
                set(S_STRING,    edpalette.syntax_string_foreground, false, false);
                set(S_TRAP,      edpalette.syntax_trap_foreground, edpalette.syntax_trap_bold,  false);

                setFont(QFont(edpalette.editor_font, edpalette.editor_font_size), S_DEFAULT);
            }

            void styleText(int start, int end) override {
                if (!editor()) return;
                char* buf = new char[end - start + 2];
                editor()->SendScintilla(QsciScintilla::SCI_GETTEXTRANGE, start, end, buf);
                QString text = QString::fromUtf8(buf, end - start);
                delete[] buf;

                startStyling(start);
                int pos = 0;

                while (pos < text.length()) {
                    QChar c = text[pos];

                    // comment
                    if (c == ';') {
                        int len = text.indexOf('\n', pos);
                        len = (len == -1 ? text.length() : len) - pos;
                        setStyling(len, S_COMMENT);
                        pos += len;
                        continue;
                    }

                    // string
                    if (c == '"') {
                        int end_q = text.indexOf('"', pos + 1);
                        int len   = (end_q == -1 ? text.length() : end_q + 1) - pos;
                        setStyling(len, S_STRING);
                        pos += len;
                        continue;
                    }

                    // whitespace
                    if (c.isSpace()) {
                        setStyling(1, S_DEFAULT);
                        pos++;
                        continue;
                    }

                    // comma
                    if (c == ',') {
                        setStyling(1, S_DEFAULT);
                        pos++;
                        continue;
                    }

                    // directive: starts with '.'
                    if (c == '.') {
                        int len = 1;
                        while (pos + len < text.length() && text[pos + len].isLetterOrNumber())
                            len++;
                        setStyling(len, S_DIRECTIVE);
                        pos += len;
                        continue;
                    }

                    // number: #N, xNN, bNN or bare digit
                    if (c == '#' || c == 'x' || c == 'X' || c == 'b' || c.isDigit()) {
                        int len = 1;
                        while (pos + len < text.length()
                            && (text[pos + len].isLetterOrNumber() || text[pos + len] == '-'))
                            len++;
                        setStyling(len, S_NUMBER);
                        pos += len;
                        continue;
                    }

                    // identifier: mnemonic, register, label, trap alias
                    if (c.isLetter() || c == '_') {
                        int len = 0;
                        while (pos + len < text.length()
                            && (text[pos + len].isLetterOrNumber() || text[pos + len] == '_'))
                            len++;

                        QString word = text.mid(pos, len).toUpper();

                        if (REGISTERS.contains(word))
                            setStyling(len, S_REGISTER);
                        else if (TRAP_ALIASES.contains(word))
                            setStyling(len, S_TRAP);
                        else if (MNEMONICS.contains(word))
                            setStyling(len, S_MNEMONIC);
                        else
                            setStyling(len, S_LABEL);  // user-defined label

                        pos += len;
                        continue;
                    }

                    setStyling(1, S_DEFAULT);
                    pos++;
                }
            }

        private:
            void set(int style, const QColor& color, bool bold = false, bool italic = false) {
                setColor(color, style);
                setFont(QFont(edpalette.editor_font, edpalette.editor_font_size, bold ? QFont::Bold : QFont::Normal, italic), style);
            }

            void init_styles() {
                load_theme();
            }
        };

    class TxtLexer : public QsciLexerCustom {
        Q_OBJECT
 
        public:
            enum Style {
                S_DEFAULT = 0,
            };
 
            explicit TxtLexer(QObject* parent = nullptr)
                : QsciLexerCustom(parent)
            {
                init_styles();
            }
 
            // NOTE: QsciLexer defines returns as this
            const char* language() const { return "Text"; }
 
            QString description(int style) const {
                switch (style) {
                    case S_DEFAULT: return "Default";
                    default:        return "";
                }
            }
            
            void styleText(int start, int end) override {
                if (!editor()) return;
                startStyling(start);
                setStyling(end - start, S_DEFAULT);
            }
 
        private:
            void init_styles() {
                setDefaultPaper(edpalette.editor_background);
                setDefaultColor(edpalette.editor_foreground);
                setColor(edpalette.editor_foreground, S_DEFAULT);
                setFont(QFont(edpalette.editor_font, edpalette.editor_font_size), S_DEFAULT);
            }
        };
 
} // namespace lc3kit::ide
