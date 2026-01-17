#include "Mapa.h"

void Mapa::agregarMuro(float x, float y, float w, float h) {
	muros.push_back(sf::FloatRect(x, y, w, h));

	// DEBUG
	sf::RectangleShape rect;
	rect.setPosition(x, y);
	rect.setSize(sf::Vector2f(w, h));

	rect.setFillColor(sf::Color(255, 0, 0, 100));
	rect.setOutlineColor(sf::Color::Red);
	rect.setOutlineThickness(1);

	murosDebug.push_back(rect);
}

void Mapa::agregarPuerta(float x, float y, float w, float h, std::string idDestino, float sX, float sY) {
	puertas.push_back({ sf::FloatRect(x,y,w,h), idDestino, sf::Vector2f(sX, sY) });

	// DEBUG
	sf::RectangleShape rect;
	rect.setPosition(x, y);
	rect.setSize(sf::Vector2f(w, h));

	rect.setFillColor(sf::Color(0, 0, 255, 100));
	rect.setOutlineColor(sf::Color::Blue);
	rect.setOutlineThickness(1);

	puertasDebug.push_back(rect);
}

void Mapa::cargar() {
	// 1. Limpiamos el mapa anterior
	muros.clear();
	puertas.clear();
	// DEBUG
	murosDebug.clear();
	puertasDebug.clear();

	// 2. Cargamos la imagen
	std::string archivo = "assets/" + getArchivoImagen();

	if (!textura.loadFromFile(archivo)) {
		std::cerr << "Error fatal cargando mapa: " << archivo << std::endl;
	}

	sprite.setTexture(textura);
	sprite.setScale(3.0f, 3.0f);

	// 3. Configuramos muros
	configurarElementos();
}

void Mapa::dibujar(sf::RenderWindow& ventana) {
	ventana.draw(sprite);

	// DEBUG
	for (const auto& rect : murosDebug) {
		ventana.draw(rect);
	}

	for (const auto& rect : puertasDebug) {
		ventana.draw(rect);
	}
}

bool Mapa::checkColision(sf::FloatRect rect) {
	for (const auto& muro: muros) {
		if (rect.intersects(muro)) return true;
	}
	return false;
}

std::string Mapa::checkPuerta(sf::FloatRect rect, sf::Vector2f& spawnOut) {
	for (const auto& p : puertas) {
		// Variable para guardar el rectangulo del "choque"
		sf::FloatRect intereseccion;

		// esta version de intersects nos rellena la variable intereseccion
		if (rect.intersects(p.zona, intereseccion)) {
			// Calculamos el area que se solapan (ancho x alto)
			float areaTocado = intereseccion.width * intereseccion.height;
			float areaPuerta = p.zona.width * p.zona.height;

			// Condicón: tienes que haber entrado al menos un 50% de la puerta
			if (areaTocado > (areaPuerta * 0.9f)) {
				spawnOut = p.spawnPoint;
				return p.idMapaDestino;
			}
		}
	}
	return "";
}