#ifndef MACHINE_H
#define MACHINE_H

#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>
#include <iostream>

enum Action
{
    LEFT,
    RIGHT,
    NONE,
    HALT
};

struct Command
{
    Command() = default;
    Command(wchar_t wch, Action act, wchar_t q)
        : _wch(wch), _act(act), _q(q) {}
    
    wchar_t _wch;
    Action _act;
    wchar_t _q;
};

class Machine
{
public:
    Machine() = default;
    std::wstring start();
    
    std::vector<wchar_t> alphabet;
    std::vector<wchar_t> states;
    std::wstring tape;
    std::wstring::iterator cursor;
    wchar_t state;
    std::vector<std::vector<Command>> table;
};

#endif // MACHINE_H
