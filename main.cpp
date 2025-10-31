#include <fstream>
#include <iterator>

#include "parser.h"

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "");
    
    std::wifstream file;
    if (argc > 1)
    {
        file.open(argv[1]);
    }
    else
    {
        std::wcout << "Error: Configuration file is not specified" << std::endl;
        return -1;
    }
    
    std::vector<std::wstring> table;
    if (file.is_open())
    {
        file.imbue(std::locale(""));
        
        table = std::vector<std::wstring>(
            std::istream_iterator<std::wstring, wchar_t>(file),
            std::istream_iterator<std::wstring, wchar_t>()
        );
        file.close();
    }
    
    Machine* machine = Parser::parse(table);
    if (machine == nullptr) return -1;
    std::wstring output = machine->start();
    if (output == L",,,") return -1;
    std::wcout << output << std::endl;
    
    delete machine;    
    return 0;
}
