#include "loader.h"
#include <string>
#include <iostream>
#include <fstream>

Loader::Loader(uint8_t* memory_ptr, uint32_t memory_size) {
    this->memory_ptr = memory_ptr;
    this->memory_size = memory_size;
}

bool Loader::memoryWrite(std::string file_name, uint32_t address) {
    std::cout  << "lendo o arquivo" << std::endl;
    std::ifstream program_file;
    std::string line;
    program_file.open (file_name, std::ios::in);
    int counter = 0;
    int byte1, byte2;
    while (getline(program_file,line)) {
        // Output the text from the file
        std::cout << "linha " << counter++ <<": " << line << std::endl;
        //std::cout << line[10] << std::endl;

        std::cout<< std::endl;
        if  (line.substr(0, 4) != "1101") {
            byte1 = stoi(line.substr(0, 8), nullptr, 2);
            byte2 = stoi(line.substr(8, 16), nullptr, 2);
            this->memoryWriteByte(address++, byte1);
            this->memoryWriteByte(address++, byte2);
        } else {
            byte1 = stoi(line.substr(0, 8), nullptr, 2);
            this->memoryWriteByte(address++, byte1);
        }
    }

    std::cout << std::endl << "fim de leitura" << std::endl;
    program_file.close();

    return true;
}

bool Loader::memoryWriteByte(uint32_t address, uint8_t value) {
    if (address > this->memory_size) {
        std::cout << "ERROR: out of memory bounds";
        return false;
    }
    
    this->memory_ptr[address] = value;
    return true;
}

