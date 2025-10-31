#include "machine.h"

std::wstring Machine::start()
{
    while(true)
    {
        size_t i;
        for (i = 0; i < this->states.size(); i++)
        {
            if (this->states[i] == this->state) break;
        }
        if (i == this->states.size())
        {
            std::wcout << L"Error: No such state as '" << this->state << L"'" << std::endl;
            return L",,,";
        }
        
        size_t j;
        for (j = 0; j < this->alphabet.size(); j++)
        {
            if (this->alphabet[j] == *this->cursor) break;
        }
        if (j == this->alphabet.size())
        {
            std::wcout << L"Error: No such alpha as '" << *this->cursor << L"'" << std::endl;
            return L",,,";
        }
        
        const Command* cmd = &this->table[i][j];
        if (cmd->_wch != L'\0')
        {
            if (std::find(this->alphabet.begin(), this->alphabet.end(), cmd->_wch) != this->alphabet.end())
                *this->cursor = cmd->_wch;
            else
            {
                std::wcout << L"Error: No such alpha as '" << cmd->_wch << L"'" << std::endl;
                return L",,,";
            }
        }
        
        switch (cmd->_act)
        {
        case Action::LEFT:
            if (this->cursor != this->tape.cbegin()) this->cursor--;
            else
            {
                this->tape = this->alphabet[0] + this->tape;
                this->cursor = this->tape.begin();
            }
            break;
        case Action::RIGHT:
            if (this->cursor != this->tape.cend() - 1) this->cursor++;
            else
            {
                this->tape += this->alphabet[0];
                this->cursor = this->tape.end() - 1;
            }
            break;
        case Action::HALT:
            return this->tape;
        default:
            break;
        }
        
        if (cmd->_q != L'\0')
        {
            if (std::find(this->states.begin(), this->states.end(), cmd->_q) != this->states.end())
                this->state = cmd->_q;
            else
            {
                std::wcout << L"Error: No such state as '" << cmd->_q << L"'" << std::endl;
                return L",,,";
            }
        }
    }
    
    return this->tape;
}
