#include "compiler_spec_helper.h"
#include <fstream>

static string src_dir() {
    const char * dir = getenv("TREESITTER_DIR");
    if (!dir) dir = getenv("PWD");
    return dir;
}

namespace tree_sitter_examples {
    extern const Grammar arithmetic;
    extern const Grammar javascript;
    extern const Grammar json;
    extern const Grammar golang;
}

START_TEST

describe("compiling the example grammars", []() {
    string example_parser_dir = src_dir() + "/examples/parsers/";

    auto compile_grammar = [&](const Grammar &grammar, string language) {
        it(("compiles the " + language + " grammar").c_str(), [&]() {
            ofstream file(example_parser_dir + language + ".c");
            file << compile(grammar, language);
            file.close();
        });
    };

    compile_grammar(tree_sitter_examples::arithmetic, "arithmetic");
    compile_grammar(tree_sitter_examples::json, "json");
    compile_grammar(tree_sitter_examples::javascript, "javascript");
    compile_grammar(tree_sitter_examples::golang, "golang");
});

END_TEST