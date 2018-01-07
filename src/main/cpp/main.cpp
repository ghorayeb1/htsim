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
#include "TempratureInterpolator.h"
#include "TemporalTempratureInterpolator.h"

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
	TempratureInterpolator * interpolator0 = new TempratureInterpolator(myAnalyticSolver);
	
	std::cout << "[Analytic solver]:Parameters" << std::endl;
	myAnalyticSolver->printParams();
	std::cout << "[Analytic solver]:Start..." << std::endl;
	myAnalyticSolver->solve();
	std::cout << "[Analytic solver]:End." << std::endl;

	std::cout << "[Analytic solver]:Export to CSV <analytic-result.csv> Start..." << std::endl;
	ExportUtils::exportToCSV(myAnalyticSolver, "exact", "analytic-result.csv");
	std::cout << "[Analytic solver]:Export to CSV End." << std::endl;

	std::cout << "[Analytic solver]:Interpolate Start..." << std::endl;
	interpolator0->interpolate();
	std::cout << "[Analytic solver]:Interpolate End." << std::endl;

	std::cout << "[Analytic solver]:Export to VTK <analytic.vtk> Start..." << std::endl;
	ExportUtils::exportToVTK(myAnalyticSolver, interpolator0, "analytic");
	std::cout << "[Analytic solver]:Export to VTK End." << std::endl;

	if (config->getStationnary() == 1){
		// Stationary Model
		HeatTransferSolver *myStationarySolver = new StationarySolver(*config);
		TempratureInterpolator * interpolator1 = new TempratureInterpolator(myStationarySolver);

		std::cout << "[Stationary solver]:Parameters" << std::endl;
		myStationarySolver->printParams();
		std::cout << "[Stationary solver]:Start..." << std::endl;
		myStationarySolver->solve();
		std::cout << "[Stationary solver]:End." << std::endl;

		std::cout << "[Stationary solver]:Export to CSV <stationary-result.csv> Start..." << std::endl;
		ExportUtils::exportToCSV(myStationarySolver, "stationary", myAnalyticSolver, "exact", "stationary-result.csv");
		std::cout << "[Stationary solver]:Export to CSV End." << std::endl;

		std::cout << "[Stationary solver]:Interpolate Start..." << std::endl;
		interpolator1->interpolate();
		std::cout << "[Stationary solver]:Interpolate End." << std::endl;

		std::cout << "[Stationary solver]:Export to VTK <stationary.vtk> Start..." << std::endl;
		ExportUtils::exportToVTK(myStationarySolver, interpolator1,"stationary");
		std::cout << "[Stationary solver]:Export to VTK End." << std::endl;

		delete myStationarySolver;
		delete interpolator1;
	}
	else{
		// Non Stationary Model
		NonStationarySolver *myNonStationarySolver = new NonStationarySolver(*config);
		TemporalTempratureInterpolator * interpolator2 = new TemporalTempratureInterpolator(myNonStationarySolver);

		std::cout << "[Non Stationary solver]:Parameters" << std::endl;
		myNonStationarySolver->printParams();
		std::cout << "[Non Stationary solver]:Start..." << std::endl;
		myNonStationarySolver->solve();
		std::cout << "[Non Stationary solver]:End." << std::endl;

		std::cout << "[Non Stationary solver]:Export to CSV <nonstationary-result.csv> Start..." << std::endl;
		ExportUtils::exportToCSV(myNonStationarySolver, "non-stationary", myAnalyticSolver, "exact", "nonstationary-result.csv");
		std::cout << "[Non Stationary solver]:Export to CSV End." << std::endl;

		
		if (config->getExportDiscretForFullPositions() == 0){
			std::cout << "[Non Stationary solver]:Export to CSV <non-stationary-discrete-partial-positions.csv> Start..." << std::endl;
			ExportUtils::exportToCSV(myNonStationarySolver, "non-stationary-discrete-partial-positions.csv", false);
			std::cout << "[Non Stationary solver]:Export to CSV End." << std::endl;
		}
		else{
			std::cout << "[Non Stationary solver]:Export to CSV <non-stationary-discrete-all-positions.csv> Start..." << std::endl;
			ExportUtils::exportToCSV(myNonStationarySolver, "non-stationary-discrete-all-positions.csv", true);
			std::cout << "[Non Stationary solver]:Export to CSV End." << std::endl;
		}
		
		std::cout << "[Non Stationary solver]:Interpolate Start..." << std::endl;
		interpolator2->interpolate();
		std::cout << "[Non Stationary solver]:Interpolate End." << std::endl;

		std::cout << "[Non Stationary solver]:Export to VTK <non-stationary.{i}.vtk> Start..." << std::endl;
		ExportUtils::exportToVTK(myNonStationarySolver, interpolator2, "non-stationary");
		std::cout << "[Non Stationary solver]:Export to VTK End." << std::endl;

		delete interpolator2;
		delete myNonStationarySolver;
	}

	delete myAnalyticSolver;
	delete interpolator0;
	return RES_OK;
}