#ifndef _LOADER_H_
#define _LOADER_H_

#include <stdint.h>

class Loader {
    public:
        Loader();
        void getDataFromUser();
        void memoryWrite();
    private:
        uint8_t data_buffer[1024];
        int initial_address;
        int data_lenght;
};

#endif
