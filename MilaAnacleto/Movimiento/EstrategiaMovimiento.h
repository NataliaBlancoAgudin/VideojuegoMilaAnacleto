#pragma once
#include "Direccion.h"
#include <SFML/Graphics.hpp>

// Interfaz abstracta (clase base pura)
class EstrategiaMovimiento {
public:
	virtual ~EstrategiaMovimiento(){}

	// Le pasamos el sprite y la velocidad para que la estrategia los modifi
	virtual void mover(sf::Sprite& sprite, float velocidad, sf::Time deltaTime, Direccion& direccionActual) = 0;
};