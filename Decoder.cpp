#include <filesystem>
#include <iostream>
#include <fstream>

namespace fs = std::filesystem;

int main() {
    std::string Res;
    std::cout << "Please provide the file name that is encoded: ";
    std::getline(std::cin, Res, '\n');

    std::ifstream ifs(Res, std::fstream::binary);

    if(!ifs.is_open()) {
        std::cout << "Failed to open \"" << Res << "\"!\n";
        return 1;
    }

    auto Size = fs::file_size(Res);
    std::string File(Size, 0);
    ifs.read(&File[0], Size);
    ifs.close();

    std::string Encoded;

    if(auto it = File.rfind('\n'); it == std::string::npos || (File.at(it+1) != '\t' && File.at(it+1) != ' ')) {
        std::cout << "this file doesn't seem to contain anything...\n";
        return 1;
    } else {
        Encoded = File.substr(it+1);
    }
    std::cout << "Result: \"";
    char ch = 0;
    int BitPos = 0;
    for(char c : Encoded) {
        if (c == ' ')ch |= 1;
        BitPos++;
        if(BitPos == 7) {
            std::cout << ch;
            BitPos = 0;
            ch = 0;
        } else {
            ch = char(ch << 1);
        }
    }
    std::cout << "\"\n";
    return 0;
}
