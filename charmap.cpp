#include <iostream>
#include <iterator>
#include <fstream>
#include <string>
#include <map>
#include <cctype>
#include <cstdlib>


void run_on_data(std::map<char,int>& newMap, char* data, int datalen)
{
	int index = 0;
	while(index < datalen)
	{
		char c1 = tolower(data[index++]);
		newMap[c1]++;
	}
}

int main()
{

	std::fstream reader("autosave.ck2",std::ios::in);
	std::map<char, int> freq_map;

	if(!reader.is_open())
	{
		std::cout << "failed to open autosave.ck2" << std::endl;
		return EXIT_FAILURE;
	}else
	{
		const int MEMLEN = 256*1024;
		char* in_data = new char[MEMLEN+1];

		do
		{
			reader.read(in_data,MEMLEN);
			
			int extracted = reader.gcount();

			run_on_data(freq_map,in_data,extracted);

		}while(reader.good());

		reader.close();

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