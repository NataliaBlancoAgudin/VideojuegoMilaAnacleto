#include "Entidad.h"

Entidad::Entidad() {
	// Valores por defecto
	frameActual = 0;
	velocidad = 0.f;
	direccionActual = Abajo;
	altoFrame = 0;
	anchoFrame = 0;
	tiempoPorFrame = 0.f;
}

void Entidad::setEstrategia(std::unique_ptr<EstrategiaMovimiento> nuevaEstrategia) {
	estrategiaActual = std::move(nuevaEstrategia);
}

void Entidad::actualizar(sf::Time deltaTime, Mapa& mapa) {
	// 1. Guardamos la posición original segura (para saber si nos hemos movido)
	sf::Vector2f posAntes = sprite.getPosition();

	// Variables auxiliares para el sliding (para que el personaje que esta siguiendo
	// no se quede atrás por una curva cerrada)
	float xAntes = posAntes.x;
	float yAntes = posAntes.y;

	// 2. Aplicamos el movimiento COMPLETO propuesto por la estrategia
	// (Ahora el sprite está en una posición "imaginaria" que podría ser "ilegal"
	// (como un muro)
	if (estrategiaActual) {
		estrategiaActual->mover(sprite, velocidad, deltaTime, direccionActual);
	}

	// Guardamos a donde QUERÍA ir el personaje
	float xDeseada = sprite.getPosition().x;
	float yDeseada = sprite.getPosition().y;

	// FASE 1: EJE X
	// Nos ponemos en (x_nueva, y_vieja)
	sprite.setPosition(xDeseada, yAntes);

	// Calculamos hitbox de PIES
	sf::FloatRect hitboxX = sprite.getGlobalBounds();
	hitboxX.top += hitboxX.height / 2; hitboxX.height /= 2;
	hitboxX.left += 5; hitboxX.width -= 10;

	if (mapa.checkColision(hitboxX)) {
		// CHOQUE EN X! Cancelamos el movimeinto en X
		sprite.setPosition(xAntes, yAntes);
	}
	else {
		// LIBRE! Confirmamos que la nueva X es segura
		xAntes = xDeseada;
	}

	// FASE 2: EJE Y
	// Nos ponemos en (x_segura, y_nueva)
	// el valor de x_segura ya esta asegurado que es correcto
	sprite.setPosition(xAntes, yDeseada);

	sf::FloatRect hitboxY = sprite.getGlobalBounds();
	hitboxY.top += hitboxY.height / 2; hitboxY.height /= 2;
	hitboxY.left += 5; hitboxY.width -= 10;

	if (mapa.checkColision(hitboxY)) {
		// CHOQUE EN Y! Cancelamos el movimeinto en Y
		sprite.setPosition(xAntes, yAntes);
	}

	// 3. Calculamos si hubo movimiento real para la animación
	sf::Vector2f posDespues = sprite.getPosition();

	// Si posDespues es diferente a posAntes es que se ha movido
	bool seMueve = (posDespues != posAntes);

	if (seMueve) relojInactividad.restart();

	int filaIdle = -1;
	if (!seMueve && relojInactividad.getElapsedTime().asSeconds() > 5.0f) {
		filaIdle = 8;
	}
	else {
		tiempoPorFrame = 0.15f;
	}

	procesarAnimacion(seMueve, filaIdle);
}

void Entidad::dibujar(sf::RenderWindow& ventana) {
	ventana.draw(sprite);
}

void Entidad::procesarAnimacion(bool seMueve, int filaIdleEspecial) {
	// 1. Decidir la fila
	int fila = static_cast<int>(direccionActual);

	// Si tenemos una fila especial para Idle (como botar) y NO nos movemos
	if (!seMueve && filaIdleEspecial != -1) {
		fila = filaIdleEspecial;
	}

	// Si no tenemos una fila especial y no nos movemos (esperar a que pasen los 5 segundos)
	else if (!seMueve && filaIdleEspecial == -1) {
		frameActual = 2;
		int posX = frameActual * anchoFrame;
		int posY = fila * altoFrame;

		sprite.setTextureRect(sf::IntRect(posX, posY, anchoFrame, altoFrame));

		return;
	}

	// 2. Calcular frame
	if (relojAnimacion.getElapsedTime().asSeconds() > tiempoPorFrame) {
		frameActual++;
		if (frameActual >= 6) frameActual = 0;

		int posX = frameActual * anchoFrame;
		int posY = fila * altoFrame;

		sprite.setTextureRect(sf::IntRect(posX, posY, anchoFrame, altoFrame));
		relojAnimacion.restart();
	}
}

void Entidad::setPosition(float x, float y) {
	sprite.setPosition(x, y);
}

void Entidad::setPosition(sf::Vector2f nuevaPosicion) {
	sprite.setPosition(nuevaPosicion);
}

sf::Vector2f Entidad::getPosition() {
	return sprite.getPosition();
}