#ifndef CONFIGURATION_READER
#define CONFIGURATION_READER

#include<iostream>
#include "SimulationConfiguration.h"

class ConfigurationReader
{
public:
	ConfigurationReader(std::string filename);
	~ConfigurationReader();

	int parseConfiguration();
	const SimulationConfiguration *getConfiguration() { return this->config; }
protected:
	void parseInt(std::string s_value, int &i_value);
	void parseDouble(std::string s_value, double &i_value);
private:
	std::string filename;
	SimulationConfiguration *config;
};

#endif



