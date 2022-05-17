#include <iostream>
#include "eventManager.h"

int main() {
    std::cout << "estou simulando um computador uhul" << std::endl;

    EventManager evMng;

    while (1) {
        char evento = evMng.getEvent();
        std::cout << "evento: " << evento << std::endl;
        
        if (evento == 'a') {
            std::cout << " desligando" << std::endl;
            break;
        }
        
    }
    return 0;
}
