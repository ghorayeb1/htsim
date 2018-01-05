#ifndef NONSTATIONARY_SOLVER
#define NONSTATIONARY_SOLVER

#include "HeatTransferSolver.h"

class NonStationarySolver :
	public HeatTransferSolver
{
public:
	NonStationarySolver(const SimulationConfiguration &cfg);
	virtual ~NonStationarySolver();
	virtual void solve();

protected:
	void initAXF();
	void calculateMatrixLU();
	void calculateLYF();
	void calculateUXY();

	void allocateStorage();
	
	bool isAllocated;
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