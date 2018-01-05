#include "ExportUtils.h"

#include <fstream>
#include <iostream>
#include <iomanip>

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
		out << x;
		out << "," << std::fixed << std::setprecision(12) << solver->temperature[i];
		out << std::endl;
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
		out << x;
		out << "," << std::fixed << std::setprecision(12) << solver1->temperature[i];
		out << "," << std::fixed << std::setprecision(12) << solver2->temperature[i];
		out << std::endl;
	}
	out.close();
}

void ExportUtils::exportToCSV(HeatTransferSolver *solver1, std::string series_name1, HeatTransferSolver *solver2, std::string series_name2, HeatTransferSolver *solver3, std::string series_name3, std::string filename)
{
	std::ofstream out(filename);
	out << "x" << "," << series_name1 << "," << series_name2 << "," << series_name3 << std::endl;
	for (int i = 0; i < solver1->domainSize; i++)
	{
		double x = i * solver1->step_size;
		out << x;
		out << "," << std::fixed << std::setprecision(12) << solver1->temperature[i];
		out << "," << std::fixed << std::setprecision(12) << solver2->temperature[i];
		out << "," << std::fixed << std::setprecision(12) << solver3->temperature[i];
		out << std::endl;
	}
	out.close();
}