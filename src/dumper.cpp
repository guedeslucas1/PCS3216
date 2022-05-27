#include "dumper.h"
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>  
#include <iomanip>

Dumper::Dumper() {

}

void Dumper::readMemory(int initialAddress, int finalAddress) {
    std::ifstream memoryFile;
    std::string line;
    memoryFile.open ("../mem/memory.txt", std::ios::in);

    int currentReadingLine = 0;

    /** PRINTANDO A TABELA DE MEMÓRIA **/
    while (memoryFile.is_open() && getline(memoryFile,line) && currentReadingLine <= finalAddress) {

        // endereços (hexadecimais) a esquerda
        std::cout << "0x" << std::hex << currentReadingLine;

        int n_digits = (int)(log(currentReadingLine+1)/log(16)); // calculando o número de digitos do endereço e adicionando espaços se necessário, pra deixar alinhada
        for (int i = n_digits; i < 3; i++)
            std::cout << " " ;
        std::cout << ":";

        // valores a direita
        for (int i = 0; i < 16; i++)
            std::cout << ((currentReadingLine + i >= initialAddress && currentReadingLine + i <= finalAddress) ? line.substr(3*i, 3) : "   ");
        std::cout << std::endl;

        currentReadingLine += 16;
    }

    memoryFile.close();
}