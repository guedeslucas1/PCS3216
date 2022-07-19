#ifndef _DUMPER_H_
#define _DUMPER_H_

#include "stdint.h"

class Dumper {
    public:
        Dumper(uint8_t* memory_ptr, uint32_t memory_size);
        bool readMemory(int initialAddress, int finalAddress);
        uint8_t* memory_ptr;
        uint32_t memory_size;
};

#endif
