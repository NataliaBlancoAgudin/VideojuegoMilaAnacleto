#pragma once
#include "Mapa.h"

class MapaFaicin : public Mapa {
protected:
	std::string getArchivoImagen() override;
	void configurarElementos() override;
};