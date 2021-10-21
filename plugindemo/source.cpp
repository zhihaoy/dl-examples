#include "openplugins.h"

#include <iostream>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "example: list-python-by-version.exe 3.7\n";
        return 2;
    }

    try
    {
        bool nonempty = false;
        for (auto &plugin : plugindemo::openplugins(std::filesystem::current_path()))
        {
            if (auto python = plugin->lookup(argv[1]))
            {
                if (nonempty)
                    std::cout << std::endl;
                std::cout << python->executable() << '\n';
                std::cout << python->windowed_executable() << '\n';
                nonempty = true;
            }
        }
        if (!nonempty)
        {
            std::cerr << "Nothing found\n";
            return 1;
        }
    }
    catch (std::exception &exc)
    {
        std::cerr << "ERROR: " << exc.what() << '\n';
        return 1;
    }
}