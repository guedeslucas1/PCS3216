#include "assembler.h"
#include <iostream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <map>
#include <bitset>

const std::string Assembler::JUMP_opcode  = "0000";
const std::string Assembler::JUMP0_opcode = "0001";
const std::string Assembler::JUMPN_opcode = "0010";
const std::string Assembler::ADD_opcode   = "0011";
const std::string Assembler::SUB_opcode   = "0100";
const std::string Assembler::MUL_opcode   = "0101";
const std::string Assembler::DIV_opcode   = "0110";
const std::string Assembler::LOAD_opcode  = "0111";
const std::string Assembler::STORE_opcode = "1000";
const std::string Assembler::CALL_opcode  = "1001";
const std::string Assembler::RTN_opcode   = "1100";
const std::string Assembler::STOP_opcode  = "1101";
const std::string Assembler::DATA_opcode  = "1110";
const std::string Assembler::WRITE_opcode = "1111";

const std::string Assembler::JUMP_string  = "JUMP";
const std::string Assembler::JUMP0_string = "JUMP0";
const std::string Assembler::JUMPN_string = "JUMPN";
const std::string Assembler::ADD_string   = "ADD";
const std::string Assembler::SUB_string   = "SUB";
const std::string Assembler::MUL_string   = "MUL";
const std::string Assembler::DIV_string   = "DIV";
const std::string Assembler::LOAD_string  = "LOAD";
const std::string Assembler::STORE_string = "STORE";
const std::string Assembler::CALL_string  = "CALL";
const std::string Assembler::RTN_string   = "RTN";
const std::string Assembler::STOP_string  = "STOP";
const std::string Assembler::DATA_string  = "DATA";
const std::string Assembler::WRITE_string = "WRITE";


Assembler::Assembler(uint8_t* memory_ptr, uint32_t memory_size) {
    this->memory_ptr = memory_ptr;
    this->memory_size = memory_size;

    this->instruction_opcode_array[0]  = Assembler::JUMP_opcode;
    this->instruction_opcode_array[1]  = Assembler::JUMP0_opcode;
    this->instruction_opcode_array[2]  = Assembler::JUMPN_opcode;
    this->instruction_opcode_array[3]  = Assembler::CALL_opcode;
    this->instruction_opcode_array[4]  = Assembler::ADD_opcode;
    this->instruction_opcode_array[5]  = Assembler::SUB_opcode;
    this->instruction_opcode_array[6]  = Assembler::MUL_opcode;
    this->instruction_opcode_array[7]  = Assembler::DIV_opcode;
    this->instruction_opcode_array[8]  = Assembler::LOAD_opcode;
    this->instruction_opcode_array[9]  = Assembler::STORE_opcode;
    this->instruction_opcode_array[10] = Assembler::RTN_opcode;
    this->instruction_opcode_array[11] = Assembler::STOP_opcode;
    this->instruction_opcode_array[12] = Assembler::DATA_opcode;
    this->instruction_opcode_array[13] = Assembler::WRITE_opcode;

    this->instruction_str_array[0]  = Assembler::JUMP_string;
    this->instruction_str_array[1]  = Assembler::JUMP0_string;
    this->instruction_str_array[2]  = Assembler::JUMPN_string;
    this->instruction_str_array[3]  = Assembler::CALL_string;
    this->instruction_str_array[4]  = Assembler::ADD_string;
    this->instruction_str_array[5]  = Assembler::SUB_string;
    this->instruction_str_array[6]  = Assembler::MUL_string;
    this->instruction_str_array[7]  = Assembler::DIV_string;
    this->instruction_str_array[8]  = Assembler::LOAD_string;
    this->instruction_str_array[9]  = Assembler::STORE_string;
    this->instruction_str_array[10] = Assembler::RTN_string;
    this->instruction_str_array[11] = Assembler::STOP_string;
    this->instruction_str_array[12] = Assembler::DATA_string;
    this->instruction_str_array[13] = Assembler::WRITE_string;
};

bool Assembler::assemblyProgram(std::string file_name, uint32_t address, bool log) {
    std::ifstream program_file;
            
    std::string line;
    int instr_number = 0;
    
    int symbol_table_index = 0;
    std::map<std::string, int> symbol_table;
    std::string symbol;

    std::ofstream MyFile("../data/default_program.s");
    
    std::string instruction;
    

    bool first_step = true;

    bool is_instr = true;
    int counter = 0;


    for (int step = 1; step <= 2; step ++) {
        if (log)
            std::cout << std::endl << "Lendo o arquivo " << file_name << " no passo: " << step << std::endl << std::endl;
        

        program_file.open (file_name, std::ios::in);

        while (getline(program_file,line)) {

            int n_chars_mnemonico;

            if (line[0] != ' ') {
                symbol = line;
                symbol.pop_back();
                symbol_table.insert({symbol, symbol_table_index});
                continue;
            } 
            if (line[0] == ' ') { //is not label
                
                if (line[3+4] == ' ') n_chars_mnemonico = 3; 
                if (line[4+4] == ' ') n_chars_mnemonico = 4; 
                if (line[5+4] == ' ') n_chars_mnemonico = 5; 
                
                if (step == 2) {
                    if(log) {
                        if (counter == 0) {
                            std::cout <<         " ______________________________" << std::endl;
                        } else {
                            std::cout <<         "|______________________________|" << std::endl;
                        }
                        std::cout <<             "|           Linha " << std::setfill(' ') << std::setw(2) << ++counter <<"           |" << std::endl;
                        std::cout <<             "|______________________________|" << std::endl;
                    }
                }

                for (int inst = 0; inst < num_of_instructions; inst++) {
                    //std::cout << instruction_str_array[inst] << " vs " << line.substr(0,n_chars_mnemonico) << std::endl;
                    if (instruction_str_array[inst] == line.substr(0+4,n_chars_mnemonico)) {
                        
                        if (step == 2 && log) {
                            std::cout <<     "| Mnemônico |"  << std::setfill(' ') << std::setw(5) << instruction_str_array[inst] << "             |" << std::endl;
                            std::cout <<     "| Opcode    | " << instruction_opcode_array[inst] << "             |" <<  std::endl ;
                        }

                        if (inst != stop ) {
                            symbol_table_index += 2;
                            if (step == 2) {

                                std::string operador = line.substr(n_chars_mnemonico+4,20);
                                operador = operador.substr(operador.find_first_not_of(" "), operador.find_last_not_of(" ")+1);
                                if (instruction_str_array[inst] != "DATA") {
                                    int  real_data = symbol_table.find(operador)->second;
                                    if (log)
                                        std::cout << "| Operador  | "  << std::setfill(' ') << std::setw(7)  << operador << " => " <<  std::setfill(' ') << std::setw(4) << std::dec << real_data << "  |" << std::endl;
                                    instruction = instruction_opcode_array[inst] + std::bitset<12>(real_data).to_string();
                                } else {
                                    if (log)
                                        std::cout << "| Operador  | "  << std::setfill(' ') << std::setw(4)  << operador <<   "             |" << std::endl;
                                    instruction = std::bitset<16>(stoi(operador)).to_string();
                                }
                            }
                        } else {
                            symbol_table_index += 1;
                            if (step == 2) {
                                instruction = instruction_opcode_array[inst] + std::bitset<4>(0).to_string();
                            }
                        }

                        if (step==2 && log)
                            std::cout <<     "| Instrução | " << std::setfill(' ') << std::setw(16) << instruction << " |" << std::endl;
                    } 
                }

                if (step == 2)
                    MyFile << instruction << "\n";
            }
        }

        if(step == 2 && log)
            std::cout <<"|______________________________|" << std::endl << std::endl;

        if(step == 1 && log) {
            std::cout<< "Tabela de simbolos"<<std::endl << std::endl;
            std::cout << "Simbolo\tEndereço\n";
            for (auto itr = symbol_table.begin(); itr != symbol_table.end(); ++itr) {
                std::cout << itr->first
                    << "\t0x" << std::hex <<itr->second << '\n';
            }
        }
    program_file.close();
    }
    MyFile.close();

    

    std::cout << std::endl << "Fim de leitura" << std::endl;
    

    return true;
}