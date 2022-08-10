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
        
        bool execute(int initial_address, bool log);


        uint8_t memory[4096] = {0};
    
        uint16_t acc;

        Dumper dump;
        Loader load;
        Assembler asmblr;

};

#endif
