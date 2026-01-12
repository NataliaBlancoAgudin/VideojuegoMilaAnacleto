#include "Mila.h"
#include <iostream>

Mila::Mila() {
	// 1. Cargamos la imagen completa
	if (!textura.loadFromFile("assets/Mila_RPG.png")) {
		std::cerr << "Error cargando la textura de Torchic" << std::endl;
	}

	// 2. Le ponemos la "piel" al sprite
	sprite.setTexture(textura);

	// 3. Configuración inicial
	anchoFrame = 32;
	altoFrame = 32;

	frameActual = 0;
	tiempoPorFrame = 0.10f;

	direccionActual = Abajo;

	// 3. Seleccionar el primer cuadro
	sprite.setTextureRect(sf::IntRect(0, 0, anchoFrame, altoFrame));

	// 4. Posición y escala
	sprite.setPosition(400.f, 300.f);
	sprite.setScale(3.f, 3.f);

	velocidad = 0.2f;
}

void Mila::actualizar() {
	// 1. Variables para saber cuanto nos queremos mover en este frame
	float movimientoX = 0.f;
	float movimientoY = 0.f;

	// 2. Detectamos todas las teclas por separado
	bool arriba = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	bool abajo = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	bool izquierda = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	bool derecha = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

	if (arriba) movimientoY -= velocidad;
	if (abajo) movimientoY += velocidad;
	if (izquierda) movimientoX -= velocidad;
	if (derecha) movimientoX += velocidad;

	// 3. Nos movemos?
	// si x o y son distintos de 0 es que nos movemos
	bool seEstaMoviendo = (movimientoX != 0 || movimientoY != 0);

	if (seEstaMoviendo) {
		// Lógica de direcciones
		if (arriba && derecha) direccionActual = ArribaDerecha;
		else if (arriba && izquierda) direccionActual = ArribaIzquierda;
		else if (abajo && derecha) direccionActual = AbajoDerecha;
		else if (abajo && izquierda) direccionActual = AbajoIzquierda;

		else if (arriba) direccionActual = Arriba;
		else if (abajo) direccionActual = Abajo;
		else if (derecha) direccionActual = Derecha;
		else if (izquierda) direccionActual = Izquierda;

		// Corrección de velocidad diagonal: si vas en diagonal se recorre más distancia
		if (movimientoX != 0 && movimientoY != 0) {
			movimientoX *= 0.707f;
			movimientoY *= 0.707f;
		}

		sprite.move(movimientoX, movimientoY);

		if (relojAnimcación.getElapsedTime().asSeconds() > tiempoPorFrame) {
			frameActual++;

			if (frameActual >= 6) {
				frameActual = 0;
			}

			int fila = static_cast<int>(direccionActual);

			int posX = frameActual * anchoFrame;
			int posY = fila * altoFrame;

			sprite.setTextureRect(sf::IntRect(posX, posY, anchoFrame, altoFrame));

			relojAnimcación.restart();
		}
	}
	else {
		frameActual = 2;
		int fila = static_cast<int>(direccionActual);

		int posX = frameActual * anchoFrame;
		int posY = fila * altoFrame;

		sprite.setTextureRect(sf::IntRect(posX, posY, anchoFrame, altoFrame));
	}
}

void Mila::dibujar(sf::RenderWindow& ventana) {
	ventana.draw(sprite);
}