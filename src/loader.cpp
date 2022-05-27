#include "loader.h"
#include <string>
#include <iostream>
#include <fstream>

Loader::Loader() {
    
}

void Loader::memoryWrite() {
    std::ofstream memory_file;
    // TODO - o resto kk
}

void Loader::getDataFromUser() {
    std::cout << "Digite o endereço inicial: (na forma 0x...): ";
    std::cin >> this->initial_address;

    std::cout << "Digite os valores dos bytes para serem escritos na memória" << std::endl;
    std::cout << "Quando acabar, digite 'k'";
    
    int index = 0;
    std::string input;
    std::cin >> input;
    while(input != "k") {
        this->data_buffer[index++] = (uint8_t)(stoi(input));
        std::cin >> input;
    }

    this->data_lenght = index;
}
