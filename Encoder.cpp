#include <filesystem>
#include <iostream>
#include <fstream>

namespace fs = std::filesystem;

int main() {
    std::string Res;
    std::cout << "Please provide the file name that contains the message: ";
    std::getline(std::cin, Res, '\n');
    std::ifstream ifs(Res, std::fstream::binary);

    if(!ifs.is_open()) {
        std::cout << "Failed to open \"" << Res << "\"!\n";
        return 1;
    }

    auto Size = fs::file_size(Res);
    std::string secret(Size, 0);
    ifs.read(&secret[0], Size);
    ifs.close();


    std::cout << "Please provide the file name to encode: ";
    std::getline(std::cin, Res, '\n');


    ifs.open(Res, std::fstream::binary);

    if(!ifs.is_open()) {
        std::cout << "Failed to open \"" << Res << "\"!\n";
        return 1;
    }

    Size = fs::file_size(Res);
    std::string File(Size, 0);
    ifs.read(&File[0], Size);
    ifs.close();

    File += '\n';
    for(char c : secret) {
        for (int BitPos = 6; BitPos >= 0; BitPos--) {
            if (char(c >> (BitPos)) & 1) {
                File += ' ';
            } else File += '\t';
        }
    }

    std::cout << "Please provide the output file name: ";
    std::getline(std::cin, Res, '\n');

    std::ofstream ofs(Res, std::fstream::binary);
    if(!ofs.is_open()) {
        std::cout << "Failed to open \"" << Res << "\"!\n";
        return 1;
    }

    ofs << File;
    ofs.close();
    std::cout << "Encoded!\n";
    return 0;
}
