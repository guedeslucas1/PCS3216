#ifndef _VIRTUAL_MACHINE_H_
#define _VIRTUAL_MACHINE_H_

#include <stdint.h>
#include <string>

#include "dumper.h"
#include "loader.h"
#include "assembler.h"

class VirtualMachine {
    public:
        VirtualMachine();
        
        bool execute(uint32_t initial_address);

        uint8_t memory[4096] = {0};
    
        uint32_t acc;

        Dumper dump;
        Loader load;
        Assembler asmblr;

    private:
        
};

#endif
