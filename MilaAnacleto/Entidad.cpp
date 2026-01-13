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

void Entidad::actualizar(sf::Time deltaTime) {
	sf::Vector2f posAntes = sprite.getPosition();

	if (estrategiaActual) {
		estrategiaActual->mover(sprite, velocidad, deltaTime, direccionActual);
	}

	sf::Vector2f posDespues = sprite.getPosition();
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