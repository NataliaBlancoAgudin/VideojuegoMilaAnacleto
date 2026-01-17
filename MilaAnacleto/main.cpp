#include <SFML/Graphics.hpp>
#include "Mila.h"
#include "Anacleto.h"
#include "FactoriaMapas.h"
#include "Transicion.h"

int main() {
	// 1. Configuracion de la ventana
	sf::RenderWindow window(sf::VideoMode(800, 600), "Mila y Anacleto");
	window.setFramerateLimit(60);

	// 2. Crear las instancias (Objetos)
	Mila jugadorMila;
	Anacleto jugadorAnacleto(jugadorMila.getSprite());

	// 3. Creamos la fabrica de mapas y las Transiciones
	FactoriaMapas fabrica;
	Transicion transicion;

	// Usamos la fábrica para crear el primer mapa
	std::unique_ptr<Mapa> mapaActual = fabrica.crearMapa("Faicin");

	// Variables "mochila" para guardar datos mientras la pantalla se pone negra
	std::string mapaPendiente = "";
	sf::Vector2f spawnPendiente;

	// 4. Camara y reloj
	sf::Clock relojDelta;
	sf::View vista(sf::FloatRect(0.f, 0.f, 800.f, 600.f)); // Camara

	jugadorMila.setPosition(1182, 1395);

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

		// B. LÓGICA DE ACTUALIZACION
		// CASO 1: ¿ESTAMOS EN TRANSICION? (pantalla abriendose / cerrandose)
		if (transicion.esActiva()) {
			// Solo actualizamos el ciruclo negro. los personajes NO
			transicion.actualizar(dt);

			// ¿Se ha cerrado del todo el circulo? (pantalla negra)
			if (transicion.estaCompleta()) {
				std::unique_ptr<Mapa> nuevoMapa = fabrica.crearMapa(mapaPendiente);

				if (nuevoMapa) {
					mapaActual = std::move(nuevoMapa);
					jugadorMila.setPosition(spawnPendiente);
					jugadorAnacleto.setPosition(spawnPendiente);
				}

				// y por ultimo, decimos que el circulo se abra
				transicion.abrir();
			}
		}

		// CASO 2: JUEGO NORMAL
		else {
			if (mapaActual) {
				// Movemos los personajes
				jugadorMila.actualizar(dt, *mapaActual);
				jugadorAnacleto.actualizar(dt, *mapaActual);

				sf::Vector2f spawnPoint;
				std::string proximoMapaId = mapaActual->checkPuerta(jugadorMila.getSprite().getGlobalBounds(), spawnPoint);

				if (proximoMapaId != "") {
					// NO CAMBIAMOS EL MAPA TODAVIA
					// 1. Guardamos a donde queremos ir en la "mochila"
					mapaPendiente = proximoMapaId;
					spawnPendiente = spawnPoint;

					// 2. Inciamos el efecto visual (congelando el juego en el siguiente frame)
					sf::Vector2f centroEfecto = jugadorMila.getSprite().getPosition();

					centroEfecto.x += 16;
					centroEfecto.y += 16;

					transicion.comenzar(centroEfecto);
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

		// Dibujamos la transicion al final
		transicion.dibujar(window);
		window.display();
	}

	return 0;
}