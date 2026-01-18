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

![Sprite de Mila](https://github.com/NataliaBlancoAgudin/VideojuegoMilaAnacleto/blob/master/MilaAnacleto/assets/Mila_RPG.png)

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
**Objetivo:** Añadir un compañero (Anacleto) con comportamiento autónomo, cámara que siga al personaje principal y mapa.

* **Creación de Anacleto (Mudkip):**
  * Gracias a la clase `Entidad`, la creación del nuevo personaje fue inmediata, heredando todas las propiedades visuales y lógicas de Mila.
* **Incorporación de cámara que sigue al personaje**
  * Hemos incorporado la cámara de movimiento, para que nuestros personajes no se salgan de la pantalla, y está les siga a donde vayan. De momento solo está para que siga al personaje de Mila, pero esto en un futuro se deberá de cambiar para que siga al personaje principal.
* **Mapa**
  * Se ha añadido un mapa de prueba (`mapa_fondo.jpg`) utilizado para ver si se implementó bien la parte de la cámara (en el futuro se añadirá el mapa real del videojuego).
* **Nueva Estrategia de Movimiento (`MovimientoSeguir`):**
  * Se implementó una IA de seguimiento para que Anacleto acompañe a Mila.
  * **Lógica:** Cálculo de vectores de dirección y distancia mínima de confort.
  * **Animación Automática:** El sprite cambia su dirección (arriba, abajo, diagonales) basándose matemáticamente en el vector de movimiento, sin input del teclado.
* **Mejoras Generales:**
  * Se actualizó la clase `Entidad` para incluir un estado de "Dormir" tras inactividad prolongada para todos los personajes.

![Sprite de Anacleto](https://github.com/NataliaBlancoAgudin/VideojuegoMilaAnacleto/blob/master/MilaAnacleto/assets/Anacleto_RPG.png)

---

### 📅 16/01/2026 - Primer mapa
**Objetivo** Crear el primer mapa del juego.

* **Creación del mapa**:
 * Se ha diseñado el mapa del pueblo de Faicín, el pueblo principal de nuestra historia, de donde salen nuestros protagonistas.
<img src="https://github.com/NataliaBlancoAgudin/VideojuegoMilaAnacleto/blob/master/MilaAnacleto/assets/mapa_fondo.png" alt="Pueblo Faicín" width="300" />

### 📅 17/01/2026 - Sistema de Mapas, Colisiones y Trasiciones
**Objetivo** Implementar la carga dinámica de mapas, sistema de colisiones robusto y transiciones visuales entre zonas.

* **Arquitectura de Mapas (Patrones de Diseño)**
  * **Template Method**: Se reestructuró la clase `Mapa`. El método `cargar()` ahora
  define el esqueleto del algoritmo (limpiar, cargar texturas, escalar), delegando en las subclases (`MapaFaicin`, `MapaInterior`) la implementación de los casos específicos (`configurarElementos()`)
  * **Factory Method**: Se implementó `FactoriaMapas` para desacoplar el `main` de las subclases concretas. Ahora el juego solicita un mapa por su `ID` ("Faicin", "InteriorMila") y la fábrica devuelve la isntancia correcta envuelta en un `std::unique_ptr`
* **Física y Colisiones (Muros)**
  * Implementación de métodos `agregarMuro()` para definir zonas intransitables.
  * **Hitbox Ajustada**: Se modificó la caja de colisión de las entidades para que solo cubra los pies/sombra. Esto permite simular profundidad (el personaje puede caminar "delante" de un muro superior sin chocar con él).
  * **Sliding (Deslizamiento)**: Se separó el cálculo de movimiento en dos ejes (X e Y). Si el personaje choca en un eje, se cancela solo ese movimiento, permitiendo que se deslice por las paredes en lugar de quedarse atascado.
* **Puertas y Transiciones**
  * **Lógica de entrada**: Para cruzar una puerta, el personaje debe de estar en la mitad de la puerta
  * **Clase `Transicion`**: Se creó un sistema de efectos visuales. Al cambiar de mapa, se ejecuta una animación **"Iris Wipe"** (un círculo negro que se cierra sobre el personaje y se vuelve a abrir en el nuevo mapa), ocultando la carga de texturas y el reposicionamiento.

### 📅 18/01/2026 - Refactorización y Documentación
**Objetivo:** Mejorar la mantenibilidad del proyecto reorganizando la estructura de archivos y sincronizar la documentación técnica.

* **Organización del Proyecto:**
  * Se ha realizado una **limpieza de arquitectura**, moviendo los archivos fuente a carpetas específicas para facilitar la navegación y escalabilidad del código.
  * Estructura actual del directorio `src`:

```text
📂 MilaAnacleto
 ├── 📂 Entidad      # (Mila.h, Anacleto.h, Entidad.h...)
 ├── 📂 Movimiento   # (EstrategiaMovimiento.h, Direccion.h...)
 └── 📂 Mapa         # (Mapa.h, FactoriaMapas.h, Transicion.h...)
```

* **Diagrama UML actualizado**:
![Diagrama UML](https://github.com/NataliaBlancoAgudin/VideojuegoMilaAnacleto/blob/master/UML/UML-PrimeraSemana.png)
