# Arquitectura del Sistema

Este proyecto implementa un sistema de **Árbol de Habilidades** totalmente modular diseñado para Unreal Engine 5. El objetivo principal de la arquitectura es separar la lógica de juego, la interfaz de usuario y la gestión de progresión, permitiendo una fácil expansión e integración en cualquier marco de juego. El sistema gira en torno al concepto de **nodos de habilidad**, **interacción visual** y **eventos de integración con el gameplay**.

## Filosofía de Diseño

* **Modularidad:** Cada componente (lógica, UI, integración) es independiente y reutilizable.
* **Escalabilidad:** Nuevas habilidades o ramas pueden añadirse sin reescribir el código.
* **Reactividad:** La interfaz refleja automáticamente los cambios de estado desde la capa lógica.

## 1. Capa de Lógica y Datos (C++)

Esta capa define el comportamiento fundamental del árbol de habilidades.

### Nodos de Habilidad (`FSkillNode`)

Cada nodo representa una habilidad o mejora. Los nodos almacenan:

* **Estado:** Bloqueado, Desbloqueado o Comprado.
* **Coste:** Recurso necesario (puntos o moneda).
* **Dependencias:** Otros nodos que deben desbloquearse primero.

> **Insight:** `FSkillNode` es el núcleo de la lógica del árbol. Su diseño con punteros débiles (`TWeakPtr`) permite gestionar relaciones de padres e hijos sin crear referencias circulares que provoquen fugas de memoria.

### Árbol de Habilidades (`USkillTree`)

Esta clase administra la colección de nodos y la lógica de desbloqueo:

* Construye los nodos desde una tabla de datos (`UDataTable`).
* Gestiona la disponibilidad de los nodos según sus dependencias.
* Emite eventos (`OnNodeChanged`) cuando un nodo cambia de estado.

> **Insight:** `USkillTree` centraliza la lógica y permite desacoplar la interfaz visual de los cálculos de estado, facilitando futuras expansiones.

## 2. Capa de Interfaz (UMG)

Proporciona la interacción visual con el jugador.

### Botones de Habilidad (`USkillButton` / `UCustomButtonWidget`)

* Representan cada nodo de habilidad en pantalla.
* Cambian apariencia según estado (bloqueado, disponible, desbloqueado).
* Gestionan eventos de interacción (`OnButtonPressed`, `OnButtonReleased`).

> **Insight:** `USkillButton` se basa en `UCustomButtonWidget`, que proporciona métodos genéricos de mostrar, ocultar y escalar elementos. Esto permite un sistema UI coherente y fácil de mantener.

### Widget del Árbol (`USkillTreeWidget`)

* Contiene todos los botones de habilidad.
* Escucha cambios del `USkillTree` y actualiza la UI automáticamente.
* Maneja animaciones y visualización de puntos, salud o estadísticas.

> **Insight:** `USkillTreeWidget` conecta la lógica con la presentación, garantizando que la interfaz refleje siempre el estado actual del árbol de habilidades.