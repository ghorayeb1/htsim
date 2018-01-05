#include<iostream>
#include<fstream>
#include<string>

#include "SimulationConfiguration.h"
#include "ConfigurationReader.h"
#include "HeatTransferSolver.h"
#include "AnalyticSolver.h"
#include "StationarySolver.h"
#include "NonStationarySolver.h"
#include "Exportutils.h"

int runSimulation(const SimulationConfiguration *config);

int main(int argc, char** argv)
{
	int RES_OK = 0;
	if (argc == 2) {
		ConfigurationReader cnfgReader(argv[1]);
		if (!cnfgReader.parseConfiguration()) {
			const SimulationConfiguration *config = cnfgReader.getConfiguration();
			RES_OK |= runSimulation(config);
		}
		else {
			std::cout << "Error parsing configuration file." << std::endl;
		}
	}
	else {
		std::cout << "Usage: "<< argv[0] << " configfile.cfg"<<std::endl;
	}

	return RES_OK;
}

int runSimulation(const SimulationConfiguration *config)
{
	int RES_OK = 0;

	// Reference : Analytic Solution
	HeatTransferSolver *myAnalyticSolver = new AnalyticSolver(*config);
	
	myAnalyticSolver->printParams();
	myAnalyticSolver->solve();

	ExportUtils::exportToCSV(myAnalyticSolver, "exact", "analytic-result.csv");

	// Stationary Model
	HeatTransferSolver *myStationarySolver = new StationarySolver(*config);

	myStationarySolver->printParams();
	myStationarySolver->solve();

	ExportUtils::exportToCSV(myStationarySolver, "stationary", myAnalyticSolver, "exact", "stationary-result.csv");

	// Non Stationary Model
	NonStationarySolver *myNonStationarySolver = new NonStationarySolver(*config);

	myNonStationarySolver->printParams();
	myNonStationarySolver->solve();

	ExportUtils::exportToCSV(myNonStationarySolver,"non-stationary", myStationarySolver, "stationary", myAnalyticSolver, "exact", "nonstationary-result.csv");
	
	ExportUtils::exportToCSV(myNonStationarySolver, "non-stationary-discrete.csv",false);

	delete myAnalyticSolver;
	delete myStationarySolver;
	delete myNonStationarySolver;

	return RES_OK;
}