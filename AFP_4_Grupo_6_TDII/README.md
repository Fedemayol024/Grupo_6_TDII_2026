# AFP 4 — Funciones no bloqueantes con SysTick

**Técnicas Digitales II — UTN FRT — Grupo 6 — 2026**

En esta actividad las aplicaciones de la [AFP 3](../AFP_3_Grupo_6_TDII) se vuelven a entregar con un **driver de retardos no bloqueantes**, que reemplaza a `HAL_Delay()`. El comportamiento visible es el mismo, pero el programa ya no se detiene mientras espera.

## Objetivos de la actividad

- Implementar un módulo de software para trabajar con retardos no bloqueantes.
- Aplicar el concepto de funciones no bloqueantes en aplicaciones concretas.
- Desarrollar un driver de funciones no bloqueantes y usarlo en las aplicaciones.

## Por qué hace falta

`HAL_Delay()` detiene el programa durante toda la espera: mientras un LED está "esperando", el micro no puede leer el pulsador ni atender otra tarea. Con retardos no bloqueantes el lazo principal sigue girando y solo pregunta si el tiempo ya se cumplió. El resultado más visible es que el pulsador responde al instante.

## Qué se incorpora

Un driver con tres funciones, que usa `HAL_GetTick()` (contador que se incrementa cada 1 ms) como base de tiempo:

```c
typedef uint32_t tick_t;
typedef bool     bool_t;

typedef struct {
    tick_t startTime;   /* Marca de tiempo en la que empezó a contar */
    tick_t duration;    /* Duración del retardo en ms                */
    bool_t running;     /* Indica si el retardo está contando        */
} delay_t;

void   delayInit(delay_t *delay, tick_t duration);
bool_t delayRead(delay_t *delay);
void   delayWrite(delay_t *delay, tick_t duration);
```

| Función | Qué debe hacer |
| :--- | :--- |
| `delayInit` | Carga la duración y deja `running` en `false`. No inicia el conteo. |
| `delayRead` | Si `running` es `false`, toma la marca de tiempo y lo pone en `true`. Si es `true`, devuelve si ya transcurrió la duración; cuando se cumple, vuelve `running` a `false`. |
| `delayWrite` | Cambia la duración de un retardo existente. |

Pasos de la consigna: primero se escriben y prueban las funciones en `main.c`; después se mueven a un archivo fuente y su cabecera dentro de `Drivers/API`; por último cada integrante integra el driver en su aplicación y elimina `HAL_Delay()`.

La consigna pide además que todo el grupo use **el mismo nombre para el driver y para sus funciones**.

## Aplicaciones

| App | Responsable | Placa | Carpeta | Archivos del driver |
| :---: | :--- | :--- | :--- | :--- |
| 1.1 | Santino Machin | NUCLEO-F429ZI | [`App_4_1_Grupo_6_2026`](App_4_1_Grupo_6_2026) | `header.h` / `fuente.c` |
| 1.2 | Carlos Mamani Flores | NUCLEO-F439ZI | [`App_4_2_Grupo_6_2026`](App_4_2_Grupo_6_2026) | `nb_delay.h` / `nb_delay.c` |
| 1.3 | Federico Mayol | NUCLEO-F767ZI | [`App_4_3_Grupo_6_2026`](App_4_3_Grupo_6_2026) | `API_Delay.h` / `API_Delay.c` |
| 1.4 | Lucas Emanuel Cusi | STM32F401RC | [`App_4_4_Grupo_6_2026`](App_4_4_Grupo_6_2026) | `API_Delay.h` / `API_Delay.c` |

### Qué debe cumplir cada aplicación

| App | Comportamiento (igual al de la AFP 0) | Tarea en esta actividad |
| :---: | :--- | :--- |
| 1.1 | Secuencia verde → azul → rojo, 200 ms encendido y 200 ms apagado | Un retardo no bloqueante marca los tiempos de encendido y apagado |
| 1.2 | La secuencia invierte su sentido con cada pulsación | Retardos no bloqueantes para la secuencia y para el antirrebote del pulsador |
| 1.3 | Cuatro secuencias; el pulsador pasa a la siguiente | Un retardo por secuencia, y uno por LED en la secuencia 3 (100, 300 y 600 ms) |
| 1.4 | Parpadeo conjunto; el pulsador cambia entre 100, 250, 500 y 1000 ms | Un único retardo cuya duración se cambia con `delayWrite` |

El detalle de cada secuencia está en el [README de la AFP 0](../AFP_0_Grupo_6_TDII).

## Estado

Las cuatro aplicaciones están entregadas y presentadas.

## Observaciones

Se conservan como se presentaron:

- **Nombre del driver:** hoy hay tres (`header`/`fuente`, `nb_delay` y `API_Delay`) y la App 1.2 usa `nb_delay_init`/`nb_delay_read`/`nb_delay_write` en lugar de `delayInit`/`delayRead`/`delayWrite`. En la [AFP 5](../AFP_5_Grupo_6_TDII) se unificó como `API_delay`.
- **App 1.1:** todavía maneja los LEDs con `HAL_GPIO_WritePin` en lugar del driver GPIO de la AFP 3.
- **App 1.3:** la secuencia 4 lee el LED con `HAL_GPIO_ReadPin`; podría resolverse solo con el driver.
