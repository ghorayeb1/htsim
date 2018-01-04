#ifndef SIMULATION_CONFIGURATION
#define SIMULATION_CONFIGURATION

class SimulationConfiguration
{
public:
	SimulationConfiguration();
	SimulationConfiguration(const SimulationConfiguration &obj);
	SimulationConfiguration(int Lx, int Ly, int Lz, int M, double Phi, double hc, int Te, int stationnary, int TFinal, int N, int Mx, int My, int Mz);
	~SimulationConfiguration();

	void printConfiguraiton() const;
	int getLx() { return Lx; }
	int getLy() { return Ly; }
	int getLz() { return Lz; }

	int getM() { return M; }

	double getPhi() { return Phi; }
	double getHc() { return hc; }

	int getTe() { return Te; }
	int getK() { return K; }

	int getStationnary() { return stationnary; }
	int getTFinal() { return TFinal; }
	int getN() { return N; }
	int getMx() { return Mx; }
	int getMy() { return My; }
	int getMz() { return Mz; }

private:
	friend class HeatTransferSolver;
	friend class AnalyticSolver;

	int Lx;
	int Ly;
	int Lz;
	int M;
	double Phi;
	double hc;
	int Te;
	int K;
	int stationnary;
	int TFinal;
	int N;
	int Mx;
	int My;
	int Mz;
};

#endif
