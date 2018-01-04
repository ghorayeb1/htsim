#include "SimulationConfiguration.h"
#include<iostream>

SimulationConfiguration::SimulationConfiguration()
	:Lx(0),
	Ly(0),
	Lz(0),
	M(0),
	Phi(0),
	hc(0),
	Te(0),
	K(164),
	stationnary(0),
	TFinal(0),
	N(0),
	Mx(0),
	My(0),
	Mz(0)
{
}

SimulationConfiguration::SimulationConfiguration(const SimulationConfiguration &obj)
	:Lx(obj.Lx),
	Ly(obj.Ly),
	Lz(obj.Lz),
	M(obj.M),
	Phi(obj.Phi),
	hc(obj.hc),
	Te(obj.Te),
	K(obj.K),
	stationnary(obj.stationnary),
	TFinal(obj.TFinal),
	N(obj.N),
	Mx(obj.Mx),
	My(obj.My),
	Mz(obj.Mz)
{
}

SimulationConfiguration::SimulationConfiguration(int Lx, int Ly, int Lz, int M, double Phi, double hc, int Te, int stationnary, int TFinal, int N, int Mx, int My, int Mz)
	:Lx(Lx),
	Ly(Ly),
	Lz(Lz),
	M(M),
	Phi(Phi),
	hc(hc),
	Te(Te),
	K(164),
	stationnary(stationnary),
	TFinal(TFinal),
	N(N),
	Mx(Mx),
	My(My),
	Mz(Mz)
{
}


SimulationConfiguration::~SimulationConfiguration()
{
}

 void SimulationConfiguration::printConfiguraiton() const{
	std::cout << "Lx=" << Lx << std::endl;
	std::cout << "Ly=" << Ly << std::endl;
	std::cout << "Lz=" << Lz << std::endl;
	std::cout << "M=" << M << std::endl;
	std::cout << "Phi=" << Phi << std::endl;
	std::cout << "hc=" << hc << std::endl;
	std::cout << "Te=" << Te << std::endl;
	std::cout << "K=" << K << std::endl;
	std::cout << "stationary=" << stationnary << std::endl;
	std::cout << "TFinal=" << TFinal << std::endl;
	std::cout << "N=" << N << std::endl;
	std::cout << "Mx=" << Mx << std::endl;
	std::cout << "My=" << My << std::endl;
	std::cout << "Mz=" << Mz << std::endl;
}