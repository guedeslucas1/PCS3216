#ifndef _EVENTMANAGER_H_
#define _EVENTMANAGER_H_

#include "dumper.h"
#include "loader.h"

class EventManager {
    public:
        EventManager();
        char getEvent();
        bool treatEvent(char event);

        static const char dumper, end, loader;
    private:
        Dumper dump;
        Loader load;
};

#endif
