#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

// Estructura auxiliar para las puertas
struct Puerta {
	sf::FloatRect zona;
	std::string idMapaDestino;
	sf::Vector2f spawnPoint;
};

class Mapa {
protected:
	sf::Sprite sprite;
	sf::Texture textura;

	std::vector<sf::FloatRect> muros;
	std::vector<Puerta> puertas;

	// Método para añadir un muro a la coordenada dada
	// x,y,w,h: coordenadas del muro
	void agregarMuro(float x, float y, float w, float h);

	// Método para añadir una puerta en las coordenadas dadas
	// - x,y,w,h: coordenadas de la puerta
	// - idDestino: id del mapa que cambiamos
	// - sX, sY: coordenadas del personaje en el nuevo mapa
	void agregarPuerta(float x, float y, float w, float h, std::string idDestino, float sX, float sY);

	// Métodos abstractos que usarán los hijos
	virtual std::string getArchivoImagen() = 0;
	virtual void configurarElementos() = 0;

	// para añadir los muros y las puertas DEBUG
	std::vector<sf::RectangleShape> murosDebug;
	std::vector<sf::RectangleShape> puertasDebug;

public:
	virtual ~Mapa() {}

	void cargar();

	// Métodos publicos generales
	void dibujar(sf::RenderWindow& ventana);
	bool checkColision(sf::FloatRect rect);
	std::string checkPuerta(sf::FloatRect rect, sf::Vector2f& spawnOut);
};