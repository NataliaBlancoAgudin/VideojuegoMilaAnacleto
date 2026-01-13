#include "Mapa.h"
#include <iostream>

Mapa::Mapa() {
	if (!textura.loadFromFile("assets/mapa_fondo.jpg")) {
		std::cerr << "Error cargando la textura de Torchic" << std::endl;
	}

	sprite.setTexture(textura);

	sprite.setScale(3.0f, 3.0f);
}

void Mapa::dibujar(sf::RenderWindow& ventana) {
	ventana.draw(sprite);
}