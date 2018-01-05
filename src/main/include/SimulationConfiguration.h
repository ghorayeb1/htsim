#ifndef SIMULATION_CONFIGURATION
#define SIMULATION_CONFIGURATION

class SimulationConfiguration
{
public:
	SimulationConfiguration();
	SimulationConfiguration(const SimulationConfiguration &obj);
	SimulationConfiguration(double Lx, double Ly, double Lz, int M, double Phi, double hc, double Te, double K, double Rho, double Cp, int stationnary, int TFinal, int N, int Mx, int My, int Mz, int ConstantPhi, int ExportDiscretForFullPositions);
	~SimulationConfiguration();

	void printConfiguraiton() const;
	double getLx() const { return Lx; }
	double getLy() const { return Ly; }
	double getLz() const { return Lz; }

	int getM() const { return M; }

	double getPhi() const { return Phi; }
	double getHc() const { return hc; }

	double getTe() const { return Te; }
	double getK() const { return K; }
	double getRho() const { return Rho; }
	double getCp() const { return Cp; }

	int getStationnary() const { return stationnary; }
	int getTFinal() const { return TFinal; }
	int getN() const { return N; }
	int getMx() const { return Mx; }
	int getMy() const { return My; }
	int getMz() const { return Mz; }
	int getConstantPhi() const { return ConstantPhi; }
	int getExportDiscretForFullPositions() const { return ExportDiscretForFullPositions; }

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
	int ExportDiscretForFullPositions;
};

#endif
