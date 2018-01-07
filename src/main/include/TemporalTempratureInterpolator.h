#ifndef TEMPORAL_TEMPRATURE_INTERPOLATOR
#define TEMPORAL_TEMPRATURE_INTERPOLATOR 

#include "NonStationarySolver.h"

class TemporalTempratureInterpolator
{
public:
	TemporalTempratureInterpolator(NonStationarySolver *solver);
	~TemporalTempratureInterpolator();

	void interpolate();

	int getTimeSteps() const { return time_steps; }
	int getSize() const { return vector_size; }
	inline double getTempratureAt(int i, int n) const { return interpolatedTemperature[ n * vector_size + i]; }

protected:
	void init();
	double interpolate(int i, int n);
	int findLowerBound(double x);
	virtual double interpolate(double xk1, double xk2, double T1, double T2, double x);

private:
	NonStationarySolver *solver;

	double *X;
	int vector_size;

	double *interpolatedTemperature;
	
	int time_steps;
};

#endif