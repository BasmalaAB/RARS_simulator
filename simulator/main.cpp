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
        programCounter = 0;
        registers["x0"] = 0;
        registers["x1"] = 0;
        registers["x2"] = 0;
        registers["x3"] = 0;
        registers["x4"] = 0;
        registers["x5"] = 0;
        registers["x6"] = 0;
        registers["x7"] = 0;
        registers["x8"] = 0;     //fp too, dk if we use that tho
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
                if(line[x] == ':'){                                       //keep reading unti;
                    address = word;
                    word = "";
                }else{
                    word += line[x];
                }
            }
            value = word;                                                    //after we are done, the value should be all that's left in the word

            memory[stoi(address)] = stoi(value);
        }
        for(auto x : memory){
            cout << "address: " << x.first << ", value: " << x.second << endl;
        }
    }
    void preset(string text_data, string text_program){                     //in preset we will initialize the registers and memory and read pc, then read the program
        ifstream program;
        readFile(program, text_data, data_preset);
        programCounter = stoi(data_preset[0]);
        cout << "PC: " << programCounter << endl;
        save_in_memory();
    };

private:
    int programCounter;
    unordered_map<int, int> memory;                               // Memory contents, using an unordered map, the first parameter is the address 'n second is the content
    unordered_map<string, int> registers;                               // Register contents
    unordered_map<string, string> register_name;

    vector<string> data_preset;
    vector<string> program;

};

//uint32_t
int main() {
    RiscVSimulator sim;
    sim.preset( "C:\\Users\\DELL\\Desktop\\RARS_simulator\\simulator\\txt_files\\data.txt", "C:\\Users\\DELL\\Desktop\\RARS_simulator\\simulator\\txt_files\\program.txt");
    return 0;
}




