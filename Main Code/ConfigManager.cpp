#include "ConfigManager.h"
#include <string>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <cstring>
#include <stdlib.h>
#include <iostream>

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
    ifstream configFile;
    configFile.open(path.c_str());
    cout << path << endl;
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
        cout<<configline.type<<" "<<configline.value<<endl;
		//A bunch of if statements for each configuration item
		if (configline.type.compare("ping_control") == 0)// 0 means it is equal
		{
			ping_control = atoi(configline.value.c_str());
		}
		else if (configline.type.compare("stop_pin") == 0)
		{
			stop_pin = atoi(configline.value.c_str());
		}
		else if (configline.type.compare("ping_tolerance") == 0)
		{
			ping_tolerance = atol(configline.value.c_str());
		}
		else if (configline.type.compare("ping_run_time") == 0)
		{
			ping_run_time = atol(configline.value.c_str());
		}
		else if (configline.type.compare("temp_humid_pin") == 0)
		{
			temp_humid_pin = atoi(configline.value.c_str());
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
			relay_minimum_temperature = atol(configline.value.c_str());
		}
		else if (configline.type.compare("ir_address") == 0)
		{
			ir_address = atoi(configline.value.c_str());
		}
        else if(strstr(configline.type.c_str(), "bus_number_") != 0)
        {
           char cNum = configline.type[configline.type.size() - 1];
           //cout<<"character: "<<cNum<<endl;
           int val = atoi(&cNum);
           //cout<<"Here1: "<<val<<endl;
           busInfo[val].num = atoi(configline.value.c_str());
        }
        else if(strstr(configline.type.c_str(), "bus_shelter_id") != 0)
        {
            char cNum = configline.type[configline.type.size() - 1];
            //cout<<"character id: "<<cNum<<endl;
            int val = atoi(&cNum);
            if(val>10)
            {
                int div = val/10;
                val -= div*10;
            }
            //cout<<"Num index: "<<val<<endl;
            busInfo[val].id = configline.value.substr(1,configline.value.size()-1);
            //cout<<busInfo[val].id<<endl;
        }
		else if (configline.type.compare("monitor_enabled") == 0)
		{
			if (atoi(configline.value.c_str()) > 0)
			{
				monitor_enabled = true;
			}
			else monitor_enabled = false;
		}
		else if (configline.type.compare("control_timeout") == 0)
		{
			control_timeout = atoi(configline.value.c_str()) * 1000;
		}
		else if (configline.type.compare("bus_timeout") == 0)
		{
			bus_timeout = atoi(configline.value.c_str()) * 1000;
		}
		else if (configline.type.compare("solar_timeout") == 0)
		{
			solar_timeout = atoi(configline.value.c_str()) * 1000;
		}
		else 
		{//nothing, just the header}
			//cout << "WTF!!!!!" << endl;
		}

	}
	configFile.close();
}
