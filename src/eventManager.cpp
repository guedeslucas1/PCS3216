#include "eventManager.h"
#include <iostream>

EventManager::EventManager() {

}

char EventManager::getEvent() {
    char a;
    std::cin >> a;
    return a;
}
