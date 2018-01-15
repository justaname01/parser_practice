/* This is the first analyzer: a simple character counter.
 * It uses an std::map to order the characters and then reports the count of each
 */

//includes
#include <iostream>
#include <iterator>
#include <fstream>
#include <string>
#include <map>
#include <cctype>
#include <cstdlib>

//prototypes
void run_on_data(std::map<char,int>&, char*, int); //It does not make sense to me to *not* specify the type in the diamond brackets
void run_reader(std::fstream&,std::map<char,int>&);
void prompt_input(std::string&);

//while I could easily contain the entire program in main(), I like the modularity of more functions better
int main()
{
	std::string file_name;
	prompt_input(file_name);
	
	std::fstream reader(file_name,std::ios::in);

	if(!reader.is_open())
	{
		std::cout << "failed to open " << file_name << "." << std::endl;
		return EXIT_FAILURE;
	}else
	{
		std::map<char,int> freq_map;
		
		run_reader(reader,freq_map);
		
		reader.close(); //run_reader does not affect the reader object by design

		std::fstream writer("frequencies.txt",std::ios::out);
		if(writer.is_open())
		{
			std::map<char,int>::iterator mapiter = freq_map.begin();
			std::map<char,int>::iterator mapender = freq_map.end();
			for(; mapiter != mapender; ++mapiter)
			{
				writer << mapiter->first << " = " << mapiter->second << std::endl;
			}
			writer.close();
			return EXIT_SUCCESS;
		}else
		{
			std::cout << "ERROR: FAILED TO OPEN OUTPUT FILE" << std::endl;
			return EXIT_FAILURE;
		}
	}
}


void prompt_input(std::string& file_name)
{
	std::cout << "Please enter the name of the input file!" << std::endl;
	std::cout << "==> ";
	
	getline(cin,file_name);
}

void run_on_data(std::map<char,int>& newMap, char* data, int datalen)
{
	int index = 0;
	while(index < datalen)
	{
		char c1 = tolower(data[index++]);
		newMap[c1]++;
		
	}
}

//as the name says. read the file, process and then return. BUT DON'T CLOSE THE STREAM
void run_reader(std::fstream& reader, std::map<char,int>& stor)
{
	const int MEMLEN = 256*1024;
	char* in_data = new char[MEMLEN+1];

	do
	{
		reader.read(in_data,MEMLEN);

		int extracted = reader.gcount();
		//std::cout << "last extracted " << extracted << "characters" << std::endl;
		
		run_on_data(freq_map,in_data,extracted);
	}while(reader.good());
	
	//not closing the stream because I don't like it when people hide rather important steps inside function calls
	
	delete in_data;
}
