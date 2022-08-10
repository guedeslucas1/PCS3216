#include "dumper.h"
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>  
#include <iomanip>

void print_format_int(int value, int n_of_chars) {
    std::cout << "0x" << std::hex << value;

    int n_digits = (value > 15)? 3 : 2; 

    for (int i = n_digits; i < n_of_chars - 1; i++)
        std::cout << " " ;
}

Dumper::Dumper(uint8_t* memory_ptr, uint32_t memory_size) {
    this->memory_ptr = memory_ptr;
    this->memory_size = memory_size;
}

bool Dumper::readMemory(int initialAddress, int finalAddress) {

    std::cout << " ";
    for (int i  = 0; i < 17*6+1+1; i++) {
        std::cout << "_";
    }
    std::cout << " " << std::endl;

    std::cout << "|";

    std::cout << " ADDR ";
    std::cout << "|";

    for (int i  = 0; i < (17*6+1-2 - 39)/2; i++) {
        std::cout << " ";
    }


    std::cout << "LEITURA DA MEMÓRIA DE ";
    print_format_int(initialAddress, 4);
    std::cout << " ATÉ ";
    print_format_int(finalAddress, 4);

    for (int i  = 0; i < (17*6+1-2 - 39)/2; i++) {
        std::cout << " ";
    }
    


    std::cout << "|" << std::endl;
    
    std::cout << "|";

    for (int i  = 0; i < 6; i++) {
        std::cout << "_";
    }

    std::cout << "|";

    for (int i  = 0; i < 17*6+1+2 - 8; i++) {
        std::cout << "_";
    }
    std::cout << "|" << std::endl;

    int init_byte_line = initialAddress - initialAddress%16;
    
    for (int byte_line = init_byte_line; byte_line < finalAddress; byte_line += 16) {    
        std::cout << "|";
        print_format_int(byte_line, 6);
        std::cout << "| ";

        for (int byte = 0; byte < 16; byte++) {
            if (byte_line + byte < finalAddress && byte_line+byte >= initialAddress) {
                //std::cout << (int)this->memory_ptr[byte_line + byte] << "  ";
                print_format_int((int)this->memory_ptr[byte_line + byte], 6);
            } else {
                std::cout << "      ";
            }
        }
        std::cout << "|" <<     std::endl;
    }

    std::cout << "|";
    for (int i  = 0; i < 17*6+1+1; i++) {
        std::cout << "_";
    }
    std::cout << "|" << std::endl << std::endl;

    return true;
}