#pragma once
#include <memory>
#include <string>
#include "Mapa.h"

class FactoriaMapas {
public:
	// Factory Method
	std::unique_ptr<Mapa> crearMapa(std::string idMapa);
};
