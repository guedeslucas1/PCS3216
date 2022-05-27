#include <iostream>
#include "eventManager.h"

int main() {
    std::cout << "estou simulando um computador uhul" << std::endl;
    
    char evento;
    EventManager evMng;

    do  {
        evento = evMng.getEvent();
        std::cout << "evento: " << evento << std::endl;
    } while(evMng.treatEvent(evento)) ;
    return 0;
}
