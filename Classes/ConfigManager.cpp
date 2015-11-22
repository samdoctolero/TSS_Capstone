#include "ConfigManager.h"
#include <string.h>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <stdio.h>
#include <iostream>

using namespace std;

struct config
{
	string type, value, description;
};

ConfigManager::ConfigManager()
{
	ReadConfigFile();
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
	path.append("\configuration.txt");

	//Open the configuration file
	ifstream configFile(path);
	string line;
	while (getline(configFile, line))
	{
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
		if (configline.type.compare("ping_ground") == 0)// 0 means it is equal
		{
			ping_ground = stoi(configline.value);
		}
		else if (configline.type.compare("ping_pwr") == 0)
		{
			ping_power = stoi(configline.value);
		}
		else if (configline.type.compare("ping_control") == 0)
		{
			ping_control = stoi(configline.value);
		}
		else if (configline.type.compare("ping_distance_tolerance") == 0)
		{
			ping_distance_tolerance = stod(configline.value);
		}
		else if (configline.type.compare("relay_ground") == 0)
		{
			relay_ground = stoi(configline.value);
		}
		else if (configline.type.compare("relay_control")==0)
		{
			relay_control = stoi(configline.value);
		}
		else if (configline.type.compare("relay_idle_temperature") == 0)
		{
			relay_idle_temperature = stod(configline.value);
		}
		else if (configline.type.compare("relay_env_min_temperature") == 0)
		{
			relay_env_min_temperature = stod(configline.value);
		}
		//bus id section
		else if (configline.type.find("bus_id_")!= string::npos)
		{
			for (int i = 0; i < DEFAULT_NUM_BUS; i++)
			{
				string id_num_str = to_string(i);
				if (configline.type.find(id_num_str) != string::npos)
				{
					bus[i].id = stoi(configline.value);
				}
			}
		}
		//bus number in each bus 
		else if (configline.type.find("bus_number_") != string::npos)
		{
			for (int i = 0; i < DEFAULT_NUM_BUS; i++)
			{
				string id_num_str = to_string(i);
				if (configline.type.find(id_num_str) != string::npos)
				{
					bus[i].number = stoi(configline.value);
				}
			}
		}
		/*
			ADD MORE OF THE CONFIGURATIONS HERE
		*/
		else {//nothing, just the header}
	}
}