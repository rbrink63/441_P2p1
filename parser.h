#pragma once
#include <string>
#include <fstream>
#include "StringTable.h"
#include "tokStack.h"
#include "scanner.h"
#include "grammar.h"

using namespace std;
class parser {
public:
    void parse(string filename);
private:
    int chooseProd(token topToken, token inputToken);
    void pushRHS(int prod_index);
    bool get_parser_err();
    void set_parser_err(bool err);
    scanner my_scanner;
    StringTable my_string_table;
    tokStack my_token_stack;
    bool parser_err = false;
    bool foundLHS = true;
};
