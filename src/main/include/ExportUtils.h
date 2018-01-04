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
};

#endif
