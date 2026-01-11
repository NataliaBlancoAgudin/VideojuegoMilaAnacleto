#pragma once
#include <SFML/Graphics.hpp>

class Mila {
private:
	// Por ahora usaremos un rectángulo, luego será un Sprite
	sf::RectangleShape forma;
	float velocidad;

public:
	// Constructor
	Mila();

	// Métodos principales
	void actualizar(); // Aquí procesaremos las teclas
	void dibujar(sf::RenderWindow& ventana); // Aquí la pintaremos

};