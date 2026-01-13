# 🎮 Mila y Anacleto - Devlog

Proyecto de desarrollo de videojuegos en C++ y SFML. Este repositorio documenta la creación de un motor 2D básico, la implementación de personajes animados y el uso de patrones de diseño de software.

## 🛠️ Tecnologías
* **IDE:** Visual Studio 2022
* **Librería:** SFML (Visual C++ 17 64-bit)
* **Herramientas de Arte:** Piskel (para edición de sprites)

---

## 📅 Diario de Desarrollo

### 📅 11/01/2026 - Configuración y Primeros Pasos
**Objetivo:** Configurar el entorno y renderizar el primer personaje.

* **Configuración del Entorno:** Se instaló y vinculó SFML en Visual Studio 2022. Se realizaron pruebas de renderizado de ventana (Test de ventana verde).
* **Creación de Mila (Torchic):**
  * Implementación inicial como una forma geométrica simple (`sf::RectangleShape`).
  * Implementación de movimiento básico por teclado.
* **Integración de Sprites:**
  * Sustitución del rectángulo por un *Sprite Sheet* de *Pokémon Mystery Dungeon*.
  * Creación del sistema de animación básico mediante control de frames y relojes (`sf::Clock`).

---

### 📅 12/01/2026 - Animación Avanzada y Refactorización
**Objetivo:** Mejorar el movimiento y limpiar la arquitectura del código.

* **Mejoras en el Movimiento:**
  * Implementación de movimiento en **8 direcciones** (incluyendo diagonales).
  * Corrección matemática de la velocidad diagonal para mantener una velocidad constante.
  * Creación de estados de inactividad: el personaje realiza una animación especial (dormir) tras 10 segundos quieto.
* **Arquitectura de Software (Patrón Strategy):**
  * Se detectó la necesidad de escalar el código para futuros personajes.
  * **Clase `Entidad`:** Se creó una clase padre para gestionar sprites, texturas y lógica común.
  * **Strategy Pattern:** Se separó la lógica de movimiento en una interfaz `EstrategiaMovimiento`, permitiendo intercambiar comportamientos (ej. `MovimientoTeclado`).

---

### 📅 13/01/2026 - IA y Segundo Personaje
**Objetivo:** Añadir un compañero (Anacleto) con comportamiento autónomo.

* **Creación de Anacleto (Mudkip):**
  * Gracias a la clase `Entidad`, la creación del nuevo personaje fue inmediata, heredando todas las propiedades visuales y lógicas de Mila.
* **Nueva Estrategia de Movimiento (`MovimientoSeguir`):**
  * Se implementó una IA de seguimiento para que Anacleto acompañe a Mila.
  * **Lógica:** Cálculo de vectores de dirección y distancia mínima de confort.
  * **Animación Automática:** El sprite cambia su dirección (arriba, abajo, diagonales) basándose matemáticamente en el vector de movimiento, sin input del teclado.
* **Mejoras Generales:**
  * Se actualizó la clase `Entidad` para incluir un estado de "Dormir" tras inactividad prolongada para todos los personajes.

---
