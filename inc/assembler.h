#ifndef _ASSEMBLER_H_
#define _ASSEMBLER_H_

#include "stdint.h"
#include <string>

class Assembler {
    public:
        Assembler(uint8_t* memory_ptr, uint32_t memory_size);
        bool assemblyProgram(std::string file_name, uint32_t address);
        uint8_t* memory_ptr;
        uint32_t memory_size;

        enum instructions_t {
            jump,
            jump0,
            jumpn,
            add,
            sub,
            mul,
            div,
            load,
            store,
            call,
            rtn,
            stop,
            data,
            write,
            num_of_instructions
        };

        std::string instruction_str_array[num_of_instructions]; 
        std::string instruction_opcode_array[num_of_instructions];


        static const std::string JUMP_opcode, JUMP0_opcode, JUMPN_opcode, CALL_opcode, ADD_opcode, SUB_opcode, MUL_opcode, DIV_opcode, LOAD_opcode, STORE_opcode, RTN_opcode, STOP_opcode, DATA_opcode, WRITE_opcode;
        static const std::string JUMP_string, JUMP0_string, JUMPN_string, CALL_string, ADD_string, SUB_string, MUL_string, DIV_string, LOAD_string, STORE_string, RTN_string, STOP_string, DATA_string, WRITE_string;
};

#endif
