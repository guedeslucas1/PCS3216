#include "eventManager.h"
#include <iostream>

const std::string EventManager::dumper_str      = "DMP";
const std::string EventManager::byte_loader_str = "LDM";
const std::string EventManager::loader_str      = "LOAD";
const std::string EventManager::montador_str    = "MNT";
const std::string EventManager::executar_str    = "EXE";
const std::string EventManager::end_str         = "QUIT";

EventManager::EventManager() {
    this->event_str_array[0] = EventManager::dumper_str;
    this->event_str_array[1] = EventManager::byte_loader_str;
    this->event_str_array[2] = EventManager::loader_str;
    this->event_str_array[3] = EventManager::montador_str;
    this->event_str_array[4] = EventManager::executar_str;
    this->event_str_array[5] = EventManager::end_str;
}

EventManager::events_t EventManager::getEvent() {
    
    std::string event_str;
    std::cin >> event_str;

    for (int i = 0; i < events_t::num_of_events; i++) {
        if (event_str == event_str_array[i]) {
            return (EventManager::events_t) i;
        }
    }

    EventManager::events_t event = dumper;
    return event;
}

bool EventManager::treatEvent(EventManager::events_t event) {
    switch (event) {
        case dumper: {
            std::cout << "Chamando o dumper" << std::endl;
            int endereco_inicial;
            int endereco_final;
            std::cout << "Endereco inicial de leitura: ";
            std::cin >> endereco_inicial;
            std::cout << "Endereco final de leitura: ";
            std::cin >> endereco_final;
            return this->vm.dump.readMemory(endereco_inicial, endereco_final);;
            break;
        }

        case end: {
            std::cout << "desligando" << std::endl;
            return false;
            break;
        }

        case loader: {
            std::string file_name;
            std::cout << "Chamando o loader" << std::endl;
            std::cout << "Nome do arquivo .s: ";
            std::cin >> file_name;
            int endereco;
            std::cout << "Endereço inicial do programa: ";
            std::cin >> endereco;

            return vm.load.memoryWrite("../data/" + file_name, endereco);
            
            break;
        }

        case byte_loader: {
            int endereco;
            std::cout << "Chamando o loader" << std::endl;
            std::cout << "Endereco inicial de escrita: ";
            std::cin >> endereco;
            std::cout << "Insira os bytes ou STOP: " << std::endl;
            std::string input;

            int contador = 0 ;
            do {
                std::cout << "Valor " << contador++ << ": ";
                std::cin >> input;
                if (input == "STOP" || input == "stop") {
                    break;
                }
                
            } while (this->vm.load.memoryWriteByte(endereco++, stoi(input)));
            std::cout << "Fim do evento Load Byte" << std::endl;
            return true;

            break;
        }

        case montador: {
            std::cout << "Chamando o montador" << std::endl;
            std::string file_name;
            std::cout << "Nome do arquivo .asm: ";
            std::cin >> file_name;
            int address;
            std::cout << "Endereco inicial de escrita: ";
            std::cin >> address;
            this->vm.asmblr.assemblyProgram("../data/" + file_name, address);
            return vm.load.memoryWrite("../data/default_program.s", address);
        }

        case executar: {
            std::cout << "Chamando a execução" << std::endl;
            int address;
            std::cout << "Endereco inicial de execução: ";
            std::cin >> address;
            this->vm.execute(address);
            return true;
        }
        default:
            std::cout << "evento não programado" <<std::endl;
            this->vm.execute(0);
            return true;
    } 
}