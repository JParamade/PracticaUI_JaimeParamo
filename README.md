# Arquitectura del Sistema

Este proyecto implementa un sistema de **Árbol de Habilidades** totalmente modular diseñado para Unreal Engine 5. El objetivo principal de la arquitectura es separar la lógica de juego, la interfaz de usuario y la gestión de progresión, permitiendo una fácil expansión e integración en cualquier marco de juego. El sistema gira en torno al concepto de **nodos de habilidad**, **interacción visual** y **eventos de integración con el gameplay**.

## Filosofía de Diseño

* **Modularidad:** Cada componente (lógica, UI, integración) es independiente y reutilizable.
* **Escalabilidad:** Nuevas habilidades o ramas pueden añadirse sin reescribir el código.
* **Reactividad:** La interfaz refleja automáticamente los cambios de estado desde la capa lógica.

## 1. Capa de Lógica y Datos (C++)

Esta capa define el comportamiento fundamental del árbol de habilidades.

### Nodos de Habilidad

Cada nodo representa una habilidad o mejora. Los nodos almacenan:

* **Estado:** Bloqueado, Desbloqueado o Comprado.
* **Coste:** Recurso necesario (puntos o moneda).
* **Dependencias:** Otros nodos que deben desbloquearse primero.

El sistema verifica si un nodo puede desbloquearse o comprarse mediante validación de estado y dependencias, garantizando que se respeten las reglas del juego.

## 2. Capa de Interfaz (UMG)

Esta capa proporciona la interacción visual con el jugador.

### Botones de Habilidad (Widgets)

* Representan visualmente cada nodo.
* Cambian de apariencia según el estado.
* Gestionan eventos como **hover**, **clic** o **selección**.

La interfaz escucha los cambios de la capa lógica y se actualiza automáticamente, asegurando que el jugador vea información precisa.

## 3. Capa de Integración con el Juego

Conecta las habilidades desbloqueadas con efectos reales en el gameplay.

### Capacidades de Integración

* **Progresión del jugador:** Activa habilidades, estadísticas o efectos de juego.
* **Eventos y Delegados:** Notifica a otros sistemas cuando se desbloquea una habilidad.
* **Guardado y Carga:** Conserva el progreso del árbol entre sesiones.

## Diagrama del Sistema

```
[ Entrada del Jugador ]
       |
       v
[ Capa UI – Botones de Habilidad ]
       |
       v
[ Capa Lógica – Nodos de Habilidad ]
       |     \-- Valida coste y dependencias
       |
       v
[ Integración con el Juego ]
       \-- Aplica habilidades, guarda progreso
```