#ifndef BSP_H
#define BSP_H

/** \brief Librería de la bsp
 **
 ** Declaraciones publicas del módulo bsp
 **
 ** \addtogroup bsp BSP
 ** \brief
 ** @{ */

/* === Headers files inclusions ================================================================ */

#include <digital.h>
#include <pantalla.h>

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

/* === Public data type declarations =========================================================== */

// Se define la estructura board como publica, pero se define un puntero a una estructura constante
// con lo cual board_s no puede ser modificada.
typedef struct board_s {
    digital_output_t buzzer;
    digital_input_t accept;
    digital_input_t cancel;
    digital_input_t set_time;
    digital_input_t set_alarm;
    digital_input_t decrement;
    digital_input_t increment;
    display_t display;

} board_s;

// se cambia el puntero a variable porque no me dejaba modificarlo en el main
typedef board_s * board_t;

/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */

board_t BoardCreate(void);
void SisTick_Init(uint16_t ticks);

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif /* BSP_H */
