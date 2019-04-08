#include <iostream>
#include <fstream>
#include <time.h>
#include <unistd.h>
#include <sstream>
#include <vector>

const int secondLoop = 1000;
double memTotal = 0;
double memFree = 0;
std::vector<std::string> words;
double userTime, kernelTime, idleTime, sumTime;
int previousSwitch = 0;
int currentSwitch = 0;
int previousProcesses = 0;
int currentProcesses = 0;

unsigned int intFromString(std::string str)
{
	unsigned int result = 0;
	for (int i = 0; i < str.size(); i++)
	{
		if(str[i] >= '0' and str[i] <= '9')
		{
			result *= 10;
			result += str[i] - 48;
		}
	}

	return result;
}

int main()
{
	std::fstream fs;
	std::fstream fs1;
       	std::string keys;	

	while(true)
	{
		fs.open("/proc/meminfo", std::fstream::in);
		fs1.open("/proc/stat", std::fstream::in);

		while(getline(fs, keys))
		{
			if(keys.find("MemTotal") != std::string::npos)
				memTotal = intFromString(keys);		
			if(keys.find("MemFree") != std::string::npos)
			{
				memFree = intFromString(keys);
				break;
			}
		}	

		while(getline(fs1,keys))
		{
			if(keys.find("cpu0") != std::string::npos)
			{
				//Iterate over the words of a string
				std::string tmp;
				std::stringstream stream(keys);
				
				while(stream >> tmp)
				{
					words.push_back(tmp);
				}	
			}

			if(keys.find("ctxt") != std::string::npos)
				currentSwitch = intFromString(keys);		

			if(keys.find("processes") != std::string::npos)
				currentProcesses = intFromString(keys);
		}	

		std::cout << "Porcentaje Memoria Libre: " << float(memFree*100/memTotal) << "%" << std::endl;		
		fs.close();

		userTime = stoi(words[1]); kernelTime = stoi(words[3]); idleTime = stoi(words[4]);
		sumTime = userTime + kernelTime + idleTime;	
		words.clear();
		
		std::cout << "User Time: " << (userTime*100/sumTime) << "%" << std::endl;
		std::cout << "Kernel Time: " << (kernelTime*100/sumTime) << "%" << std::endl;
		std::cout << "Idle Time: " << (idleTime*100/sumTime) << "%" << std::endl;

		std::cout << "Switches since last second: " << currentSwitch - previousSwitch << std::endl;
		previousSwitch = currentSwitch;

		std::cout << "Processes forked since last second: " << currentProcesses - previousProcesses << std::endl;
		previousProcesses = currentProcesses;
		std::cout << "-----------------------------" << std::endl;

		fs1.close();
		usleep(secondLoop*secondLoop);
	}

}

