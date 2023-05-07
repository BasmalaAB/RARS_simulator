#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<fstream>
#include<algorithm>
using namespace std;
uint32_t regs[32]; // unsigned 32 bit  int 
const int mem_size = 2048;
uint32_t sram[2048];
int num = 0;
string dectobin(int num, int length) {
	bool flag = (num < 0);
	if (flag)
		num *= -1;
	string s;
	while (num) {
		s = to_string(num % 2) + s;
		num /= 2;
	}
	string prefix(length - s.size(), '0');
	if (!flag)
		return prefix + s;
	string str = prefix + s;
	for (int i = 0; i < str.size(); i++)
		str[i] = str[i] == '0' ? '1' : '0';
	for (int i = str.size() - 1; i >= 0; i--) {
		if (str[i] == '1')
			str[i] = '0';
		else {
			str[i] = '1';
			break;
		}
	}
	return str;
}//convert decimal to binary 
//return string containing the binary value of the input
// if the integer is negative it gets its 2's complement of the binary string
// also, it add  leading zero if needed
