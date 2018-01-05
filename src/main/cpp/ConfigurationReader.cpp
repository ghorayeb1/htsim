#include "ConfigurationReader.h"
#include <fstream>
#include <string>
#include <sstream>
#include <map>

ConfigurationReader::ConfigurationReader(std::string filename)
	:filename(filename),
	config(NULL)
{
}


ConfigurationReader::~ConfigurationReader()
{
	if (this->config) {
		delete this->config;
		this->config = NULL;
	}
}

int ConfigurationReader::parseConfiguration()
{
	int error = 0;
	double Lx = 0;
	double Ly = 0;
	double Lz = 0;
	int M = 0;
	double Phi = 0;
	double hc = 0;
	double Te = 0;
	double K = 0;
	double Rho = 0;
	double Cp = 0;
	int stationnary = 0;
	int TFinal = 0;
	int N = 0;
	int Mx = 0;
	int My = 0;
	int Mz = 0;
	// Open File Stream
	std::string line;
	std::ifstream cfgfile(filename);
	std::map<std::string, std::string> options;

	// Read properties
	if (cfgfile.is_open())
	{
		for (std::string line; std::getline(cfgfile, line);){
			std::istringstream iss(line);
			std::string key, value;
			
			if (std::getline(iss, key, ' ')){
				std::getline(iss, value);
				options[key] = value;
			}
		}
		// Close File
		cfgfile.close();

		// Update the Options for Lx Ly Lz
		std::istringstream lxyz(options["Lx"]);
		std::string lx_v, ly_k, ly_v, lz_k, lz_v;
		std::getline(lxyz, lx_v, ' ');
		std::getline(lxyz, ly_k, ' ');
		std::getline(lxyz, ly_v, ' ');
		std::getline(lxyz, lz_k, ' ');
		std::getline(lxyz, lz_v, ' ');
		options["Lx"] = lx_v;
		options["Ly"] = ly_v;
		options["Lz"] = lz_v;
		// Update the Options for Mx My Mz
		std::istringstream mxyz(options["Mx"]);
		std::string mx_v, my_k, my_v, mz_k, mz_v;
		std::getline(mxyz, mx_v, ' ');
		std::getline(mxyz, my_k, ' ');
		std::getline(mxyz, my_v, ' ');
		std::getline(mxyz, mz_k, ' ');
		std::getline(mxyz, mz_v, ' ');
		options["Mx"] = mx_v;
		options["My"] = my_v;
		options["Mz"] = mz_v;
		// Print Options
		std::cout << "Configuration File Verification: key value" << std::endl;
		for (std::map<std::string, std::string>::iterator it = options.begin(); it != options.end(); it++){
			std::cout << it->first << " => " << it->second << std::endl;
		}
		std::cout << "Parsing Options..." << std::endl;
		// Lx, Ly, Lz
		parseDouble(options["Lx"], Lx);
		parseDouble(options["Ly"], Ly);
		parseDouble(options["Lz"], Lz);
		// M
		parseInt(options["M"],M);
		// Phi
		parseDouble(options["Phi"],Phi);
		// hc
		parseDouble(options["hc"],hc);
		// Te
		parseDouble(options["Te"], Te);
		//K
		parseDouble(options["K"], K);
		//Rho
		parseDouble(options["Rho"], Rho);
		//Cp
		parseDouble(options["Cp"], Cp);
		// stationnary
		parseInt(options["stationnary"],stationnary);
		// TFinal
		parseInt(options["TFinal"],TFinal);
		// M
		parseInt(options["N"],N);
		// Mx, MY, Mz
		parseInt(options["Mx"],Mx);
		parseInt(options["My"],My);
		parseInt(options["Mz"],Mz);
		std::cout << "Done." << std::endl;
	}
	else {
		std::cerr << "Unable to open Configuration File." << std::endl;
		error = 10;
	}
	//Create Configuration Object
	if (!error && this->config == NULL) {
		this->config = new SimulationConfiguration(Lx, Ly, Lz, M, Phi, hc, Te, K, Rho, Cp, stationnary, TFinal, N, Mx, My, Mz);
	}

	return error;
}

void ConfigurationReader::parseInt(std::string s_value, int &i_value)
{
	std::istringstream is(s_value);
	is >> i_value;
}

void ConfigurationReader::parseDouble(std::string s_value, double &i_value)
{
	std::istringstream is(s_value);
	is >> i_value;
}