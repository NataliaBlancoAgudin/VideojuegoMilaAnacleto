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

## 📅 Diario de Desarrollo

### Día 1: Primeros Pasos y Creación de Mila

**Hito 1: El Bucle de Juego**
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