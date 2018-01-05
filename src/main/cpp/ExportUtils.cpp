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

void ExportUtils::exportToCSV(NonStationarySolver *solver, std::string filename, bool fullexport)
{
	int period = 10; // export T for every 10 seconds
	int selected_positions[3];

	std::ofstream out(filename);

	if (fullexport){
		out << "x";
		for (int n = 0; n < solver->time_steps_nbr; n++)
		{
			if (n % period == 0){
				out << "," << "t" << n;
			}
		}
		out << std::endl;
		out.flush();

		for (int i = 0; i < solver->domainSize; i++)
		{
			double x = i * solver->step_size;
			out << x;
			for (int n = 0; n < solver->time_steps_nbr; n++)
			{
				if (n % period == 0)
					out << "," << std::fixed << std::setprecision(12) << solver->discretTemprature[n * solver->domainSize + i];
			}

			out << std::endl;
			out.flush();
		}
	}
	else{
		selected_positions[0] = 0;
		selected_positions[1] = solver->domainSize / 2;
		selected_positions[2] = solver->domainSize - 1;

		out << "time" << "," << "x0" << "," << "xM/2" << "," << "xM" << "," <<std::endl;
		out.flush();

		for (int n = 0; n < solver->time_steps_nbr; n++)
		{
			if (n % period == 0){
				out << std::fixed << std::setprecision(6) << n * solver->time_Step;
				for (int i = 0; i < 3; i++)
				{
					out << "," << std::fixed << std::setprecision(12) << solver->discretTemprature[n * solver->domainSize + selected_positions[i]];
				}
				out << std::endl;
				out.flush();
			}
		}
	}
	out.close();
}