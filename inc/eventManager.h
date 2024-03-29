#ifndef _EVENTMANAGER_H_
#define _EVENTMANAGER_H_

// #include "dumper.h"
// #include "loader.h"
#include "virtualMachine.h"

#include <string>


class EventManager {
    public:
        EventManager();

        enum events_t {
            dumper,
            byte_loader,
            loader,
            montador,
            executar,
            end,
            list,
            log,
            num_of_events
        };
        std::string event_str_array[num_of_events]; 
        
        EventManager::events_t getEvent();
        bool treatEvent(EventManager::events_t event);
        
        void init();
        bool log_enable = false;

        static const std::string dumper_str, byte_loader_str, loader_str, montador_str, executar_str, end_str, log_str, list_str;
    private:
        VirtualMachine vm;
};

#endif
