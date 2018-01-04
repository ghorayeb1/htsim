#include "HeatTransferSolver.h"
#include <iostream>

HeatTransferSolver::HeatTransferSolver(const SimulationConfiguration &cfg)
{
	this->cfg = new SimulationConfiguration(cfg);
	this->domainSize = this->cfg->getM() + 1;
	this->step_size = this->cfg->getLx() / (double)this->cfg->getM();
	this->temperature = new double[domainSize];

	for (int i = 0; i < domainSize; i++)
	{
		temperature[i] = 0;
	}
}


HeatTransferSolver::~HeatTransferSolver()
{
	if (cfg != NULL) delete cfg;
	if (temperature != NULL) delete temperature;
}

void HeatTransferSolver::printParams()
{
	std::cout << "Simulation Parameters:" << std::endl;
	cfg->printConfiguraiton();
}