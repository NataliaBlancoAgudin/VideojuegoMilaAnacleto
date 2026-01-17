#include "Mapa.h"

void Mapa::agregarMuro(float x, float y, float w, float h) {
	muros.push_back(sf::FloatRect(x, y, w, h));

	// DEBUG
	/*sf::RectangleShape rect;
	rect.setPosition(x, y);
	rect.setSize(sf::Vector2f(w, h));

	rect.setFillColor(sf::Color(255, 0, 0, 100));
	rect.setOutlineColor(sf::Color::Red);
	rect.setOutlineThickness(1);

	murosDebug.push_back(rect);*/
}

void Mapa::agregarPuerta(float x, float y, float w, float h, std::string idDestino, float sX, float sY) {
	puertas.push_back({ sf::FloatRect(x,y,w,h), idDestino, sf::Vector2f(sX, sY) });

	// DEBUG
	/*sf::RectangleShape rect;
	rect.setPosition(x, y);
	rect.setSize(sf::Vector2f(w, h));

	rect.setFillColor(sf::Color(0, 0, 255, 100));
	rect.setOutlineColor(sf::Color::Blue);
	rect.setOutlineThickness(1);

	puertasDebug.push_back(rect);*/
}

void Mapa::cargar() {
	// 1. Limpiamos el mapa anterior
	muros.clear();
	puertas.clear();
	// DEBUG
	/*murosDebug.clear();
	puertasDebug.clear();*/

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
	/*for (const auto& rect : murosDebug) {
		ventana.draw(rect);
	}

	for (const auto& rect : puertasDebug) {
		ventana.draw(rect);
	}*/
}

bool Mapa::checkColision(sf::FloatRect rect) {
	for (const auto& muro: muros) {
		if (rect.intersects(muro)) return true;
	}
	return false;
}

std::string Mapa::checkPuerta(sf::FloatRect rect, sf::Vector2f& spawnOut) {
	for (const auto& p : puertas) {
		// 1. Calculamos el centro exacto de Mila
		float centroX = rect.left + (rect.width / 2);
		float centroY = rect.top + (rect.height / 2);

		// 2. ¿exe punto (x,y) está dentro del rectangulo de la puerta?
		if (p.zona.contains(centroX, centroY)) {
			spawnOut = p.spawnPoint;
			return p.idMapaDestino;
		}
	}
	return "";
}