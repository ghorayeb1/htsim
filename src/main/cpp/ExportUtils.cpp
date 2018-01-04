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