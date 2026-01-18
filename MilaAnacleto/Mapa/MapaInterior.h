#pragma once
#include "Mapa.h"

class MapaInterior : public Mapa {
protected:
	std::string getArchivoImagen() override;
	void configurarElementos() override;

};
