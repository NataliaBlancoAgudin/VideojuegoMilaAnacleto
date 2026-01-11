#pragma once
#include <SFML/Graphics.hpp>

class Mila {
private:
	sf::Sprite sprite; // Muñeco que se ve en la pantalla
	sf::Texture textura; // La imagen cargada en memoria (la hoja completa)
	float velocidad;

	// --- Variables de animación ---
	sf::Clock relojAnimcación;
	int frameActual;
	float tiempoPorFrame;
	int anchoFrame;
	int altoFrame;

public:
	// Constructor
	Mila();

	// Métodos principales
	void actualizar(); // Aquí procesaremos las teclas
	void dibujar(sf::RenderWindow& ventana); // Aquí la pintaremos

};