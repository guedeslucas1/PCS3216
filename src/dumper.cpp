#include "dumper.h"
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>  
#include <iomanip>

void print_format_int(int value, int n_of_chars) {
    std::cout << "0x" << std::hex << value;
    int n_digits = (int)(log(value+1)/log(16)) + 2;
    if (value == 255) {
        n_digits--;
    }
    for (int i = n_digits; i < n_of_chars - 1; i++)
        std::cout << " " ;
}

Dumper::Dumper(uint8_t* memory_ptr, uint32_t memory_size) {
    this->memory_ptr = memory_ptr;
    this->memory_size = memory_size;
}

bool Dumper::readMemory(int initialAddress, int finalAddress) {
    std::cout << std::endl << "--- LEITURA DA MEMÓRIA DE 0x" << std::hex << initialAddress << " ATÉ 0x" << std::hex << finalAddress << " ---" << std::endl;

    for (int byte_line = 0; byte_line < finalAddress; byte_line += 16) {    
        print_format_int(byte_line, 6);
        std::cout << ": ";

        for (int byte = 0; byte < 16; byte++) {
            if (byte_line + byte < finalAddress && byte_line+byte >= initialAddress) {
                //std::cout << (int)this->memory_ptr[byte_line + byte] << "  ";
                print_format_int((int)this->memory_ptr[byte_line + byte], 6);
            } else {
                std::cout << "     ";
            }
        }
        std::cout << std::endl;
    }

    return true;
}