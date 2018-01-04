#ifndef STATIONARY_SOLVER
#define STATIONARY_SOLVER

#include "HeatTransferSolver.h"

class StationarySolver :
	public HeatTransferSolver
{
public:
	StationarySolver(const SimulationConfiguration &cfg);
	virtual ~StationarySolver();

	virtual void solve();

protected:
	void initAXF();
	void calculateMatrixLU();
	void calculateLYF();
	void calculateUXY();

	double *a;
	double *b;
	double *c;
	double *T;
	double *F;
	double *Y;
	double *X;

	double *bL;
	double *cU;
};

#endif