#include "Mila.h"

Mila::Mila() {
	// Incializamos a Mila como un cuadrado amarillo de 50x50 (torchic)
	forma.setSize(sf::Vector2f(50.f, 50.f));
	forma.setFillColor(sf::Color::Yellow);
	forma.setPosition(400.f, 300.f); // centro
	velocidad = 0.2f; // velocidad de movimiento
}

void Mila::actualizar() {
	// Detectar teclado (WASD o flechas)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		forma.move(0.f, -velocidad);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		forma.move(0.f, velocidad);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		forma.move(-velocidad, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		forma.move(velocidad, 0.f);
	}
}

void Mila::dibujar(sf::RenderWindow& ventana) {
	ventana.draw(forma);
}