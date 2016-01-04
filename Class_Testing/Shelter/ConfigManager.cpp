#include "ConfigManager.h"
#include <string>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <cstring>
#include <stdlib.h>

using namespace std;

struct config
{
	string type, value, description;
};

ConfigManager::ConfigManager()
{
	//ReadConfigFile();
}


ConfigManager::~ConfigManager()
{
}

void ConfigManager::ReadConfigFile()
{
	//Get filepath of the configuration file
	char currentPath[FILENAME_MAX];
	getcwd(currentPath,FILENAME_MAX);
	string path(currentPath); //modified char to string
	path.append("/configuration.txt");

	//Open the configuration file
	ifstream configFile(path);
	string line;
	while (configFile.good())
	{
		getline(configFile, line);
		string token;
		config configline;
		stringstream ss(line);
		getline(ss, token, ','); //get the type
		configline.type = token;
		getline(ss, token, ','); //get the value
		configline.value = token;
		getline(ss, token, ','); //get the description
		configline.description = token;
		//A bunch of if statements for each configuration item
		if (configline.type.compare("ping_control") == 0)// 0 means it is equal
		{
			ping_ground = atoi(configline.value.c_str());
		}
		else if (configline.type.compare("ping_tolerance") == 0)
		{
			ping_power = atol(configline.value.c_str());
		}
		else if (configline.type.compare("ping_run_time") == 0)
		{
			ping_control = atol(configline.value.c_str());
		}
		else if (configline.type.compare("temp_humid_pin") == 0)
		{
			ping_distance_tolerance = atoi(configline.value.c_str());
		}
		else if (configline.type.compare("relay_control")==0)
		{
			relay_control = atoi(configline.value.c_str());
		}
		else if (configline.type.compare("relay_idle_temperature") == 0)
		{
			relay_idle_temperature = atol(configline.value.c_str());
		}
		else if (configline.type.compare("relay_minimum_temperature") == 0)
		{
			relay_env_min_temperature = atol(configline.value.c_str());
		}

		/*
		//bus id section
		else if (configline.type.find("bus_id_")!= string::npos)
		{
			for (int i = 0; i < 10; i++)
			{
				string id_num_str = to_string(i);
				if (configline.type.find(id_num_str) != string::npos)
				{
					bus[i].id = atoi(configline.value.c_str());
				}
			}
		}
		//bus number in each bus 
		else if (configline.type.find("bus_number_") != string::npos)
		{
			for (int i = 0; i < 10; i++)
			{
				string id_num_str = to_string(i);
				if (configline.type.find(id_num_str) != string::npos)
				{
					bus[i].number = atoi(configline.value.c_str());
				}
			}
		}*/
		/*
			ADD MORE OF THE CONFIGURATIONS HERE
		*/
		else 
		{//nothing, just the header}
			//cout << "WTF!!!!!" << endl;
		}

	}
	configFile.close();
}