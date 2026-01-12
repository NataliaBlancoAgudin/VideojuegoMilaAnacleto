#pragma once
#include "EstrategiaMovimiento.h"
#include "Direccion.h"
#include <SFML/Graphics.hpp>

class MovimientoTeclado : public EstrategiaMovimiento {
public:
	void mover(sf::Sprite& sprite, float velocidad, sf::Time deltaTime, Direccion& direccionActual) override;
};