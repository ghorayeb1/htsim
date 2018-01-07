#include "TempratureInterpolator.h"

#include <iostream>

TempratureInterpolator::TempratureInterpolator(HeatTransferSolver * solver)
	:solver(solver)
{
	this->vector_size = solver->cfg->getMx() + 1;
	this->interpolatedTemperature = new double[this->vector_size];
	this->X = new double[this->vector_size];

	init();
}

TempratureInterpolator::~TempratureInterpolator()
{
	if (interpolatedTemperature != NULL) delete interpolatedTemperature;
	if (X != NULL) delete X;
	this->solver = NULL;
}

void TempratureInterpolator::init()
{
	double Dx = solver->cfg->getLx() / (double) solver->cfg->getMx();
	for (int i = 0; i < vector_size; i++)
	{
		X[i] = i * Dx;
		interpolatedTemperature[i] = 0;
	}
}

void TempratureInterpolator::interpolate()
{
	interpolatedTemperature[0] = solver->temperature[0];
	interpolatedTemperature[vector_size - 1] = solver->temperature[solver->domainSize - 1];

	for (int i = 1; i < (vector_size -1); i++)
	{
		interpolatedTemperature[i] = interpolate(i);
	}
}

double TempratureInterpolator::interpolate(int i)
{
	int k1=0;
	int k2=0;
	double x;
	double xk1;
	double xk2;
	double T1;
	double T2;
	double delta_x = solver->cfg->getLx() / (double)solver->cfg->getM();
	double Dx = solver->cfg->getLx() / (double)solver->cfg->getMx();
	x = i * Dx;
	// find K1
	k1 = findLowerBound(x);
	// find K2
	k2 = k1 + 1;

	xk1 = k1 * delta_x;
	xk2 = k2 * delta_x;

	T1 = solver->temperature[k1];
	T2 = solver->temperature[k2];

	return interpolate(xk1,xk2,T1,T2,x);
}

int TempratureInterpolator::findLowerBound(double x)
{
	double delta_x = solver->cfg->getLx() / (double)solver->cfg->getM();
	int k_low = 0;
	double s = x;
	while ( s >= delta_x ) {
		k_low++;
		s -= delta_x;
	}
	return k_low;
}

double TempratureInterpolator::interpolate(double xk1, double xk2, double T1, double T2, double x)
{
	return (T1 + T2)/(double)2.0;
}
