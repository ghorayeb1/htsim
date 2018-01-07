#ifndef TEMPRATURE_INTERPOLATOR
#define TEMPRATURE_INTERPOLATOR

#include "HeatTransferSolver.h"

class TempratureInterpolator
{
public:
	TempratureInterpolator(HeatTransferSolver *solver);
	~TempratureInterpolator();

	void interpolate();

	int getSize() const { return vector_size; }
	inline double getTempratureAt(int i) const { return interpolatedTemperature[i]; }

protected:
	void init();
	double interpolate(int i);
	int findLowerBound(double x);
	virtual double interpolate(double xk1, double xk2, double T1, double T2, double x);

private:
	HeatTransferSolver *solver;

	double *X;
	double *interpolatedTemperature;
	int vector_size;
};

#endif

