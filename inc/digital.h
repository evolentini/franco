#ifndef TEMPLATE_H
#define TEMPLATE_H

/** \brief Modulo: digital
 **
 ** Declaraciones publicas del modulo: digital
 **
 ** \addtogroup digital Modulo digital
 ** \brief -
 ** @{ */

/* === Headers files inclusions ================================================================ */
#include <stdint.h>
#include <stdbool.h>
/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

typedef struct digital_output_s * digital_output_t;
typedef struct digital_input_s * digital_input_t;

/* === Public data type declarations =========================================================== */

/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */
digital_output_t DigitalOutputCreate(uint8_t port, uint8_t pin);

void DigitalOutputActivate(digital_output_t output);

void DigitalOutputDeactivate(digital_output_t output);

void DigitalOutputToggle(digital_output_t output);

digital_input_t DigitalInputCreate(uint8_t port, uint8_t pin, bool inverted);

bool DigitalInputGetState(digital_input_t input);

bool DigitalInputHasChanged(digital_input_t input);

bool DigitalInputHasActivated(digital_input_t input);

bool DigitalInputHasDeactivated(digital_input_t input);
/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif /* TEMPLATE_H */
