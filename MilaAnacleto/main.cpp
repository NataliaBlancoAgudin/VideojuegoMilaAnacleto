#include <SFML/Graphics.hpp>
#include "Mila.h"

int main() {
	// 1. Configuracion de la ventana
	sf::RenderWindow window(sf::VideoMode(800, 600), "Mila y Anacleto");

	// 2. Crear las instancias (Objetos)
	Mila jugadorMila;

	sf::Clock relojDelta;

	// 3. Game Loop (bucle del juego)
	while (window.isOpen()) {
		// Calcular deltaTime (tiempo que pasó desde el último frame)
		sf::Time dt = relojDelta.restart();

		// A. Procesar eventos (Cerrar ventana)
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// B. Actualizar lógica (Mover cosas)
		jugadorMila.actualizar(dt);

		// c. Renderizar (Dibujar cosas)
		window.clear(sf::Color(34, 139, 34));

		jugadorMila.dibujar(window);

		window.display();
	}

	return 0;
}