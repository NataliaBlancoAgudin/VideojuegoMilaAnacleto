#include "MapaFaicin.h"

std::string MapaFaicin::getArchivoImagen() {
	return "mapa_fondo.png";
}

void MapaFaicin::configurarElementos() {
	// 1. Muros
	// 1.1. Bosque de alrededor
	agregarMuro(0, 0, 1659, 474);	// Arboles arriba
	agregarMuro(0, 474, 453, 1932); // Arboles izquierda
	agregarMuro(0, 1935, 2385, 459); // Arboles abajo
	agregarMuro(1935, 0, 465, 1932); // Arboles derecha

	// 1.2. Casas
	agregarMuro(1083,1062,180,177);
	agregarMuro(1083, 1242, 48, 48);
	agregarMuro(1206, 1242, 48, 48);

	// Puertas
	agregarPuerta(1149, 1248, 48, 42, "InteriorMila",  477, 700); // Casa de Mila y Anacleto
}