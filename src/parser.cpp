#include "parser.h"

Action getAction(wchar_t wchact);

Machine* Parser::parse(std::vector<std::wstring> table)
{
    Machine* machine = new Machine();
    std::vector<std::vector<std::wstring>> csv_table(table.size());
    for (size_t i = 0; i < table.size(); i++)
    {
        std::wstring buffer = L"";
        for (size_t j = 0; j < table[i].length(); j++)
        {
            if (table[i][j] == L',')
            {
                csv_table[i].push_back(buffer);
                buffer = L"";
            }
            else if (table[i][j] != L' ') buffer += table[i][j];
        }
        csv_table[i].push_back(buffer);
    }
    
    for (size_t i = 3; i < csv_table[1].size(); i += 3)
    {
        if (std::find(machine->alphabet.begin(), machine->alphabet.end(), csv_table[1][i][0]) == machine->alphabet.end())
            machine->alphabet.push_back(csv_table[1][i][0]);
        else
        {
            std::wcout << L"Error: Alpha '" << csv_table[1][i][0] << L"' repeats multiple times" << std::endl;
            return nullptr;
        }
    }
    for (size_t i = 2; i < csv_table.size(); i++)
    {
        if (std::find(machine->states.begin(), machine->states.end(), csv_table[i][0][0]) == machine->states.end())
            machine->states.push_back(csv_table[i][0][0]);
        else
        {
            std::wcout << L"Error: State '" << csv_table[i][0][0] << L"' repeats multiple times" << std::endl;
            return nullptr;
        }
    }
    
    machine->tape = csv_table[0][0];
    if (csv_table[0][1] == L"L" || csv_table[0][1] == L"")
        machine->cursor = machine->tape.begin();
    else if (csv_table[0][1] == L"R")
        machine->cursor = machine->tape.end() - 1;
    else if (csv_table[0][1] == L"ML" && machine->tape.length() % 2 == 0)
        machine->cursor = machine->tape.end() - (machine->tape.length() / 2) - 1;
    else if (csv_table[0][1] == L"MR" && machine->tape.length() % 2 == 0)
        machine->cursor = machine->tape.end() - (machine->tape.length() / 2);
    else if ((csv_table[0][1] == L"ML" || csv_table[0][1] == L"MR") && machine->tape.length() % 2 != 0)
        machine->cursor = machine->tape.end() - (machine->tape.length() / 2) - 1;
    else
    {
        std::wcout << L"Error: No such cursor definition as '" << csv_table[0][1] << L"'" << std::endl;
        return nullptr;
    }
    
    machine->state = machine->states[0];
    for (size_t i = 0; i < csv_table.size() - 2; i++)
        machine->table.push_back(std::vector<Command>((csv_table[1].size() - 1) / 3));
        
    for (size_t i = 0; i < machine->table.size(); i++)
    {
        for (size_t j = 0; j < machine->table[i].size(); j++)
        {
            machine->table[i][j] = Command(csv_table[2 + i][1 + 3 * j][0],
                                           getAction(csv_table[2 + i][2 + 3 * j][0]),
                                           csv_table[2 + i][3 + 3 * j][0]);
        }
    }
    
    return machine;
}

Action getAction(wchar_t wchact)
{
    if (wchact == L'L')
        return Action::LEFT;
    else if (wchact == L'R')
        return Action::RIGHT;
    else if (wchact == L'H')
        return Action::HALT;
    return Action::NONE;
}
