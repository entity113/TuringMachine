#ifndef PARSER_H
#define PARSER_H

#include "machine.h"

class Parser
{
public:
    Parser() = delete;
    Parser(const Parser&) = delete;
    Parser(Parser&&) = delete;
    Parser& operator=(const Parser&) = delete;
    Parser& operator=(Parser&&) = delete;
    ~Parser() = delete;
    
    static Machine* parse(std::vector<std::wstring> table);
};

#endif // PARSER_H
