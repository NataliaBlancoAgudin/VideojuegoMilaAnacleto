#pragma once
#include <SFML/Graphics.hpp>

class Transicion {
private:
	sf::CircleShape circulo;
	sf::Vector2f centroPantalla;
	float radioActual;
	float velocidad;
	bool activa;
	// true=cerrado (se hace negro)
	// false=abriendo (se ve el mapa)
	bool cerrando;

public:
	Transicion();

	void comenzar(sf::Vector2f centro);
	void actualizar(sf::Time dt);
	void dibujar(sf::RenderWindow& ventana);

	// ¿Ya está todo negro?
	bool estaCompleta();
	// ¿Ya se ha vuelto a abrir del todo?
	bool haTerminado();
	bool esActiva() { return activa; }

	void abrir();
};
