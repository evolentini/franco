#ifndef RELOJ_H
#define RELOJ_H

/* === Headers files inclusions ================================================================ */
#include <stdbool.h>
#include "stdint.h"
/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

#define TICKS_PER_SECOND 1000 // Cuantos ticks debe contar el reloj para sumar un segundo

/* === Public data type declarations =========================================================== */

typedef struct reloj_s * reloj_t;
typedef void (*callback_disparar)(reloj_t reloj,
                                  bool act_desact); // funcion de callback que facilita el testing

/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */

reloj_t ClockCreate(int ticks_por_segundo, callback_disparar funcion_de_disparo);

bool GetClockTime(reloj_t reloj, uint8_t * hora, int size);

bool SetClockTime(reloj_t reloj, const uint8_t * hora, int size);

int RelojNuevoTick(reloj_t reloj);

bool SetAlarmTime(reloj_t reloj, const uint8_t * alarma);

bool GetAlarmTime(reloj_t reloj, uint8_t * alarma);

void VerificarAlarma(reloj_t reloj);

void ToggleHabAlarma(reloj_t reloj);

void PosponerAlarma(reloj_t reloj, uint8_t tiempo);

void CancelarAlarma(reloj_t reloj);

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif /* RELOJ_H */