#pragma once

#include <QByteArray>
#include <variant>

#include <lc3kit/asm>

namespace lc3kit::ide {
    // forward declare to break the cycle
    class TextEditor;

    struct qassemble_item {
        TextEditor*   editor   = nullptr;
        bool          run      = false;
        bool          is_debug = false;
        bool          fresh    = false;
        bool          ext      = settings.get_bool(EXT_ENABLED);
    };

    struct qasm_obj {
        lasm::sections_t    sections;
        lasm::sym_table_t   symtab;
        lasm::lines_addrs_t linesaddrs;
    };

    // NOTE: not using QVariant, cuz errors_t is not a Qt object.
    using qasm_result_t = std::variant<qasm_obj, lasm::errors_t>;

    struct qasm_ctx {
        qassemble_item src;
        qasm_result_t  result;

        qasm_ctx(qassemble_item s, qasm_obj obj) : src(s), result(std::move(obj)) {}
        qasm_ctx(qassemble_item s, lasm::errors_t errors) : src(s), result(std::move(errors)) {}

        bool ok()     const { return std::holds_alternative<qasm_obj>(result); }
        bool failed() const { return std::holds_alternative<lasm::errors_t>(result); }

        qasm_obj&        obj()    { return std::get<qasm_obj>(result); }
        lasm::errors_t&  errors() { return std::get<lasm::errors_t>(result); }
    };

} // namespace lc3kit::ide
