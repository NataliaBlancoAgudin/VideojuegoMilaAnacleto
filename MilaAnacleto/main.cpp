#include <SFML/Graphics.hpp>
#include "Mila.h"
#include "Anacleto.h"
#include "FactoriaMapas.h"

int main() {
	// 1. Configuracion de la ventana
	sf::RenderWindow window(sf::VideoMode(800, 600), "Mila y Anacleto");

	// 2. Crear las instancias (Objetos)
	Mila jugadorMila;
	Anacleto jugadorAnacleto(jugadorMila.getSprite());

	// 3. Creamos la fabrica de mapas
	FactoriaMapas fabrica;

	// Usamos la fábrica para crear el primer mapa
	std::unique_ptr<Mapa> mapaActual = fabrica.crearMapa("Faicin");

	sf::Clock relojDelta;
	sf::View vista(sf::FloatRect(0.f, 0.f, 800.f, 600.f)); // Camara

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

		if (mapaActual) {
			// B. Actualizar lógica (Mover cosas)
			jugadorMila.actualizar(dt, *mapaActual);
			jugadorAnacleto.actualizar(dt, *mapaActual);

			sf::Vector2f spawnPoint;
			std::string proximoMapaId = mapaActual->checkPuerta(jugadorMila.getSprite().getGlobalBounds(), spawnPoint);

			if(proximoMapaId != "") {
				std::unique_ptr<Mapa> nuevoMapa = fabrica.crearMapa(proximoMapaId);

				if (nuevoMapa) {
					mapaActual = std::move(nuevoMapa);
					jugadorMila.setPosition(spawnPoint);
					jugadorAnacleto.setPosition(spawnPoint);
				}
			}
		}

		// Centrar la camara
		sf::Vector2f posicionMila = jugadorMila.getSprite().getPosition();
		posicionMila.x += 16;
		posicionMila.y += 16;
		vista.setCenter(posicionMila);

		// c. Renderizar (Dibujar cosas)
		window.clear();

		// Activamos la camara
		window.setView(vista);

		if (mapaActual) mapaActual->dibujar(window);
		jugadorMila.dibujar(window);
		jugadorAnacleto.dibujar(window);

		window.display();
	}

	return 0;
}