# 🎮 Mila y Anacleto - Aventura en SFML

Un proyecto de videojuego 2D desarrollado en C++ utilizando la librería SFML. El proyecto documenta la evolución desde una ventana básica hasta la implementación de patrones de diseño y lógica de IA de acompañante.

## 🛠️ Tecnologías y Entorno

* **Lenguaje:** C++
* **IDE:** Visual Studio 2022
* **Librería:** SFML (Simple and Fast Multimedia Library) - Versión Visual C++ 17 (2022) 64-bit.

---

## ⚙️ Configuración del Entorno (11/01/2026)

Se ha decidido utilizar **Visual Studio 2022** alineado con las prácticas de la asignatura de Videojuegos.

### Pasos de instalación realizados:
1.  Descarga de SFML (VC++ 17 64-bit).
2.  Descompresión de la librería.

> ⚠️ **Nota de ubicación**
> Se ha descomprimido la librería directamente en la carpeta `C:` para facilitar la vinculación.

3.  Vinculación de librerías y cabeceras en las propiedades del proyecto de VS.

> 🔔 **Importante**
> Recordar revisar la configuración del *Linker* para incluir las dependencias de `sfml-graphics`, `sfml-window` y `sfml-system`.

---

# 📅 Diario de Desarrollo

## Día 1: Primeros Pasos y Creación de Mila

### ⚙️ Hito 1: El Bucle de Juego
Se configuró la ventana básica y el *Game Loop* (bucle de juego) para procesar eventos y renderizado.

<details>
<summary>📄 Ver código del Main (Test inicial)</summary>

```cpp
#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Mila y Anacleto - Test");

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::Green);
		window.display();
	}
	return 0;
}
```
</details>

### 👤 Hito 2: Cración de personajes (básico)
Una vez creado la pantalla básica del juego vamos a añadir nuestro primer personaje: Mila (Torchic)

<details>
<summary>📄 Ver código de Mila.h </summary>

```cpp
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
```
</details>

<details>
<summary>📄 Ver código de Mila.cpp </summary>

```cpp
#include "Mila.h"

Mila::Mila() {
	// Incializamos a Mila como un cuadrado amarillo de 50x50 (torchic)
	forma.setSize(sf::Vector2f(50.f, 50.f));
	forma.setFillColor(sf::Color::Yellow);
	forma.setPosition(400.f, 300.f); // centro
	velocidad = 0.2f; // velocidad de movimiento
}

void Mila::actualizar() {
	// Detectar teclado (WASD o flechas)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		forma.move(0.f, -velocidad);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		forma.move(0.f, velocidad);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		forma.move(-velocidad, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		forma.move(velocidad, 0.f);
	}
}

void Mila::dibujar(sf::RenderWindow& ventana) {
	ventana.draw(forma);
}
```
</details>

Y hemos modificado nuestro `main.cpp` para añadir nuestro primer personaje
<details>
<summary>📄 Ver código de main.cpp</summary>

```cpp
#include <SFML/Graphics.hpp>
#include "Mila.h"

int main() {
	// 1. Configuracion de la ventana
	sf::RenderWindow window(sf::VideoMode(800, 600), "Mila y Anacleto");

	// 2. Crear las instancias (Objetos)
	Mila jugadorMila;

	// 3. Game Loop (bucle del juego)
	while (window.isOpen()) {
		// A. Procesar eventos (Cerrar ventana)
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// B. Actualizar lógica (Mover cosas)
		jugadorMila.actualizar();

		// c. Renderizar (Dibujar cosas)
		window.clear(sf::Color(34, 139, 34));

		jugadorMila.dibujar(window);

		window.display();
	}

	return 0;
}
```
</details>

Y así tendremos nuestro primer personaje

### 📃 Hito 3. Creación del sprite de Mila
Teniendo ya la animación más o menos hemos decidido añadir el sprite de Mila. Para ello, buscando por Internet nos salió este sprite:

[Torchic - Pokémon Mystery Dungeon: Explorers of Sky - DS / DSi](https://www.spriters-resource.com/ds_dsi/pokemonmysterydungeonexplorersofsky/asset/131076/)

Que tiene todos los sprite que necesitamos (moverse hacia delante, hacia atrás, de lado,….) e incluso muchos mas! (nos vendrá bien para hacer más efectos)

Separaremos el primer movimiento en un sprite para poder insertarlo en nuestro videojuego
Y cambiaremos el código de Mila para añadirle esta animación
<details>
<summary>📄 Ver código de Mila.h</summary>

```cpp
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
```
</details>

<details>
<summary>📄 Ver código de Mila.cpp</summary>

```cpp
#include "Mila.h"
#include <iostream>

Mila::Mila() {
	// 1. Cargamos la imagen completa
	if (!textura.loadFromFile("assets/Mila_walk.png")) {
		std::cerr << "Error cargando la textura de Torchic" << std::endl;
	}

	// 2. Le ponemos la "piel" al sprite
	sprite.setTexture(textura);

	// 3. Configuración inicial
	anchoFrame = 14;
	altoFrame = 22;

	frameActual = 0;
	tiempoPorFrame = 0.10f;

	// 3. Seleccionar el primer cuadro
	sprite.setTextureRect(sf::IntRect(0, 0, anchoFrame, altoFrame));

	// 4. Posición y escala
	sprite.setPosition(400.f, 300.f);
	sprite.setScale(3.f, 3.f);

	velocidad = 0.2f;
}

void Mila::actualizar() {
	bool seEstaMoviendo = false;

	// Detectar teclado (WASD o flechas)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		sprite.move(0.f, -velocidad);
		seEstaMoviendo = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		sprite.move(0.f, velocidad);
		seEstaMoviendo = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		sprite.move(-velocidad, 0.f);
		seEstaMoviendo = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		sprite.move(velocidad, 0.f);
		seEstaMoviendo = true;
	}

	// animacion
	if (seEstaMoviendo) {
		if (relojAnimcación.getElapsedTime().asSeconds() > tiempoPorFrame) {
			frameActual++;

			if (frameActual >= 6) {
				frameActual = 0;
			}

			int posX = frameActual * anchoFrame;

			sprite.setTextureRect(sf::IntRect(posX, 0, anchoFrame, altoFrame));

			relojAnimcación.restart();
		}
	}
	else {
		frameActual = 2;
		int posX = frameActual * anchoFrame;
		sprite.setTextureRect(sf::IntRect(posX, 0, anchoFrame, altoFrame));
	}
}

void Mila::dibujar(sf::RenderWindow& ventana) {
	ventana.draw(sprite);
}
```
</details>

Y así hemos conseguido tener nuestra primera animación.
