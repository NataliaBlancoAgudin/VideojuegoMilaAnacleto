#include "MapaInterior.h"

std::string MapaInterior::getArchivoImagen() {
	return "mapa_casa.png";
}

void MapaInterior::configurarElementos() {
	agregarMuro(128, 128, 3, 3);
}