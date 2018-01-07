#ifndef HEAT_TRANSFER_SOLVER
#define HEAT_TRANSFER_SOLVER

#include "SimulationConfiguration.h"

class HeatTransferSolver
{
public:
	HeatTransferSolver(const SimulationConfiguration &cfg);
	virtual ~HeatTransferSolver();

	virtual void solve() = 0;

	void printParams();

protected:
	friend class ExportUtils;
	friend class TempratureInterpolator;

	SimulationConfiguration *cfg;

	int domainSize;
	double step_size;
	double *temperature;
};

#endif
