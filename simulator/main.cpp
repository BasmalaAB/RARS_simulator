#include <iostream>
#include <algorithm>
//#include<bitset>
#include <fstream>
#include <sstream>
//#include <map>
#include <string>
#include <vector>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <cstdlib>
using namespace std;


class RiscVSimulator {
public:
    RiscVSimulator() {
        error = 0;
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

        instruction_struct["jalr"] = 'i';
        instruction_struct["lb"] = 'i';
        instruction_struct["lh"] = 'i';
        instruction_struct["lw"] = 'i';
        instruction_struct["lbu"] = 'i';
        instruction_struct["lhu"] = 'i';
        instruction_struct["addi"] = 'i';
        instruction_struct["slti"] = 'i';
        instruction_struct["sltiu"] = 'i';
        instruction_struct["xori"] = 'i';
        instruction_struct["ori"] = 'i';
        instruction_struct["andi"] = 'i';
        instruction_struct["slli"] = 'i';
        instruction_struct["srli"] = 'i';
        instruction_struct["srai"] = 'i';


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
           else error = 1;
       }
       for(auto x : labels) cout << x.first << " " << x.second << endl;
    };

   // void r_functions(string line, string instruction){

//        stringstream isstring;
//        string instruct = "",reg1, reg2, rd;
//        isstring.clear();
//        isstring.str(line);
//        isstring >> instruct;
//        isstring >> rd;
//        rd.pop_back();                              //removing the ',' at the end
//        isstring >> reg1;
//        reg1.pop_back();                            //removing the ',' at the end
//        isstring >> reg2;
//
//        string r1, r2, rdst;
//        if(!registers.count(reg1)||!registers.count(reg2)||!registers.count(rd)) {
//            //if you find the register in the array, count function returns 1, else 0
//            if( !registers.count((register_name[reg1])) ||                    //checking if reg1 exists
//                !registers.count((register_name[reg2])) ||                    //checking if reg2 exists
//                !registers.count(register_name[rd]))  {                       //checking if rd exists
//                cout << "unknown reg" << endl;
//                return;
//            }   else{
//
//                if(!registers.count(reg1)) r1 = register_name[reg1];
//                else r1 = reg1;
//                if(!registers.count(reg2)) r2 = register_name[reg2];
//                else r2 = reg2;
//                if(!registers.count(rd)) rdst = register_name[rd];
//                else rdst = rd;
//
//            }
//        }
//        //by the end, if any of the regsiters enetered are missing, we should know
//        if (rd != "x0" && rd != "zero") {
//
//            if (instruction == "add") {
//                registers[rdst] = registers[r1] + registers[r2];
//            }else if(instruction == "sub") registers[rdst] = registers[r1] - registers[r2];
//            else if(instruction == "sll") registers[rdst] = registers[r1] << registers[r2];
//            else if(instruction == "srl") registers[rdst] = registers[r1] >> registers[r2];
//            else if(instruction == "and") registers[rdst] = registers[r1] && registers[r2];
//            else if(instruction == "or") registers[rdst] = registers[r1] || registers[r2];
//            else if(instruction == "xor") registers[rdst] = registers[r1] ^ registers[r2];
//            else if(instruction == "sltu") registers[rdst] = (registers[r1] < abs(registers[r2]))?1:0;
//            else if(instruction == "slt") registers[rdst] = (registers[r1] < registers[r2])?1:0;
//            else if(instruction == "sra") registers[rdst] = registers[r1] << registers[r2];
//

//        }
//    };
    void execute(){
        for(auto line : program){
            stringstream isstring;
            string instruct = "";
            isstring.clear();
            isstring.str(line);
            isstring >> instruct;                                                   //just the first word of each line, which will either be an instruction or a label, or a comment

            if(instruct[0] != '#' && instruct[0] != '.'){                               //check that it's not a comment or a .text for example
                if(instruct == "ecall" || instruct == "fence" || instruct == "ebreak") return;

            char index = instruction_struct[instruct];

            switch(index){
                case 'i':
                    cout << "instruction found" << endl;

                    break;
                case 'r':
                    cout << "instruction found" << endl;
                 //   r_functions(line, instruct);
                    break;
                case 'u':
                    cout << "instruction found" << endl;

                    break;
                case 's':
                    cout << "instruction found" << endl;

                    break;
                case 'b':
                    cout << "instruction found" << endl;

                    break;
                case 'j':
                    cout << "instruction found" << endl;

                    break;
                default:
                    cout << "instruction not recognized" << endl;
                    break;
                }
            }
        }
    };

    void r_functions(string line)
    {
        stringstream isstring;
        string instruct = "";
        isstring.clear();
        isstring.str(line);
        isstring >> instruct;
        if (!instruction_struct.count(instruct))
        {
            isstring >> instruct;
        }
    }


private:
    int programCounter;
    unordered_map<int, int> memory;                                              // Memory contents, using an unordered map, the first parameter is the address 'n second is the content
    unordered_map<string, int> registers;                                        // Register contents
    unordered_map<string, string> register_name;                                 // an array just in case we have a register used as its name not the normal x1,2,3,.. etc
    unordered_map<string, char> instruction_struct;

    vector<string> data_preset;
    vector<string> program;

    unordered_map<int, string> programm;
    unordered_map<string, int> labels;
    int error;

};

//uint32_t
int main() {
    RiscVSimulator sim;
    sim.preset( "C:\\Users\\DELL\\Desktop\\RARS_simulator\\simulator\\txt_files\\data.txt", "C:\\Users\\DELL\\Desktop\\RARS_simulator\\simulator\\txt_files\\program.txt");
    //sim.execute();
    return 0;
}




