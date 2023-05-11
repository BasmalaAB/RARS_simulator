#include <iostream>
#include <algorithm>
//#include<bitset>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <vector>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <cstdlib>
#include <cstdint>
#include <bits/stdc++.h>
using namespace std;


class RiscVSimulator {
public:
    RiscVSimulator() {
        programCounter = 0;
        registers["x0"] = 0;
        registers["x1"] = 0;
        registers["x2"] = 0;
        registers["x3"] = 0;
        registers["x4"] = 0;
        registers["x5"] = 0;
        registers["x6"] = 0;
        registers["x7"] = 0;
        registers["x8"] = 0;
        registers["x9"] = 0;
        registers["x10"] = 0;
        registers["x11"] = 0;
        registers["x12"] = 0;
        registers["x13"] = 0;
        registers["x14"] = 0;
        registers["x15"] = 0;
        registers["x16"] = 0;
        registers["x17"] = 0;
        registers["x18"] = 0;
        registers["x19"] = 0;
        registers["x20"] = 0;
        registers["x21"] = 0;
        registers["x22"] = 0;
        registers["x23"] = 0;
        registers["x24"] = 0;
        registers["x25"] = 0;
        registers["x26"] = 0;
        registers["x27"] = 0;
        registers["x28"] = 0;
        registers["x29"] = 0;
        registers["x30"] = 0;
        registers["x31"] = 0;

        //okay so up there i am initializing the registers w zero, nothing fancy or complicated
        //but idk how we will account for the other names the regiser might have so i created this other array that has the
        //names of the register, if that makes sense
        register_name["zero"] = "x0";
        register_name["ra"] = "x1";
        register_name["sp"] = "x2";
        register_name["gp"] = "x3";
        register_name["tp"] = "x4";
        register_name["t0"] = "x5";
        register_name["t1"] = "x6";
        register_name["t2"] = "x7";
        register_name["s0"] = "x8";
        register_name["fp"] = "x8";     //fp too, dk if we use that tho
        register_name["s1"] = "x9";
        register_name["a0"] = "x10";
        register_name["a1"] = "x11";
        register_name["a2"] = "x12";
        register_name["a3"] = "x13";
        register_name["a4"] = "x14";
        register_name["a5"] = "x15";
        register_name["a6"] = "x16";
        register_name["a7"] = "x17";
        register_name["s2"] = "x18";
        register_name["s3"] = "x19";
        register_name["s4"] = "x20";
        register_name["s5"] = "x21";
        register_name["s6"] = "x22";
        register_name["s7"] = "x23";
        register_name["s8"] = "x24";
        register_name["s9"] = "x25";
        register_name["s10"] = "x26";
        register_name["s11"] = "x27";
        register_name["t3"] = "x28";
        register_name["t4"] = "x29";
        register_name["t5"] = "x30";
        register_name["t6"] = "x31";

        //now i will initialize all the instructions and their formats
        instruction_struct["add"] = 'r';
        instruction_struct["sub"] = 'r';
        instruction_struct["sll"] = 'r';
        instruction_struct["slt"] = 'r';
        instruction_struct["sltu"] = 'r';
        instruction_struct["xor"] = 'r';
        instruction_struct["srl"] = 'r';
        instruction_struct["sra"] = 'r';
        instruction_struct["or"] = 'r';
        instruction_struct["and"] = 'r';

        instruction_struct["sb"] = 's';
        instruction_struct["sh"] = 's';
        instruction_struct["sw"] = 's';

        instruction_struct["auipc"] = 'u';
        instruction_struct["lui"] = 'u';

        instruction_struct["jal"] = 'j';

        instruction_struct["beq"] = 'b';
        instruction_struct["bne"] = 'b';
        instruction_struct["blt"] = 'b';
        instruction_struct["bge"] = 'b';
        instruction_struct["bltu"] = 'b';
        instruction_struct["bgeu"] = 'b';

        instruction_struct["jalr"] = 'l';
        instruction_struct["lb"] = 'l';
        instruction_struct["lh"] = 'l';
        instruction_struct["lw"] = 'l';
        instruction_struct["lbu"] = 'l';
        instruction_struct["lhu"] = 'l';

        instruction_struct["addi"] = 'i';
        instruction_struct["slti"] = 'i';
        instruction_struct["sltiu"] = 'i';
        instruction_struct["xori"] = 'i';
        instruction_struct["ori"] = 'i';
        instruction_struct["andi"] = 'i';
        instruction_struct["slli"] = 'i';
        instruction_struct["srli"] = 'i';
        instruction_struct["srai"] = 'i';

        instruction_struct["fence"] = 'x';
        instruction_struct["ecall"] = 'x';
        instruction_struct["ebreak"] = 'x';


    }


    void readFile(ifstream& file, string text, vector<string>& to_read){                 //a function to read from the text file, maybe will decide to have it return an array with every line
        file.open(text);
        if(file.is_open()){                                                              //checking to see if I accessed the file or not to begin with
            cout << "Successfully accessed program" << endl;
        }else {
            cout << "!error accessing file!" << endl;
            exit(-1);
        }
        cout << endl;
        string line;                                                                    //temp for each line
        while(!file.eof()) {
            getline(file, line);
            to_read.push_back(line);
        }
    };

    void save_in_memory(){

        string line;
        for(int i = 1; i < data_preset.size(); i++) {
            line = data_preset[i];
            string word = "", address, value;
            for(int x = 0; x < line.size(); x++){
                if(line[x] == ':'){                                              //keep reading unti;
                    address = word;
                    word = "";
                }else{
                    word += line[x];
                }
            }
            value = word;                                                      //after we are done, the value should be all that's left in the word

            memory[stoi(address)] = stoi(value);
        }
        for(auto x : memory){
            cout << "address: " << x.first << ", value: " << x.second << endl;
        }
    }

    void preset(string text_data, string text_program){                         //in preset we will initialize the registers and memory and read pc, then read the program
        ifstream read_program, read_data;
        readFile(read_data, text_data, data_preset);
        programCounter = stoi(data_preset[0]);
        cout << "PC: " << programCounter << endl;
        save_in_memory();
        readFile(read_program, text_program, program);
       // for(auto x : program) cout << x << endl;                              //just checking if program is read.
        int i = 0;
        for(auto x : program){                                              //moves the program into a map where we can reach the lines passed on their address in the memory
            programm[programCounter+(i*4)] = x;
           i++;
        }
        programEnd = programCounter+((i-1)*4);
        for(auto x : programm){
            string instruct = "";
           stringstream line;
           line.clear();
           line.str(x.second);
           line >> instruct;

            if(!instruction_struct.count(instruct) && instruct.back() == ':') {
               instruct.pop_back();
               labels[instruct] = x.first;
            }
       }
    };

void break_down_instruction_forB(string& r1, string& r2, string& label, string& instruct, string line){
    stringstream word;
    word.clear();
    word.str(line);
    word >> instruct;
    if(!instruction_struct.count(instruct)) word >> instruct;   //if the first word is a label, move to the next word, hence instruction
    word >> r1; word >> r2; word >> label;
    r2.pop_back();
    r1.pop_back();
};

    int b_instructions( string line, string& label, int& error){
        string r1, r2, instruct;
        break_down_instruction_forB(r1, r2, label, instruct, line);

        if(register_exits(r1) == 1){ }
        else if(register_exits(r1) == 0) {return -1;
        } else if(register_exits(r1) == 2) r1 = register_name[r1];

        if(register_exits(r2) == 1){ }
        else if(register_exits(r2) == 0) { return -1;
        } else if(register_exits(r2) == 2) r2 = register_name[r2];


        if(instruct == "beq"){
            if(registers[r1] == registers[r2]) return 1;
        }else if(instruct == "bne"){
            if(registers[r1] != registers[r2]) return 1;
        }else if(instruct == "blt"){
            if(registers[r1] < registers[r2]) return 1;
        }else if(instruct == "bge"){
            if(registers[r1] >= registers[r2]) return 1;
        }else if(instruct == "bltu"){
            if(abs(registers[r1]) < abs(registers[r2])) return 1;
        }else if(instruct == "bgeu"){
            if(abs(registers[r1]) >= abs(registers[r2])) return 1;
        }else return 0;
        return 0;
    };

    int register_exits(string reg) {               //this function makes sure that the given register exists
        if (registers.count(reg)) return 1;
        else if (register_name.count(reg)) return 2;
        else return 0;
    };

    void i_instructions(string line, int& error){
        string r1, imm, rd, instruct;
        break_down_instruction_forRni(rd, r1, imm, instruct, line);

        if(register_exits(r1) == 1){ }
        else if(register_exits(r1) == 0) {error = 1; return;
        } else if(register_exits(r1) == 2) r1 = register_name[r1];

        if(register_exits(rd) == 1){ } else
        if(register_exits(rd) == 0) {error = 1; return;}
        else if(register_exits(rd) == 2) rd = register_name[rd];


        if(instruct == "addi") registers[rd] = registers[r1] + stoi(imm);
        else if (instruct == "slti") registers[rd] = (registers[r1] < stoi(imm)) ? 1 : 0;
        else if (instruct == "sltiu") registers[rd] = (abs(registers[r1]) < abs(stoi(imm)))?1:0;
        else if (instruct == "xori") registers[rd] = registers[r1] ^ stoi(imm);
        else if (instruct == "ori") registers[rd] = registers[r1] || stoi(imm);
        else if (instruct == "andi") registers[rd] = registers[r1] && stoi(imm);
        else if (instruct == "slli") registers[rd] = registers[r1] << stoi(imm);
        else if (instruct == "srli") registers[rd] = registers[r1] >> stoi(imm);
        else if(instruct == "srai") registers[rd] = sra(registers[r1], stoi(imm));

    };

    void break_down_instruction_S(string& rd, string& r1, string& offset, string& instruct, string line){
        stringstream word;
        word.clear();
        word.str(line);
        word >> instruct;
        if(!instruction_struct.count(instruct)) word >> instruct;   //if the first word is a label, move to the next word, hence instruction
        word >> r1; word >> rd;
        r1.pop_back();

        string offs = "", empty;
        empty = "";
        for(auto x : rd) {
            if(x == '('){
                offset = empty;
                empty = "";
            }else empty += x;
        }
        rd = empty;
        rd.pop_back();
    };

    void i0_instructions(string line, int& error){
        string r1, offset, rd, instruct;
        break_down_instruction_S(rd, r1, offset, instruct, line);

        if(register_exits(r1) == 1){ }
        else if(register_exits(r1) == 0) {error = 1; return;
        } else if(register_exits(r1) == 2) r1 = register_name[r1];

        if(register_exits(rd) == 1){ } else
        if(register_exits(rd) == 0) {error = 1; return;}
        else if(register_exits(rd) == 2) rd = register_name[rd];

        if (instruct == "lw") registers[r1] = memory[registers[rd] + stoi(offset)];
        else if (instruct == "lh") registers[r1] = (memory[registers[rd] + stoi(offset)] & 0b00000000000000001111111111111111);
        else if (instruct == "lb") registers[r1] = (memory[registers[rd] + stoi(offset)] & 0b00000000000000000000000011111111);
        else if (instruct == "lhu") registers[r1] = (uint32_t) (memory[registers[rd] + stoi(offset)] & 0b00000000000000001111111111111111);
        else if (instruct == "lbu") registers[r1] = (uint32_t) (memory[registers[rd] + stoi(offset)] & 0b00000000000000000000000011111111);
        else if (instruct == "jalr") registers[r1] = (uint32_t) (memory[registers[rd] + stoi(offset)] & 0b00000000000000000000000011111111);

    };

    void s_instructions(string line, int& error){
        string r1, offset, rd, instruct;
        break_down_instruction_S(rd, r1, offset, instruct, line);

        if(register_exits(r1) == 1){ }
        else if(register_exits(r1) == 0) {error = 1; return;
        } else if(register_exits(r1) == 2) r1 = register_name[r1];

        if(register_exits(rd) == 1){ } else
        if(register_exits(rd) == 0) {error = 1; return;}
        else if(register_exits(rd) == 2) rd = register_name[rd];

<<<<<<< HEAD
        if(registers[rd] +stoi(offset) > 1000){ error = 1; return;}
=======
>>>>>>> e0b92312fffe53a601f862d9b6c55ee1bcbf4560
     if (instruct == "sw") memory [registers[rd] +stoi(offset)]=  registers[r1]  ;
     else if (instruct == "sh") memory [registers[rd] +stoi(offset)]=  registers[r1] & 0b00000000000000001111111111111111;
     else if (instruct == "sb") memory [registers[rd] +stoi(offset)]=  registers[r1] & 0b00000000000000000000000011111111;

    };

    void r_instructions(string line, int& error){
        string r1, r2, rd, instruct;
        break_down_instruction_forRni(rd, r1, r2, instruct, line);

         if(register_exits(r1) == 1){ }
        else if(register_exits(r1) == 0) {error = 1; return;
        } else if(register_exits(r1) == 2) r1 = register_name[r1];

        if(register_exits(r2) == 1){ }
        else if(register_exits(r2) == 0) {error = 1; return;
        } else if(register_exits(r2) == 2) r2 = register_name[r2];

        if(register_exits(rd) == 1){ } else
        if(register_exits(rd) == 0) {error = 1; return;}
        else if(register_exits(rd) == 2) rd = register_name[rd];

        if(instruct == "add") registers[rd] = registers[r1] + registers[r2];
        else if(instruct == "sub") registers[rd] = registers[r1] - registers[r2];
        else if(instruct == "and") registers[rd] = registers[r1] && registers[r2];
        else if(instruct == "or") registers[rd] = registers[r1] || registers[r2];
        else if(instruct == "xor") registers[rd] = registers[r1] ^ registers[r2];
        else if(instruct == "sll") registers[rd] = registers[r1] << registers[r2];
        else if(instruct == "srl") registers[rd] = registers[r1] >> registers[r2];
        else if(instruct == "slt") registers[rd] = (registers[r1] < registers[r2]) ? 1 : 0;
        else if(instruct == "sltu") registers[rd] = (abs(registers[r1]) < abs(registers[r2])) ? 1 : 0;
        else if(instruct == "sra") registers[rd] = sra(registers[r1], registers[r2]);

    };

    int32_t sra(int32_t x, uint32_t bits) //takes 2 arguments, x- value we want to shift, and bits= num of bits to shift by 
    {
        int32_t sign = x >> 31;  //takes sign bit to check the number's sign (check if it's +ve or -ve)
        int32_t sh = x >> bits;   //right shifts x by the number of bits provided
        int32_t mask = -((sign << bits) != 0);

        //Explanation of line 3 of the function:
        //If the sign bit shifted by shamt bits is non-zero,
        //then the mask will be set to -1 (i.e., all bits set to 1), meaning the shift result should be sign-extended.
        //Otherwise, the mask will be set to 0.

        return (sh | mask);  //uses bitwise or operation to apply the necessary sign extension (if needed)
    }

<<<<<<< HEAD
=======

>>>>>>> e0b92312fffe53a601f862d9b6c55ee1bcbf4560
    void u_instructions(string line, int pc, int& error)
    {
        //LUI  Load Upper Immediate, loads the imm value into the upper 20 bits of a number, leaving the rest 12 as zeros
        // AUIPC  Add Upper Immediate to PC
        string rd, instruct, imm;
        break_down_instruction_forU(rd, instruct, imm, line);
<<<<<<< HEAD

        if(register_exits(rd) == 1){ }
        else if(register_exits(rd) == 0) {error = 1; return;
        } else if(register_exits(rd) == 2) rd = register_name[rd];

        int immediate = stoi(imm) << 12;
        if(instruct == "lui") registers[rd] = immediate;
        if(instruct == "auipc") registers[rd] = immediate + pc;

=======
        if(register_exits(rd) == 1){ }
        else if(register_exits(rd) == 0) {error = 1; return;
        } else if(register_exits(rd) == 2) rd = register_name[rd];

        int immediate = stoi(imm) << 12;
        if(instruct == "lui") registers[rd] = immediate;
        if(instruct == "auipc") registers[rd] = immediate + pc;

>>>>>>> e0b92312fffe53a601f862d9b6c55ee1bcbf4560
    };

    void break_down_instruction_forU(string& rd, string& instruct, string& imm, string line) {
        stringstream word;
        word.clear();
        word.str(line);
        word >> instruct;

        if (!instruction_struct.count(instruct)) word >> instruct;   //if the first word is a label, move to the next word, hence instruction
        word >> rd;
        rd.pop_back();
        word >> imm;

    };

    void break_down_instruction_forRni(string& rd, string& r1, string& r2, string& instruct, string line){
        stringstream word;
        word.clear();
        word.str(line);
        word >> instruct;
        if(!instruction_struct.count(instruct)) word >> instruct;   //if the first word is a label, move to the next word, hence instruction
        word >> rd; word >> r1; word >> r2;
        rd.pop_back();
        r1.pop_back();
    };

    void show(){
        cout << "REGISTERS: " << endl;
        for(int i = 0; i < 32; i++){
            string reg = 'x' + to_string(i);
            cout << reg << ": "  << registers[reg] << endl;
        }cout << endl;

        cout << "MEMORY: " << endl;
        for(auto x : memory){
            cout << "address: " << x.first << ", value: " << x.second << endl;
        }   cout << endl;
    };

    void execute(){
        int error = 0;
        for(int pc = programCounter; pc <= programEnd; pc += 4){

            string line = programm[pc];
            stringstream word;
            word.clear();
            word.str(line);
            string instruct; word >> instruct;                                                    //instruct is the first word in a line
            if(instruct[0] != '#' && instruct[0] != '.') {                                        //check that it's not a comment or a .text for example
                if(!instruction_struct.count(instruct)) word >> instruct;                      //if the first word is a label, move to the next word, hence instruction
                if (instruct == "ecall" || instruct == "fence" || instruct == "ebreak") return;

                char index = instruction_struct[instruct];
                if(index == 'i') {i_instructions(line, error);         }
                else if(index == 'r'){r_instructions(line, error);     }
                else if(index == 'u'){u_instructions(line, pc, error);     }
                else if(index == 's'){s_instructions(line, error);     }
<<<<<<< HEAD
                else if(index == 'l'){
                    if(instruct == "jalr"){
                        string r1, offset, rd, instruct;
                        break_down_instruction_S(rd, r1, offset, instruct, line);

                        if(register_exits(r1) == 1){ }
                        else if(register_exits(r1) == 0) {error = 1; return;
                        } else if(register_exits(r1) == 2) r1 = register_name[r1];

                        if(register_exits(rd) == 1){ } else
                        if(register_exits(rd) == 0) {error = 1; return;}
                        else if(register_exits(rd) == 2) rd = register_name[rd];

                        registers[r1] = pc + 4;
                        pc = registers[rd] + stoi(offset);
                    }
                    else i0_instructions(line, error);    }
=======
                else if(index == 'l'){i0_instructions(line, error);    }
>>>>>>> e0b92312fffe53a601f862d9b6c55ee1bcbf4560
                else if(index == 'b'){
                    string label;
                    int res = b_instructions(line, label, error);
                    if(res == 1) pc = labels[label] - 4;                                             //if b instrcution is true, return to label address
                    else if(res == -1) {
                        cout << "ERROR!! UNKNOWN LABEL!!" << endl;
                        return;
                    }else { }}
                else if(index == 'j'){
                    string label;

                    word >> label;
                    registers["x1"] = pc + 4;           //save the return address
                    if(!labels.count(label)){
                        cout << "ERROR!! UNKNOWN LABEL!!" << endl;
                        return;
                    }
                    else pc = labels[label] - 4;             //jump to the label

                }else cout << "instruction not recognized" << endl;
                cout << "PC: " << pc << endl;
                show();

                if(error == 1) {
                    cout << "MET ERROR, TERMINATE" << endl;
                    return;
                }
            }
        }
    };


private:
    int32_t programCounter, programEnd;
    map<int32_t, int32_t> memory;                                              // Memory contents, using an unordered map, the first parameter is the address 'n second is the content
    map<string, int32_t> registers;                                        // Register contents
    unordered_map<string, string> register_name;                                 // an array just in case we have a register used as its name not the normal x1,2,3,.. etc
    unordered_map<string, char> instruction_struct;


    vector<string> data_preset;
    vector<string> program;

    map<int32_t, string> programm;
    unordered_map<string, int32_t> labels;

};

//uint32_t
int main() {
    RiscVSimulator sim;
    sim.preset( "C:\\Users\\DELL\\Desktop\\RARS_simulator\\simulator\\txt_files\\data.txt", "C:\\Users\\DELL\\Desktop\\RARS_simulator\\simulator\\txt_files\\program.txt");
    sim.execute();

    return 0;
}
