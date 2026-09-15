#pragma once

#include <QColor>
#include <QString>

namespace lc3kit::ide
{
    typedef struct TextEditorPalette {
        QColor  editor_background;
        QColor  editor_foreground;
        QString editor_font;
        uint    editor_font_size;

        QColor margin_background;
        QColor margin_foreground;

        QColor caret_foreground;
        QColor caret_line_background;
        
        QColor selection_background;

        QColor indentation_guides_foreground;

        QColor matched_brace_foreground;
        QColor matched_brace_background;

        QColor marker_pc_foreground;
        QColor marker_pc_background;

        QColor marker_breakpoint_foreground;
        QColor marker_breakpoint_background;
        
        QColor marker_error_background;
        
        QColor indicator_search_foreground;
        QColor indicator_pc_foreground;
        
        QColor syntax_default_foreground;
        QColor syntax_comment_foreground;
        QColor syntax_mnemonic_foreground;
        QColor syntax_directive_foreground;
        QColor syntax_register_foreground;
        QColor syntax_label_foreground;
        QColor syntax_number_foreground;
        QColor syntax_string_foreground;
        QColor syntax_trap_foreground;
        
        bool syntax_mnemonic_bold;
        bool syntax_comment_italic;
        bool syntax_trap_bold;
    } qte_palette;

    typedef struct QSSPalette {
        QColor bg_0;
        QColor bg_1;
        QColor bg_2;
        QColor bg_3;
        QColor bg_inset;

        QColor border_soft;

        QColor text_0;
        QColor text_1;
        QColor text_2;

        QColor accent_soft;
        QColor accent_hi;
        QColor accent_text;

        QColor border;
        QColor accent;

        QColor ok;
        QColor warn;
        QColor danger;
        QColor violet;
    } qss_palette;
} // namespace lc3kit::ide
