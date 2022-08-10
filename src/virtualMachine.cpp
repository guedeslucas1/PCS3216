#include "virtualMachine.h"
#include <iostream>
#include <iostream>
#include <fstream>
#include <bitset>

VirtualMachine::VirtualMachine() : dump(memory, 4096), load(memory, 4096), asmblr(memory, 4096) {
    this->acc = 0;
    this->memory[0x0a] = 0x01;
    this->memory[0x1a] = 0x12;
    this->memory[0x21] = 0x42;
    this->memory[0x3F] = 0x20;
}

bool VirtualMachine::execute(int initial_address, bool log) {
    int PC = initial_address;
    int LR = 0;

    while (this->memory[PC]>>4 != 0b1101) { // Não é STOP

        
        int opcode = memory[PC]>>4;
        int arg_h = (int)((uint8_t) (memory[PC] << 4)) >> 4;
        PC++;
        int arg_l = memory[PC];

        int arg = arg_h<< 8 | arg_l;

        int operando = ((int)this->memory[arg] | (int)this->memory[arg+1]);

        PC++;
        
        switch (opcode) {
            case 0b0000: {              //jump
                PC = arg;
                break;
            }

            case 0b0001: {              //jump0
                if (this->acc == 0) {
                    PC = arg;
                }
                break;
            }
            
            case 0b0010: {              //jumpn
                if ( (int8_t) this->acc < 0 ) {
                    PC = arg;
                }
                break;
            }

            case 0b0011: {              //add
                this->acc += operando;
                break;    
            }
            
            case 0b0100: {              //sub
                this->acc -= operando;
                break;
            }     

            case 0b0101: {              //mul
                this->acc *= operando;
                break;
            }

            case 0b0110: {              //DIV
                this->acc /= operando;
                break;
            }

            case 0b0111: {              //load
                this->acc = operando;
                break;
            }

            case 0b1000: {              //store

                uint8_t acc_h = acc>>8;
                uint8_t acc_l = acc;

                this->memory[arg] = acc_h;
                this->memory[arg+1] = acc_l;
                break;
            }   
            
            case 0b1001: {              //call
                LR = PC;
                PC = operando;
                break;
            }   
            
            case 0b1010: {              //rtn
                PC = LR;
                break;
            }   

        default:
            break;
        }
        

    }
}
