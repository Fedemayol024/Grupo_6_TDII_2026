# AFP 0 — Entorno STM32CubeIDE y programación de microcontroladores

**Técnicas Digitales II — UTN FRT — Grupo 6 — 2026**

Primera actividad práctica de la materia. Sirve para familiarizarse con STM32CubeIDE y recorrer el ciclo completo de una aplicación: edición, compilación, depuración y programación de la placa.

## Objetivos de la actividad

- Conocer el entorno STM32CubeIDE y sus herramientas.
- Crear un proyecto desde cero y configurar el módulo GPIO para los LEDs y el pulsador de la placa.
- Reutilizar un proyecto existente como plantilla para uno nuevo.
- Ejercitar las particularidades de la programación de microcontroladores.

## Qué se pide

Cuatro aplicaciones que usan los tres LEDs y el pulsador de la placa. En esta etapa se resuelven con las funciones de la HAL (`HAL_GPIO_WritePin`, `HAL_GPIO_ReadPin`) y retardos bloqueantes (`HAL_Delay`). Todas deben ser de carácter general: los LEDs se manejan con un vector para poder agregar más con cambios mínimos.

Estas cuatro aplicaciones son la base de las actividades siguientes: en la [AFP 3](../AFP_3_Grupo_6_TDII) se les incorpora un driver GPIO propio y en la [AFP 4](../AFP_4_Grupo_6_TDII) retardos no bloqueantes.

## Aplicaciones

| App | Responsable | Placa | Carpeta |
| :---: | :--- | :--- | :--- |
| 1.1 | Santino Machin | NUCLEO-F429ZI | [`App_1_1_Grupo_6_2026`](App_1_1_Grupo_6_2026) |
| 1.2 | Carlos Mamani Flores | NUCLEO-F439ZI | [`App_1_2_Grupo_6_2026`](App_1_2_Grupo_6_2026) |
| 1.3 | Federico Mayol | NUCLEO-F767ZI | [`App_1_3_Grupo_6_2026`](App_1_3_Grupo_6_2026) |
| 1.4 | Lucas Emanuel Cusi | STM32F401RC | [`App_1_4_Grupo_6_2026`](App_1_4_Grupo_6_2026) |

### App 1.1 — Secuencia de LEDs

Enciende y apaga en secuencia los tres LEDs: LED1 (verde), LED2 (azul), LED3 (rojo) y vuelve a empezar. Cada LED permanece 200 ms encendido y 200 ms apagado.

### App 1.2 — Secuencia con inversión de sentido

Arranca con la secuencia de la App 1.1. Cada vez que se presiona el pulsador, la secuencia invierte su sentido y continúa.

### App 1.3 — Cuatro secuencias seleccionables

El pulsador pasa de una secuencia a la siguiente; después de la cuarta vuelve a la primera.

| Secuencia | Comportamiento | Alternancia |
| :---: | :--- | :--- |
| 1 | Igual a la App 1.1 | 150 ms |
| 2 | Los tres LEDs parpadean juntos | 300 ms |
| 3 | Cada LED parpadea a su propio ritmo | LED1 100 ms, LED2 300 ms, LED3 600 ms |
| 4 | LED1 y LED3 parpadean juntos y LED2 en oposición | 150 ms |

### App 1.4 — Parpadeo con frecuencia seleccionable

Los tres LEDs parpadean juntos. Cada pulsación cambia el tiempo de alternancia: 100 ms → 250 ms → 500 ms → 1000 ms, y vuelve a 100 ms.

## Estado

Las cuatro aplicaciones están entregadas y presentadas.
