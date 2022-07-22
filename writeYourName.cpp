/*
writeYourName.cpp v 2.0
This will write the name and the student details to all the files that you specify
usage:
put the details you want to write on writeYourName.txt
compile writeYourName.cpp -std=c++17 -o out
./out *.cpp *.h
-r after all the file names will remove the comments instead of adding them,
it assumes that there are only one comment of name btw and the comment type is the backslash - star style one
another assumption is that the comment will start at first line.. I don't
bother to correct this because this is just a simple utility.

*/
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

int main(int argc, const char *argv[])
{
    std::stringstream file1_content;
    std::ifstream file("writeYourName.txt");
    file1_content << file.rdbuf();
    bool remove_file = false;
    if (std::string(argv[argc - 1]) == "-r")
    {
        remove_file = true;
    }

    for (int i = 1; i < argc - 1; i++)
    {
        if (std::string(argv[i]).find("test") != std::string::npos || std::string(argv[i]).find("Test") != std::string::npos || std::string(argv[i]).find("writeYour") != std::string::npos || std::string(argv[i]).find(".out") != std::string::npos)
        {
            continue;
        }

        std::stringstream file2_content;
        std::fstream file2;
        file2.open(argv[i], std::ios::in | std::ios::out);
        file2_content << file2.rdbuf();
        file2.close();
        file2.open(argv[i], std::ios::out | std::ios::trunc);

        std::string file2_content_str = file2_content.str();
        if (file2_content_str.substr(0, 2) == "/*")
        {
            file2_content_str.erase(0, file2_content_str.find("*/") + 2);
        }

        if (!remove_file)
        {
            file2 << file1_content.str();
            file2 << std::endl
                  << std::endl;
        }
        //! TODO : something wrong below fix it
        // file2_content_str.erase(0, file2_content_str.find_first_not_of(" \t\n\r\f\v") - 1);
        file2 << file2_content_str;
    }
}
