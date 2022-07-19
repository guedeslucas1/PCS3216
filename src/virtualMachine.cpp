#include "virtualMachine.h"
#include <iostream>
#include <iostream>
#include <fstream>
#include <bitset>

VirtualMachine::VirtualMachine() : dump(memory, 4096), load(memory, 4096), asmblr(memory, 4096) {
    this->acc = 0;
}

bool VirtualMachine::execute(uint32_t initial_address) {
    int PC = initial_address;
    int LR = 0;;
    int contador =0 ;
    while (this->memory[PC]>>4 != 0b1101 && contador++ < 30 ) {
        int opcode = memory[PC]>>4;
        int arg_h = (int)((uint8_t) (memory[PC] << 4)) >> 4;
        PC++;
        int arg_l = memory[PC];

        int arg = arg_h<<8 | arg_l;
        //std::cout << contador << ": " << opcode << " " << arg_h << " " << arg_l << " " << arg <<std::endl; 

        PC++;

        switch (opcode) {
            case 0b0000: {              //jump
                PC = arg;
                break;
            }

            case 0b0001: {
                if (this->acc == 0) {
                    PC = arg;
                }
                break;
            }
            
            case 0b0010: {
                if ( (int8_t) this->acc < 0 ) {
                    PC = arg;
                }
                break;
            }

            case 0b0011: {              //add
                this->acc += arg;
                break;    
            }
            
            case 0b0100: {              //sub
                this->acc -= arg;
                break;
            }     

            case 0b0101: {              //mul
                this->acc *= arg;
                break;
            }

            case 0b0110: {              //DIV
                this->acc /= arg;
                break;
            }

            case 0b0111: {              //load
                this->acc = arg;
                break;
            }

            case 0b1000: {              //store
                this->memory[arg] = this->acc;
                break;
            }   
            
            case 0b1001: {              //call
                LR = PC;
                PC = arg;
                break;
            }   
            
            case 0b1010: {              //rtn
                PC = LR;
                break;
            }   

        default:
            std::cout << "instrucão não reconhecida: " << opcode << std::endl;
            break;
        }
    }
}
