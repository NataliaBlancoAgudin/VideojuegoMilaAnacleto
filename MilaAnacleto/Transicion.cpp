#include "Transicion.h"

Transicion::Transicion() {
	activa = false;
	cerrando = false;
	radioActual = 800.f; // Empezamos con un agujero grande
	velocidad = 1000.f;

	// configuracion
	circulo.setFillColor(sf::Color::Transparent);
	circulo.setOutlineColor(sf::Color::Black);
	circulo.setOutlineThickness(2000.f);
	circulo.setPointCount(100);
}

void Transicion::comenzar(sf::Vector2f centro) {
	activa = true;
	cerrando = true;
	radioActual = 800.f;
	centroPantalla = centro;

	circulo.setPosition(centro);
}

void Transicion::actualizar(sf::Time dt) {
	if (!activa) return;

	if (cerrando) {
		// Reducimos el agujero
		radioActual -= velocidad * dt.asSeconds();
		if (radioActual <= 0) {
			radioActual = 0;
			// Cuando llega a 0, no cambiamos 'activa' a false
			// esperamos a que el main cambie de mapa
		}
	}
	else {
		// abriendo (agrandando el agujero)
		radioActual += velocidad * dt.asSeconds();
		if (radioActual >= 800.f) {
			activa = false; // fin
		}
	}

	// actualizamos la forma
	circulo.setRadius(radioActual);

	circulo.setOrigin(radioActual, radioActual);
	circulo.setPosition(centroPantalla);
}

void Transicion::dibujar(sf::RenderWindow& ventana) {
	if (activa) {
		ventana.draw(circulo);
	}
}

bool Transicion::estaCompleta() {
	// devuelve true si el agujero se ha cerrado del todo
	return (activa && cerrando && radioActual <= 0);
}

bool Transicion::haTerminado() {
	return !activa;
}

void Transicion::abrir() {
	cerrando = false; // cambia el sentido de la animacion
}