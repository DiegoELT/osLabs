#include <fstream>
#include <iostream>
#include <string>

int main()
{
	std::fstream fs;
	fs.open("/proc/cpuinfo", std::fstream::in);
	//Opening the cpuinfo file
	
	std::string keys;
	while (getline(fs, keys))
	{
		if (keys.find("model name") != std::string::npos)
		{
			std::size_t pos = keys.find(":");
			std::cout << keys.substr(pos+2) << std::endl;
			break;
		}
	}
	//Until it finds model name. Then it reads the position of the colon and prints the rest.
	
	fs.close();

	fs.open("/proc/meminfo", std::fstream::in);
	while (getline(fs, keys))
	{
		if (keys.find("MemTotal") != std::string::npos)
		{
			std::size_t pos = keys.find(":");
			std::cout << keys.substr(pos+2) << std::endl;
			break;
		}
	}

	fs.close();

	fs.open("/proc/version", std::fstream::in);
	while(getline(fs,keys))
	{
		std::size_t pos = keys.find("#");
		std::cout << keys.substr(0,pos) << std::endl;
	}

	fs.close();

	fs.open("/proc/uptime", std::fstream::in);

	while(getline(fs,keys))
	{
		std::size_t pos = keys.find(" ");
		std::cout << keys.substr(0,pos) << " seconds." << std::endl;
	}

}
