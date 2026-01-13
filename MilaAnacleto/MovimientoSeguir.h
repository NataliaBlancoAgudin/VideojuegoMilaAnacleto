#pragma once
#include "EstrategiaMovimiento.h"
#include <SFML/Graphics.hpp>

class MovimientoSeguir : public EstrategiaMovimiento {
private:
	// Guardamos un puntero al sprite del objetivo
	// Usamos puntero (*) prque necesitamos acceder al personaje original no a una copia
	const sf::Sprite* objetivo;
	float distanciaMinima;

public:
	// ¿A quién sigo?
	MovimientoSeguir(const sf::Sprite* objetivoASeguir);

	void mover(sf::Sprite& sprite, float velocidad, sf::Time deltaTime, Direccion& direccionActual) override;
};