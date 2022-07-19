#include <iostream>
#include "eventManager.h"

int main() {
    std::cout << "=== Inicio da simulação ===" << std::endl << std::endl;
    EventManager::events_t evento;
    EventManager evMng;
    
    do  {
        evento = evMng.getEvent();
    } while(evMng.treatEvent(evento)) ;

    return 0;
}
