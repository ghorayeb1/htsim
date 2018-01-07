#include "AnalyticSolver.h"

#include <iostream>
#include <cmath>

AnalyticSolver::AnalyticSolver(const SimulationConfiguration &cfg)
	:HeatTransferSolver(cfg)
{
}


AnalyticSolver::~AnalyticSolver()
{
}

void AnalyticSolver::solve()
{
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
	double sqrt_a = (double)sqrt(a);
	double sqrt_a_lx = sqrt_a * cfg->Lx;
	double h = cfg->Lx / (double)cfg->M;
	double x = i * h;
	double X1 = ((double)cosh(sqrt_a_lx) / (double)(sqrt_a * (double)sinh(sqrt_a_lx)));
	double X2 = ((double)cosh(sqrt_a * (cfg->Lx - x))) / (double)((double)cosh(sqrt_a_lx));

	temprature_exact = cfg->Te + cfg->Phi * X1 * X2 / (double)cfg->K;
	return temprature_exact;
}