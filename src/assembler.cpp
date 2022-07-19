#include "assembler.h"
#include <iostream>
#include <iostream>
#include <fstream>
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
    this->instruction_opcode_array[7]  = Assembler::LOAD_opcode;
    this->instruction_opcode_array[8]  = Assembler::STORE_opcode;
    this->instruction_opcode_array[9]  = Assembler::CALL_opcode;
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
    this->instruction_str_array[7]  = Assembler::LOAD_string;
    this->instruction_str_array[8]  = Assembler::STORE_string;
    this->instruction_str_array[9]  = Assembler::CALL_string;
    this->instruction_str_array[10] = Assembler::RTN_string;
    this->instruction_str_array[11] = Assembler::STOP_string;
    this->instruction_str_array[12] = Assembler::DATA_string;
    this->instruction_str_array[13] = Assembler::WRITE_string;

};

bool Assembler::assemblyProgram(std::string file_name, uint32_t address) {
    std::ofstream MyFile("../data/default_program.s");

    std::string instruction;
    std::cout  << "lendo o arquivo" << std::endl;
    std::ifstream program_file;
    std::string line;
    program_file.open (file_name, std::ios::in);

    bool is_instr = false;
    int counter = 0;
    while (getline(program_file,line)) {

        int n_chars_mnemonico;
        if (line[3] == ' ') n_chars_mnemonico = 3; 
        if (line[4] == ' ') n_chars_mnemonico = 4; 
        if (line[5] == ' ') n_chars_mnemonico = 5; 
        
        std::cout << "linha " << counter++ <<": " << line << std::endl;
        for (int inst = 0; inst < num_of_instructions; inst++) {
            //std::cout << instruction_str_array[inst] << " vs " << line.substr(0,n_chars_mnemonico) << std::endl;

            if (instruction_str_array[inst] == line.substr(0,n_chars_mnemonico)) {
                
                std::cout << "Mnemônico:"  << instruction_str_array[inst] << std::endl;
                std::cout << "Opcode: " << instruction_opcode_array[inst] << std::endl ;
                
                if (inst != stop ) {
                    std::string operador = line.substr(n_chars_mnemonico,20);
                    std::cout << "Operador: " << operador << std::endl;
                    instruction = instruction_opcode_array[inst] + std::bitset<12>(stoi(operador)).to_string();
                } else {
                    instruction = instruction_opcode_array[inst] + std::bitset<4>(0).to_string();
                }

                
                std::cout << "instrução: " << instruction << std::endl;
                std::cout << std::endl;
            } 
        }

        MyFile << instruction << "\n";
    }
    MyFile.close();
    std::cout << std::endl << "fim de leitura" << std::endl;
    program_file.close();




    return true;
}