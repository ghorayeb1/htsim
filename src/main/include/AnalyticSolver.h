#ifndef ANALYTIC_SOLVER
#define ANALYTIC_SOLVER

#include "HeatTransferSolver.h"

class AnalyticSolver :
	public HeatTransferSolver
{
public:
	AnalyticSolver(const SimulationConfiguration &cfg);
	virtual ~AnalyticSolver();
	virtual void solve();

protected:
	virtual double computeAnalyticValue(int i);
};

#endif
