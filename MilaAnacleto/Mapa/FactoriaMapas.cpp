#include "FactoriaMapas.h"

#include "MapaFaicin.h"
#include "MapaInterior.h"

std::unique_ptr<Mapa> FactoriaMapas::crearMapa(std::string idMapa) {
	std::unique_ptr<Mapa> nuevoMapa = nullptr;

	// 1. Seleccionamos el mapa
	if (idMapa == "Faicin") {
		nuevoMapa = std::make_unique<MapaFaicin>();
	}
	else if (idMapa == "InteriorMila"){
		nuevoMapa = std::make_unique<MapaInterior>();
	}

	// 2. Incialización
	if (nuevoMapa) {
		nuevoMapa->cargar();
	}

	return nuevoMapa;
}