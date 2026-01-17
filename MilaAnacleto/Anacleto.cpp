#include "Anacleto.h"
#include <iostream>
#include "MovimientoSeguir.h"

Anacleto::Anacleto(const sf::Sprite& spriteMila) {
	// 1. Cargamos la imagen completa
	if (!textura.loadFromFile("assets/Anacleto_RPG.png")) {
		std::cerr << "Error cargando la textura de Mudkip" << std::endl;
	}

	// 2. Le ponemos la "piel" al sprite
	sprite.setTexture(textura);

	// 3. Configuración inicial (sus estadisticas)
	anchoFrame = 32;
	altoFrame = 32;
	frameActual = 0;
	tiempoPorFrame = 0.10f;
	direccionActual = Abajo;
	velocidad = 120.0f;

	// 4. Posición y escala
	sprite.setPosition(1119, 1392);
	sprite.setScale(3.f, 3.f);

	setEstrategia(std::make_unique<MovimientoSeguir>(&spriteMila));

}