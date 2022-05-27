#include "eventManager.h"
#include <iostream>

const char EventManager::dumper = 'd';
const char EventManager::end = 'q';
const char EventManager::loader = 'l';

EventManager::EventManager() {
}

char EventManager::getEvent() {
    char event;
    std::cin >> event;
    return event;
}

bool EventManager::treatEvent(char event) {
    switch (event) {
        case dumper: {
            std::cout << "chamando o dumper" << std::endl;
            this->dump.readMemory(4, 0xBE);
            return true;
            break;
        }

        case end: {
            std::cout << "desligando" << std::endl;
            return false;
            break;
        }

        case loader: {
            load.getDataFromUser();
            load.memoryWrite();
            break;
        }

        default:
            std::cout << "evento não programado" <<std::endl;
            return true;
    } 
}