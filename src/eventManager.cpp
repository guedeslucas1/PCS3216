#include "eventManager.h"
#include <iostream>

const std::string EventManager::dumper_str      = "DMP";
const std::string EventManager::byte_loader_str = "LDM";
const std::string EventManager::loader_str      = "LOAD";
const std::string EventManager::montador_str    = "MNT";
const std::string EventManager::executar_str    = "EXE";
const std::string EventManager::end_str         = "QUIT";
const std::string EventManager::log_str         = "LOG";
const std::string EventManager::list_str        = "LIST";

EventManager::EventManager() {
    this->event_str_array[0] = EventManager::dumper_str;
    this->event_str_array[1] = EventManager::byte_loader_str;
    this->event_str_array[2] = EventManager::loader_str;
    this->event_str_array[3] = EventManager::montador_str;
    this->event_str_array[4] = EventManager::executar_str;
    this->event_str_array[5] = EventManager::end_str;
    this->event_str_array[6] = EventManager::list_str;
    this->event_str_array[7] = EventManager::log_str;
}

void EventManager::init() {

    std::cout << "- lista de eventos disponíveis -" << std::endl;

    std::cout <<                                " _______________________________________" << std::endl;
    std::cout <<                                "|COMANDO  |  DEFINIÇÃO                  |" << std::endl;
    std::cout <<                                "|---------------------------------------|" << std::endl;
    std::cout << "|" << this->event_str_array[0] << "      |  Dumper                     |"<< std::endl;
    std::cout << "|" << this->event_str_array[1] << "      |  Loader byte a byte         |"<< std::endl;
    std::cout << "|" << this->event_str_array[2] <<  "     |  Loader de arquivo binário  |"<< std::endl;
    std::cout << "|" << this->event_str_array[3] << "      |  Montador                   |"<< std::endl;
    std::cout << "|" << this->event_str_array[4] << "      |  Executar                   |"<< std::endl;
    std::cout << "|" << this->event_str_array[5] <<  "     |  Desligar simulador         |"<< std::endl;
    std::cout << "|" << this->event_str_array[7] << "      |  Liga/Desliga Log           |"<< std::endl;
    std::cout << "|" << this->event_str_array[6] <<  "     |  Lista comandos disponiveis |"<< std::endl;
    std::cout <<                                "|_______________________________________|" << std::endl << std::endl;
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
            std::cout << std::endl << "- Chamando o Dumper -" << std::endl << std::endl;
            int endereco_inicial;
            int endereco_final;
            std::cout << "Endereço inicial de leitura: ";
            std::cin >> endereco_inicial;
            std::cout << "Endereço final de leitura: ";
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
            std::cout << std::endl << "- Chamando o Loader -" << std::endl << std::endl;
            std::cout << "Nome do arquivo .s: ";
            std::cin >> file_name;
            int endereco;
            std::cout << "Endereço inicial do programa: ";
            std::cin >> endereco;

            return vm.load.memoryWrite("../data/" + file_name, endereco, this->log_enable);
            
            break;
        }

        case byte_loader: {
            int endereco;
            std::cout << std::endl << "- Chamando o Loader -" << std::endl << std::endl;
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
            std::cout << "Fim do evento Load Byte" << std::endl << std::endl;
            return true;

            break;
        }

        case montador: {
            std::cout << std::endl << "- Chamando o Montador -" << std::endl << std::endl;

            this->vm.asmblr.assemblyProgram("../data/program.asm", 0, this->log_enable);

            std::cout << "Gerando arquivo: default_program.s" << std::endl;
            std::cout << "Fim de escrita na memória." << std::endl << std::endl;
            return vm.load.memoryWrite("../data/default_program.s", 0, this->log_enable);
        }

        case executar: {
            std::cout << std::endl << "- Chamando a execução -" << std::endl << std::endl;
            int address;
            std::cout << "Endereco inicial de execução: ";
            std::cin >> address;
            this->vm.execute(address, true);
            
            std::cout << "Fim da execução" << std::endl << std::endl;
            return true;
        }

        case list: {
            this->init();
            return true;
        }

        case log: {
            std::string input;
            std::cout << "Ativar Log? [S/N]";
            std::cin >> input;
            this->log_enable = (input == "S");
            break;
        }

        default:
            std::cout << "evento não programado" <<std::endl;
            return true;
    } 
}