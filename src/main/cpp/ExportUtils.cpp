#include "ExportUtils.h"

#include <fstream>
#include <iostream>

ExportUtils::ExportUtils()
{
}


ExportUtils::~ExportUtils()
{
}

void ExportUtils::exportToCSV(HeatTransferSolver *solver, std::string series_name, std::string filename)
{
	std::ofstream out(filename);
	out << "x" << "," << series_name << std::endl;
	for (int i = 0; i < solver->domainSize; i++)
	{
		double x = i * solver->step_size;
		out << x << "," << solver->temperature[i] << std::endl;
	}
	out.close();
}

void ExportUtils::exportToCSV(HeatTransferSolver *solver1, std::string series_name1, HeatTransferSolver *solver2, std::string series_name2, std::string filename)
{
	std::ofstream out(filename);
	out << "x" << "," << series_name1 << "," << series_name2 << std::endl;
	for (int i = 0; i < solver1->domainSize; i++)
	{
		double x = i * solver1->step_size;
		out << x << "," << solver1->temperature[i] << "," << solver2->temperature[i] << std::endl;
	}
	out.close();
}