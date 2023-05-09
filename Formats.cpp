#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using namespace std;

//void Readfile(int line, vector<string> words); //The functions kenzy made, so they'll read each line
//words vector is the vector containing the line that we are currently reading from the file
void FindFormat(vector<string> words);

void R_Format(vector<string> words);
void I_Format(vector<string> words);
void S_Format(vector<string> words);
//...more formats

void SB_Format(vector<string> words);
void U_Format(vector<string> words);
void UJ_Format(vector<string> words);




int main()
{
	//In main file
}

void FindFormat(vector<string> words)
{
	set<string>  R_op;
	set<string>  I_op;
	set<string>  S_op;
	set<string>  SB_op;
	set<string>  U_op;
	set<string>  UJ_op;

	//R_format instructions
	R_op.insert("add"); //Arithmetic operations
	R_op.insert("addu"); // addu and subu are both unsigned 
	R_op.insert("sub");
	R_op.insert("subu");  //unsigned
	R_op.insert("mul");
	R_op.insert("div");
	R_op.insert("sll"); //Shift instructions
	R_op.insert("srl");
	R_op.insert("and"); //bitwise operations
	R_op.insert("or");
	R_op.insert("xor");
	R_op.insert("nor");

	//I format instructions
	I_op.insert("addi");
	I_op.insert("slti");
	I_op.insert("xori");
	I_op.insert("ori");
	I_op.insert("andi");
	I_op.insert("srli");
	I_op.insert("slli");
	I_op.insert("srai");
	I_op.insert("jalr");

	//S format instructions
	S_op.insert("sb");
	S_op.insert("sh");
	S_op.insert("sw");

	//SB format instructions
	SB_op.insert("beq");
	SB_op.insert("bne");
	SB_op.insert("blt");
	SB_op.insert("bge");
	SB_op.insert("bltu");
	SB_op.insert("bgeu");

	//U format instructions
	U_op.insert("lui"); //Load upper imm
	U_op.insert("auipc"); //Add upper imm to PC


	//UJ format instructions
	UJ_op.insert("jal");
	U_op.insert("j");

	if (R_op.count(words[0]))
	{
		R_Format(words);
	}
	else if (I_op.count(words[0]))
	{
		I_Format(words);
	}
	else if (S_op.count(words[0]))
	{
		S_Format(words);
	}
	else if (SB_op.count(words[0]))
	{
		SB_Format(words);
	}
	else if (U_op.count(words[0]))
	{
		U_Format(words);
	}
	else if (UJ_op.count(words[0]))
	{
		UJ_Format(words);
	}


	return;
}

void R_Format(vector<string> words)
{
	if (words[0] == "add")
	{
		int temp;
		//           0        1  2   3
		//words: instruction rd rs1 rs2
	}
	//make if conditions for each 
}

void I_Format(vector<string> words)
{

}

void S_Format(vector<string> words)
{

}


void SB_Format(vector<string> words)
{

}


void U_Format(vector<string> words)
{

}

void UJ_Format(vector<string> words)
{

}


