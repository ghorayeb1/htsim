#ifndef EXPORT_UTILS
#define EXPORT_UTILS

#include "HeatTransferSolver.h"
#include <string>

class ExportUtils
{
private:
	ExportUtils();
	~ExportUtils();

public:
	static void exportToCSV(HeatTransferSolver *solver, std::string series_name, std::string filename);
	static void exportToCSV(HeatTransferSolver *solver1, std::string series_name1, HeatTransferSolver *solver2, std::string series_name2, std::string filename);
};

#endif
