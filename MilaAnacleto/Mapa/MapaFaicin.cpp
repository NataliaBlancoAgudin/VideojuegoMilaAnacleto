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
	 // Casa Mila
	agregarMuro(1083,1062,180,177);
	agregarMuro(1083, 1242, 40, 48);
	agregarMuro(1224, 1242, 40, 48);

	 // Casa roja
	agregarMuro(648, 1443, 180, 177);
	agregarMuro(648, 1623, 40, 48);
	agregarMuro(780, 1623, 40, 48);

	 // Casa naranja
	agregarMuro(1608, 1434, 182, 189);
	agregarMuro(1611, 1623, 40, 48);
	agregarMuro(1746, 1623, 40, 48);

	// Casa morada
	agregarMuro(555, 612, 327, 190);
	agregarMuro(555, 801, 40, 48);
	agregarMuro(804, 801, 40, 48);


	// Puertas
	agregarPuerta(1149, 1248, 48, 42, "InteriorMila",  477, 700); // Casa de Mila y Anacleto
	agregarPuerta(714, 1623, 48, 42, "InteriorMila", 477, 700); // Casa roja
	agregarPuerta(1680, 1617, 48, 42, "InteriorMila", 477, 700); // Casa naranja
	agregarPuerta(639, 816, 141, 42, "InteriorMila", 477, 700); // Casa morada
}