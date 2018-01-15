#include <algorithm>
#include <iostream>
#include <iterator>
#include <fstream>
#include <string>
#include <iomanip>
#include <utility>
#include <map>
#include <cctype>
#include <cstdlib>
#include <vector>


void run_on_data(std::map<char,int>& newMap, char* data, int datalen)
{
	int index = 0;
	while(index < datalen)
	{
		char c1 = tolower(data[index++]);
		if(newMap.count(c1) == 0)
		{
			newMap.insert(std::make_pair(c1,0));
		}else
		{
			newMap.at(c1)++;
		}
	}
}

void integrate(std::map<char,int>& lhs, std::map<char,int>& rhs)
{
	std::map<char,int>::iterator intiter = rhs.begin();
	for(;intiter != rhs.end(); ++intiter)
	{
		std::map<char,int>::iterator liter = lhs.find(intiter->first);
		if(liter == lhs.end())
		{
			lhs.insert(std::make_pair(intiter->first,intiter->second));
		}else
		{
			liter->second += intiter->second;
		}
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
			//std::cout << "last extracted " << extracted << "characters" << std::endl;

			
			//data2.assign(in_data+extracted/2,in_data+extracted+1);

			//boost::thread t1(run_on_data,boost::ref(map2),boost::ref(data2));

			run_on_data(freq_map,in_data,extracted);

			//t1.join();
			
			//integrate(freq_map,map2);

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