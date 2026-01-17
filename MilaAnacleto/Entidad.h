#pragma once
#include <SFML/Graphics.hpp>
#include "Direccion.h"
#include "EstrategiaMovimiento.h"
#include "Mapa.h"

class Entidad {
protected:
	sf::Sprite sprite;
	sf::Texture textura;
	float velocidad;

	// Animacion
	sf::Clock relojAnimacion;
	sf::Clock relojInactividad;
	int frameActual;
	float tiempoPorFrame;
	int anchoFrame, altoFrame;

	Direccion direccionActual;

	std::unique_ptr<EstrategiaMovimiento> estrategiaActual;

public:
	Entidad();

	void setPosition(float x, float y);

	void setPosition(sf::Vector2f nuevaPosicion);

	sf::Vector2f getPosition();

	void setEstrategia(std::unique_ptr<EstrategiaMovimiento> nuevaEstrategia);

	virtual void actualizar(sf::Time deltaTime, Mapa& mapa);
	void dibujar(sf::RenderWindow& ventana);

	const sf::Sprite& getSprite() const { return sprite;  }

	// Funcion de ayuda para no repetri la mate de la animcaion
	void procesarAnimacion(bool seMueve, int filaIdleEspecial = -1);
};
