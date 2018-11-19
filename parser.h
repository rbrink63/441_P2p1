#pragma once
#include <string>
#include <fstream>
#include "StringTable.h"
#include "tokStack.h"
#include "scanner.h"

using namespace std;
class parser {
public:
    void parse(string filename);
private:
    scanner my_scanner;
    StringTable my_string_table;
    tokStack my_token_stack;
};
