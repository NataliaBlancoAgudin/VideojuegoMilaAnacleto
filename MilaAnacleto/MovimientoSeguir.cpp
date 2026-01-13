#include "MovimientoSeguir.h"
#include <cmath>

MovimientoSeguir::MovimientoSeguir(const sf::Sprite* objetivoASeguir) {
	objetivo = objetivoASeguir;
	distanciaMinima = 80.0f; // se parará a 80 pixeles del objetivo
}

void MovimientoSeguir::mover(sf::Sprite& sprite, float velocidad, sf::Time deltaTime, Direccion& direccionActual) {
	if (!objetivo) return; // si no hay objetivo no hacemos nada

	// 1. Donde están los personajes
	sf::Vector2f posYo = sprite.getPosition();
	sf::Vector2f posEl = objetivo->getPosition();

	// 2. Vector direccion (hacia donde tiene que ir)
	sf::Vector2f direccion = posEl - posYo;

	// 3. Distancia
	float distancia = std::sqrt(direccion.x * direccion.x + direccion.y * direccion.y);

	// 4. Solo nos movemos si estamos lejos del objetivo
	if (distancia > distanciaMinima) {
		// 1. MOVERSE
		sf::Vector2f movimientoNormalizado = direccion / distancia;

		sprite.move(movimientoNormalizado * velocidad * deltaTime.asSeconds());

		// 2. ANIMACIÓN
		// si se mueve mucho en X y poco en Y -> izquierda / Derecha
		// si se mueve mucho en Y y poco en X -> Arriba abajo
		bool moDerecha = direccion.x > 0;
		bool movAbajo = direccion.y > 0;

		float umbral = 0.4f;

		if (movimientoNormalizado.y < -umbral && movimientoNormalizado.x > umbral) direccionActual = ArribaDerecha;
		else if (movimientoNormalizado.y < -umbral && movimientoNormalizado.x < umbral) direccionActual = ArribaIzquierda;
		else if (movimientoNormalizado.y > -umbral && movimientoNormalizado.x > umbral) direccionActual = AbajoDerecha;
		else if (movimientoNormalizado.y > -umbral && movimientoNormalizado.x < umbral) direccionActual = AbajoIzquierda;

		else if (movimientoNormalizado.y < -umbral) direccionActual = Arriba;
		else if (movimientoNormalizado.y > umbral) direccionActual = Abajo;
		else if (movimientoNormalizado.x < -umbral) direccionActual = Izquierda;
		else if (movimientoNormalizado.x > umbral) direccionActual = Derecha;
	}
}