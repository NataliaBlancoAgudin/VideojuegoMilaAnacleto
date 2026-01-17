#include "MapaInterior.h"

std::string MapaInterior::getArchivoImagen() {
	return "mapa_casa.png";
}

void MapaInterior::configurarElementos() {
	agregarMuro(426, 429, 54, 54);
}