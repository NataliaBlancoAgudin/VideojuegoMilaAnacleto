#include "Mila.h"
#include <iostream>

Mila::Mila() {
	// 1. Cargamos la imagen completa
	if (!textura.loadFromFile("assets/Mila_walk.png")) {
		std::cerr << "Error cargando la textura de Torchic" << std::endl;
	}

	// 2. Le ponemos la "piel" al sprite
	sprite.setTexture(textura);

	// 3. Configuración inicial
	anchoFrame = 14;
	altoFrame = 22;

	frameActual = 0;
	tiempoPorFrame = 0.10f;

	// 3. Seleccionar el primer cuadro
	sprite.setTextureRect(sf::IntRect(0, 0, anchoFrame, altoFrame));

	// 4. Posición y escala
	sprite.setPosition(400.f, 300.f);
	sprite.setScale(3.f, 3.f);

	velocidad = 0.2f;
}

void Mila::actualizar() {
	bool seEstaMoviendo = false;

	// Detectar teclado (WASD o flechas)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		sprite.move(0.f, -velocidad);
		seEstaMoviendo = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		sprite.move(0.f, velocidad);
		seEstaMoviendo = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		sprite.move(-velocidad, 0.f);
		seEstaMoviendo = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		sprite.move(velocidad, 0.f);
		seEstaMoviendo = true;
	}

	// animacion
	if (seEstaMoviendo) {
		if (relojAnimcación.getElapsedTime().asSeconds() > tiempoPorFrame) {
			frameActual++;

			if (frameActual >= 6) {
				frameActual = 0;
			}

			int posX = frameActual * anchoFrame;

			sprite.setTextureRect(sf::IntRect(posX, 0, anchoFrame, altoFrame));

			relojAnimcación.restart();
		}
	}
	else {
		frameActual = 2;
		int posX = frameActual * anchoFrame;
		sprite.setTextureRect(sf::IntRect(posX, 0, anchoFrame, altoFrame));
	}
}

void Mila::dibujar(sf::RenderWindow& ventana) {
	ventana.draw(sprite);
}