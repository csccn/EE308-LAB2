#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using std::string;

void Count_Keywork_Switch_Case(string inputfile,int level) {//TODO(JZ)
    std::ifstream inFile("G:\EE308\testfile.cpp", std::ios::in); //open file
	
	//Define variables and initialize value
	string x;
	string y;
	int Keyword_num = 0;
	int Count = 0;
	int Switch_Loop = 0;	
	string Case_Num = "";
	int Case_Number = 0;
	
	string keyword[32] = {"auto","break","case","char","const","continue","default","do",
			                "double","else","enum","extern","float","for","goto","if",
			                "int","long","register","return","short","signed","sizeof","static",
			                "struct","switch","typedef","union","unsigned","void","volatile","while"};

	while (inFile>>x) {
		y = "";
		
		for (int i = 0;i < x.length(); i++) {
			if (x[i] >= 'A' && x[i] <= 'z')
			{
				y += x[i];
			}
		}
			
		for (int a = 0; a < 32; a++) {
			if (keyword[a] == y) {
					
				Keyword_num += 1;
			}
		}
		
		if (y == "switch") {
			Count += 1;
			Switch_Loop += 1;
		}
		
		if (Switch_Loop > 0 && y == "case") {
			Case_Number += 1;
		}
		
		if (Switch_Loop > 0 && y == "default") {
			Case_Num += std::to_string(Case_Number);
			Case_Number = 0;
			Switch_Loop = 0;
		}
			
		
	}
	inFile.close();
	if (level == 1) {
		std::cout << "total num: " << Keyword_num << std::endl;
	}
	if (level >=2) {
		std::cout << "total num: " << Keyword_num << std::endl;
		std::cout << "switch num:" << Count << std::endl;
		std::cout << "case num:";
		for (int b = 0; b < Count; b++) {
			std::cout << Case_Num[b] << " ";
		}
		std::cout << std::endl;
	}
	
}


void Count_If_Elseif(string inputfile, int level) {
	std::ifstream inFile(inputfile, std::ios::in);
	string x;
	string z;
	std::vector<string> line;
	int Sec_else = 0;
	int Sec_elseif = 0;
	int Count_Ifelse = 0;
	int Count_Elseif = 0;
	while (getline(inFile, x)) {

		for (int i = 0; i < x.length(); i++) {
			if (x[i] >= 'A' && x[i] <= 'z')
			{
				if (x[i] == 'e' || x[i] == 'f' || x[i] == 'l' || x[i] == 's' || x[i] == 'i')
				{
					z += x[i];
				}
			}

		}
		
		if (z.length() >= 2 && z.substr(0, 2) == "if") {
			line.push_back(z.substr(0, 2));

		}
		
		if (z.length() >= 2 && z.length() <= 6 && z.substr(0, 4) == "else") {
			line.push_back(z.substr(0, 4));

		}
		
		if (z.length() >= 6 && z.substr(0, 6) == "elseif") {
			line.push_back(z.substr(0, 6));

		}

		z = "";
	}
	inFile.close();
	
	for (int a = 0; a < line.size(); a++) {//if else elseif 
		if (line[a] == "if") {
			Sec_else += 1;
			Sec_elseif += 1;

		}
		
		if (line[a] == "else" && Sec_else > 0) {
			Count_Ifelse += 1;
			Sec_else -= 1;
			Sec_elseif -= 1;
		}
		
		if (line[a] == "elseif" && Sec_elseif > 0) {
			Sec_else -= 1;
			Sec_elseif -= 1;
			Count_Elseif += 1;
		}


	}
	
	if (level == 3) {
		std::cout << "if-else num:" << Count_Ifelse << std::endl;
	}
	
	if (level == 4) {
		std::cout << "if-else num:" << Count_Ifelse << std::endl;
		std::cout << "if-elseif-else num:" << Count_Elseif << std::endl;
	}
	

}

	
	
int main() {
	string filename;
	int level;
	std::cout << "please enter the name of file" << std::endl;
	std::cin >> filename;
	std::cout << "please enter the level" << std::endl;
	std::cin >> level;
	if (level <= 2) {
		Count_Keywork_Switch_Case(filename, level);
	}
	if (level > 2) {
		Count_Keywork_Switch_Case(filename, level);
		Count_If_Elseif(filename, level);
	}
}
