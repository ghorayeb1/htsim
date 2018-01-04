#include "StationarySolver.h"

#include <iostream>

StationarySolver::StationarySolver(const SimulationConfiguration &cfg)
	:HeatTransferSolver(cfg)
{
	initAXF();
}


StationarySolver::~StationarySolver()
{
	if (a != NULL) delete a;
	if (b != NULL) delete b;
	if (c != NULL) delete c;
	if (T != NULL) delete T;
	if (F != NULL) delete F;
	if (Y != NULL) delete Y;
	if (X != NULL) delete X;
	if (bL != NULL) delete bL;
	if (cU != NULL) delete cU;
}

void StationarySolver::solve()
{
	std::cout << "[Stationary solver]" << std::endl;

	calculateMatrixLU();
	calculateLYF();
	calculateUXY();

	for (int i = 0; i < domainSize; i++)
	{
		temperature[i] = X[i];
	}
}

void StationarySolver::initAXF()
{
	std::cout << "initAXF" << std::endl;
	int M = cfg->M;
	double Te = cfg->Te;
	double Phi = cfg->Phi;
	double h = cfg->Lx / (double)cfg->M;
	double k = cfg->K;
	double p = 2 * (cfg->Lx + cfg->Ly);
	double S = cfg->Ly * cfg->Lz;
	double kh = k / (double)h;
	double kh2 = k / (double)(h*h);
	double hcpS = cfg->hc * p / (double)S;

	this->T = new double[domainSize];
	this->F = new double[domainSize];
	this->X = new double[domainSize];
	this->Y = new double[domainSize];
	this->a = new double[domainSize];
	this->b = new double[domainSize];
	this->c = new double[domainSize];
	this->bL = new double[domainSize];
	this->cU = new double[domainSize];

	for (int i = 0; i < domainSize; i++)
	{
		a[i] = -kh2;
	}
	a[0] = 0;
	a[M] = -kh;

	for (int i = 0; i < domainSize; i++)
	{
		b[i] = 2*kh2 + hcpS;
	}
	b[0] = kh;
	b[M] = kh;

	for (int i = 0; i < domainSize; i++)
	{
		c[i] = -kh2;
	}
	c[0] = -kh;
	c[M] = 0;

	for (int i = 0; i < domainSize; i++)
	{
		F[i] = hcpS * Te;
	}
	F[0] = Phi;
	F[M] = 0;
}

void StationarySolver::calculateMatrixLU()
{
	std::cout << "calculateMatrixLU" << std::endl;
	int M = cfg->M;

	bL[0] = b[0];
	cU[0] = c[0]/(double)bL[0];
	for (int i = 1; i < domainSize-1; i++)
	{
		bL[i] = b[i] - a[i] * cU[i-1];
		cU[i] = c[i]/bL[i];
	}
	bL[M] = b[M]-a[M]*cU[M-1];
}

void StationarySolver::calculateLYF()
{
	std::cout << "calculateLYF" << std::endl;
	Y[0] = F[0] / bL[0];
	for (int i = 1; i < domainSize; i++)
	{
		Y[i] = (F[i]  - a[i] *Y[i-1])/ bL[i];
	}
}

void StationarySolver::calculateUXY()
{
	std::cout << "calculateUXY" << std::endl;
	int M = cfg->M;
	X[M] = Y[M];

	for (int i = M-1; i >= 0; i--)
	{
		X[i] = Y[i] - cU[i] * X[i+1];
	}
}