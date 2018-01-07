#include "TemporalTempratureInterpolator.h"

#include <iostream>

TemporalTempratureInterpolator::TemporalTempratureInterpolator(NonStationarySolver * solver)
	:solver(solver)
{
	this->vector_size = solver->cfg->getMx() + 1;
	this->time_steps = solver->time_steps_nbr;

	this->X = new double[this->vector_size];
	this->interpolatedTemperature = new double[this->vector_size * this->time_steps];

	init();
}

TemporalTempratureInterpolator::~TemporalTempratureInterpolator()
{
	if (interpolatedTemperature != NULL) delete interpolatedTemperature;
	if (X != NULL) delete X;
	this->solver = NULL;
}

void TemporalTempratureInterpolator::interpolate()
{
	for (int n = 0; n < time_steps; n++) {
		int baseIdx = n * vector_size;
		interpolatedTemperature[baseIdx + 0] = solver->discretTemprature[n*solver->domainSize + 0];
		interpolatedTemperature[baseIdx + vector_size - 1] = solver->discretTemprature[n*solver->domainSize+ solver->domainSize - 1];

		for (int i = 1; i < (vector_size - 1); i++)
		{
			interpolatedTemperature[baseIdx+i] = interpolate(i,n);
		}
	}
}

void TemporalTempratureInterpolator::init()
{
	double Dx = solver->cfg->getLx() / (double)solver->cfg->getMx();
	for (int i = 0; i < vector_size; i++)
	{
		X[i] = i * Dx;
	}
	for (int n = 0; n < time_steps; n++)
	{
		for (int i = 0; i < vector_size; i++)
		{
			interpolatedTemperature[n*vector_size +i] = 0;
		}
	}
}

double TemporalTempratureInterpolator::interpolate(int i, int n)
{
	int k1 = 0;
	int k2 = 0;
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

	T1 = solver->discretTemprature[n * solver->domainSize + k1];
	T2 = solver->discretTemprature[n * solver->domainSize + k2];

	return interpolate(xk1, xk2, T1, T2, x);
}

int TemporalTempratureInterpolator::findLowerBound(double x)
{
	double delta_x = solver->cfg->getLx() / (double)solver->cfg->getM();
	int k_low = 0;
	double s = x;
	while (s >= delta_x) {
		k_low++;
		s -= delta_x;
	}
	return k_low;
}

double TemporalTempratureInterpolator::interpolate(double xk1, double xk2, double T1, double T2, double x)
{
	double a = (T2 - T1) / (double)(xk2 - xk1);
	double b = (T1 + T2 - a * (xk1 + xk2)) * (double)0.5;
	return a*x + b;
}
