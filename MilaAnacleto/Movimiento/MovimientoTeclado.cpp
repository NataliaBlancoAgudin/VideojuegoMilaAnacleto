#include "MovimientoTeclado.h"
#include <SFML/Window/Keyboard.hpp>

void MovimientoTeclado::mover(sf::Sprite& sprite, float velocidad, sf::Time deltaTime, Direccion& direccionActual) {
	// 1. Variables para saber cuanto nos queremos mover en este frame
	sf::Vector2f movimiento(0.f, 0.f);

	// 2. Detectamos todas las teclas por separado
	bool arriba = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	bool abajo = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	bool izquierda = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	bool derecha = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

	// Si tocamos CUALQUIER tecla reiniciamos el reloj de inactividad a 0
	//if (arriba || abajo || izquierda || derecha) relojInactividad.restart();

	if (arriba) movimiento.y -= velocidad;
	if (abajo) movimiento.y += velocidad;
	if (izquierda) movimiento.x -= velocidad;
	if (derecha) movimiento.x += velocidad;

	// 3. Nos movemos?
	// si x o y son distintos de 0 es que nos movemos
	bool seEstaMoviendo = (movimiento.x != 0 || movimiento.y != 0);

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
		if (movimiento.x != 0 && movimiento.y != 0) {
			movimiento.x *= 0.707f;
			movimiento.y *= 0.707f;
		}

		sprite.move(movimiento * deltaTime.asSeconds());
	}

}