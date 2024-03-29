#ifndef EXPORT_UTILS
#define EXPORT_UTILS

#include "HeatTransferSolver.h"
#include "NonStationarySolver.h"
#include "TempratureInterpolator.h"
#include "TemporalTempratureInterpolator.h"
#include <string>

class ExportUtils
{
private:
	ExportUtils();
	~ExportUtils();

public:
	static void exportToCSV(HeatTransferSolver *solver, std::string series_name, std::string filename);
	static void exportToCSV(HeatTransferSolver *solver1, std::string series_name1, HeatTransferSolver *solver2, std::string series_name2, std::string filename);
	static void exportToCSV(HeatTransferSolver *solver1, std::string series_name1, HeatTransferSolver *solver2, std::string series_name2, HeatTransferSolver *solver3, std::string series_name3, std::string filename);
	static void exportToCSV(NonStationarySolver *solver, std::string filename, bool fullexport);

	static void exportToVTK(HeatTransferSolver *solver, TempratureInterpolator *interpolator, std::string solution);
	static void exportToVTK(NonStationarySolver *solver, TemporalTempratureInterpolator *interpolator, std::string solution);
};

#endif
