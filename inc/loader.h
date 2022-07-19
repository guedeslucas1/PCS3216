#ifndef _LOADER_H_
#define _LOADER_H_

#include <stdint.h>
#include <string>

class Loader {
    public:
        Loader(uint8_t* memory_ptr, uint32_t memory_size);
        bool memoryWrite(std::string file_name, uint32_t address);
        bool memoryWriteByte(uint32_t address, uint8_t value);
        uint8_t* memory_ptr;
        uint32_t memory_size;
};

#endif
