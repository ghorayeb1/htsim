#include "AnalyticSolver.h"

#include <iostream>
AnalyticSolver::AnalyticSolver(const SimulationConfiguration &cfg)
	:HeatTransferSolver(cfg)
{
}


AnalyticSolver::~AnalyticSolver()
{
}

void AnalyticSolver::solve()
{
	std::cout << "[Analytic solver]" <<std::endl;
	for (int i = 0; i < domainSize; i++)
	{
		temperature[i] = computeAnalyticValue(i);
	}
}

inline double AnalyticSolver::computeAnalyticValue(int i)
{
	double temprature_exact = 0;
	double p = 2 * (cfg->Lx + cfg->Ly);
	double S = cfg->Ly * cfg->Lz;
	double a = (cfg->hc * p) / (double)(cfg->K * S);
	double sqrt_a = sqrt(a);
	double sqrt_a_lx = sqrt_a * cfg->Lx;
	double h = cfg->Lx / (double)cfg->M;
	double x = i * h;
	double X1 = (cosh(sqrt_a_lx) / (double)(sqrt_a * sinh(sqrt_a_lx)));
	double X2 = (cosh(sqrt_a * (cfg->Lx - x))) / (double)(cosh(sqrt_a_lx));

	temprature_exact = cfg->Te + ((cfg->Phi) / (double)(cfg->K)) * X1 * X2;
	return temprature_exact;
}