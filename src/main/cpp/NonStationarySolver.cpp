#include "NonStationarySolver.h"
#include <iostream>

NonStationarySolver::NonStationarySolver(const SimulationConfiguration &cfg)
	:HeatTransferSolver(cfg)
	, isAllocated(false)
	, time_steps_nbr(cfg.N)
	, time_Step(cfg.TFinal / (double) cfg.N)
{
	allocateStorage();
	discretTemprature = new double[this->cfg->N * domainSize];
}


NonStationarySolver::~NonStationarySolver()
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

	if (discretTemprature != NULL) delete discretTemprature;
}

void NonStationarySolver::solve()
{
	// n== 0
	// init T0
	double Te = cfg->Te;
	for (int i = 0; i < domainSize; i++)
	{
		temperature[i] = Te;
		discretTemprature[i] = Te;
	}
	int N = this->cfg->N;
	int ConstantPhi = this->cfg->ConstantPhi;
	bool zeroPhi = false;
	for (int n = 1; n < N; n++)
	{
		if ( ConstantPhi == 0 && (((int)(n*time_Step) % 30) == 0)) zeroPhi = !zeroPhi;
		initAXF(zeroPhi);
		calculateMatrixLU();
		calculateLYF();
		calculateUXY();
		// Tn = Tn+1
		for (int i = 0; i < domainSize; i++)
		{
			temperature[i] = X[i];
			discretTemprature[n*domainSize + i] = temperature[i];
		}
	}

}

void NonStationarySolver::allocateStorage()
{
	if (!isAllocated){
		this->T = new double[domainSize];
		this->F = new double[domainSize];
		this->X = new double[domainSize];
		this->Y = new double[domainSize];
		this->a = new double[domainSize];
		this->b = new double[domainSize];
		this->c = new double[domainSize];
		this->bL = new double[domainSize];
		this->cU = new double[domainSize];
	}
	isAllocated = true;
}

void NonStationarySolver::initAXF(bool zeroPhi)
{
	int M = cfg->M;
	double Te = cfg->Te;
	double Phi = zeroPhi? 0: cfg->Phi;
	double h = cfg->Lx / (double)cfg->M;
	double k = cfg->K;
	double p = 2 * (cfg->Lx + cfg->Ly);
	double S = cfg->Ly * cfg->Lz;
	double kh = k / (double)h;
	double kh2 = k / (double)(h*h);
	double hcpS = cfg->hc * p / (double)S;
	
	double Rho = cfg->Rho;
	double Cp = cfg->Cp;
	double Dt = cfg->TFinal / (double)cfg->N;
	double RhoCp = Rho * Cp;
	double RhoCpDt = RhoCp / (double)Dt;

	for (int i = 0; i < domainSize; i++)
	{
		a[i] = -kh2;
	}
	a[0] = 0;
	a[M] = -kh;

	for (int i = 0; i < domainSize; i++)
	{
		b[i] = 2 * kh2 + hcpS + RhoCpDt;
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
		F[i] = hcpS * Te + RhoCp * temperature[i] / (double)Dt;
	}
	F[0] = Phi;
	F[M] = 0;
}

void NonStationarySolver::calculateMatrixLU()
{
	int M = cfg->M;

	bL[0] = b[0];
	cU[0] = c[0] / (double)bL[0];
	for (int i = 1; i < domainSize - 1; i++)
	{
		bL[i] = b[i] - a[i] * cU[i - 1];
		cU[i] = c[i] / (double)bL[i];
	}
	bL[M] = b[M] - a[M] * cU[M - 1];
}

void NonStationarySolver::calculateLYF()
{
	Y[0] = F[0] / (double)bL[0];
	for (int i = 1; i < domainSize; i++)
	{
		Y[i] = (F[i] - a[i] * Y[i - 1]) / (double)bL[i];
	}
}

void NonStationarySolver::calculateUXY()
{
	int M = cfg->M;
	X[M] = Y[M];

	for (int i = M - 1; i >= 0; i--)
	{
		X[i] = Y[i] - cU[i] * X[i + 1];
	}
}