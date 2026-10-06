# AFP 3 — Creación de drivers en STM32CubeIDE

**Técnicas Digitales II — UTN FRT — Grupo 6 — 2026**

En esta actividad las aplicaciones de la [AFP 0](../AFP_0_Grupo_6_TDII) se vuelven a entregar con un **driver GPIO propio**. El comportamiento de cada aplicación es el mismo; cambia la forma en que accede al hardware.

## Objetivos de la actividad

- Desarrollar un ejemplo concreto de creación de un driver para un módulo de la placa.
- Usar ese driver en el desarrollo de aplicaciones.
- Entender el uso de drivers como buena práctica: mejora la portabilidad del código si hay que cambiar de plataforma.

## Qué se incorpora

1. Se crea un driver para el módulo GPIO, ubicado en `Drivers/API` del proyecto, con funciones para encender, apagar y conmutar un LED y para leer el pulsador.
2. En `main.c` se reemplazan las llamadas a la HAL de GPIO por las funciones del driver.
3. Se compila, se depura y se verifica en la placa que la aplicación funciona igual que antes.

La consigna pide además que todo el grupo use **el mismo nombre para el driver y para sus funciones**.

## Aplicaciones

| App | Responsable | Placa | Carpeta | Driver utilizado |
| :---: | :--- | :--- | :--- | :--- |
| 1.1 | Santino Machin | NUCLEO-F429ZI | [`App 1.1`](App%201.1) | Todavía usa la HAL directamente |
| 1.2 | Carlos Mamani Flores | NUCLEO-F439ZI | [`App_3_2_Grupo_6_2026`](App_3_2_Grupo_6_2026) | `driver_led`, `driver_boton`, `driver_time` y capa PAL |
| 1.3 | Federico Mayol | NUCLEO-F767ZI | [`App 1.3`](App%201.3) | `API_GPIO` |
| 1.4 | Lucas Emanuel Cusi | STM32F401RC | [`App_3_4_Grupo_6_2026`](App_3_4_Grupo_6_2026) | `API_GPIO` |

La carpeta [`App_3_3_Grupo_6_2026`](App_3_3_Grupo_6_2026) contiene solo el proyecto generado por STM32CubeIDE, sin la lógica de la aplicación. La versión funcional de la App 1.3 es la de la carpeta `App 1.3`.

### Qué debe cumplir cada aplicación

| App | Comportamiento (igual al de la AFP 0) | Tarea en esta actividad |
| :---: | :--- | :--- |
| 1.1 | Secuencia verde → azul → rojo, 200 ms encendido y 200 ms apagado | Manejar los LEDs con el driver GPIO |
| 1.2 | La secuencia invierte su sentido con cada pulsación | Manejar LEDs y pulsador con el driver |
| 1.3 | Cuatro secuencias; el pulsador pasa a la siguiente | Manejar LEDs y pulsador con el driver |
| 1.4 | Parpadeo conjunto; el pulsador cambia entre 100, 250, 500 y 1000 ms | Manejar LEDs y pulsador con el driver |

El detalle de cada secuencia está en el [README de la AFP 0](../AFP_0_Grupo_6_TDII).

### Interfaz del driver `API_GPIO`

```c
typedef uint16_t led_t;
typedef bool     buttonStatus_t;

void           WriteLedOn_GPIO(led_t LDx);   /* Enciende el LED indicado     */
void           WriteLedOff_GPIO(led_t LDx);  /* Apaga el LED indicado        */
void           ToggleLed_GPIO(led_t LDx);    /* Conmuta el LED indicado      */
buttonStatus_t ReadButton_GPIO(void);        /* Devuelve el estado del pulsador */
```

La App 1.2 resuelve lo mismo con una arquitectura de tres capas (aplicación, drivers genéricos y capa de abstracción de plataforma); está explicada en su propio [README](App_3_2_Grupo_6_2026/README.md).

## Pendientes

- **App 1.1:** incorporar el driver GPIO; hoy `main.c` llama a `HAL_GPIO_WritePin`.
- **App 1.3:** pasar el código de `App 1.3` a `App_3_3_Grupo_6_2026` y dejar una sola carpeta.
- **Nombres de funciones:** la App 1.3 usa `WriteLedOn_GPIO` y la App 1.4 `writeLedOn_GPIO`; la App 1.2 usa otro driver (`LED_Write`, `BOTON_DetectarFlancoPresionado`). La consigna pide unificarlos.
- **Nombres de carpetas:** renombrar `App 1.1` a `App_3_1_Grupo_6_2026`.
