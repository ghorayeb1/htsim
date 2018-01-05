#ifndef SIMULATION_CONFIGURATION
#define SIMULATION_CONFIGURATION

class SimulationConfiguration
{
public:
	SimulationConfiguration();
	SimulationConfiguration(const SimulationConfiguration &obj);
	SimulationConfiguration(double Lx, double Ly, double Lz, int M, double Phi, double hc, double Te, double K, double Rho, double Cp, int stationnary, int TFinal, int N, int Mx, int My, int Mz, int ConstantPhi);
	~SimulationConfiguration();

	void printConfiguraiton() const;
	double getLx() { return Lx; }
	double getLy() { return Ly; }
	double getLz() { return Lz; }

	int getM() { return M; }

	double getPhi() { return Phi; }
	double getHc() { return hc; }

	double getTe() { return Te; }
	double getK() { return K; }
	double getRho() { return Rho; }
	double getCp() { return Cp; }

	int getStationnary() { return stationnary; }
	int getTFinal() { return TFinal; }
	int getN() { return N; }
	int getMx() { return Mx; }
	int getMy() { return My; }
	int getMz() { return Mz; }
	int getConstantPhi(){ return ConstantPhi; }

private:
	friend class HeatTransferSolver;
	friend class AnalyticSolver;
	friend class StationarySolver;
	friend class NonStationarySolver;

	double Lx;
	double Ly;
	double Lz;
	int M;
	double Phi;
	double hc;
	double Te;
	double K;
	double Rho;
	double Cp;
	int stationnary;
	int TFinal;
	int N;
	int Mx;
	int My;
	int Mz;
	int ConstantPhi;
};

#endif
