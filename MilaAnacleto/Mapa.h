#pragma once
#include <SFML/Graphics.hpp>

class Mapa {
private:
	sf::Texture textura;
	sf::Sprite sprite;

public:
	Mapa();
	void dibujar(sf::RenderWindow& ventana);
};