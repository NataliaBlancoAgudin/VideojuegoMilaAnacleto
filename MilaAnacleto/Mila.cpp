#include "Mila.h"
#include <iostream>
#include "MovimientoTeclado.h"

Mila::Mila() {
	// 1. Cargamos la imagen completa
	if (!textura.loadFromFile("assets/Mila_RPG.png")) {
		std::cerr << "Error cargando la textura de Torchic" << std::endl;
	}

	// 2. Le ponemos la "piel" al sprite
	sprite.setTexture(textura);

	// 3. Configuración inicial (sus estadisticas)
	anchoFrame = 32;
	altoFrame = 32;
	frameActual = 0;
	tiempoPorFrame = 0.10f;
	direccionActual = Abajo;
	velocidad = 150.0f;

	// 4. Posición y escala
	sprite.setPosition(400.f, 300.f);
	sprite.setScale(3.f, 3.f);

	setEstrategia(std::make_unique<MovimientoTeclado>());
	
}