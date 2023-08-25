/** \brief Brief description of the file
 **
 ** Full file description
 **
 ** \addtogroup name Module denomination
 ** \brief Brief description of the module
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "pantalla.h"
#include "string.h"
#include "reloj.h"

/* === Macros definitions ====================================================================== */

#if !defined(DISPLAY_MAX_DIGITS)
    #define DISPLAY_MAX_DIGITS 8
#endif

/* === Private data type declarations ========================================================== */

struct display_s {
    uint8_t digits;       // cantidad de digitos del display
    uint8_t active_digit; // digito activo

    // Cada byte de 'memory' tiene los segmentos que se quieren encender de un digito en
    // particular. DisplayRefresh accede a esa memoria, recorriendola, y sacando los segmentos de
    // cada digito en particular
    uint8_t memory[DISPLAY_MAX_DIGITS];
    struct display_driver_s driver[1];
    uint8_t flashing_from;
    uint8_t flashing_to;
    uint16_t flashing_count;
    uint16_t flashing_factor;
};

/* === Private variable declarations =========================================================== */

static const uint8_t IMAGES[] = {
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F,
    SEGMENT_B | SEGMENT_C,
    SEGMENT_A | SEGMENT_B | SEGMENT_D | SEGMENT_E | SEGMENT_G,
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_G,
    SEGMENT_B | SEGMENT_C | SEGMENT_F | SEGMENT_G,
    SEGMENT_A | SEGMENT_C | SEGMENT_D | SEGMENT_F | SEGMENT_G,
    SEGMENT_A | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G,
    SEGMENT_A | SEGMENT_B | SEGMENT_C,
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G,
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_F | SEGMENT_G,
};

/* === Private function declarations =========================================================== */

display_t DisplayAllocate();

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */
display_t DisplayAllocate() {

    static struct display_s instances[1] = {0};
    return &instances[0];
}
/* === Public function implementation ========================================================== */

display_t DisplayCreate(uint8_t digits, display_driver_t driver) {

    display_t display = DisplayAllocate();
    display->digits = digits;           // cantidad de digitos que tiene el display (4)
    display->active_digit = digits - 1; // comienza el ultimo digito como activo (3)
    display->flashing_count = 0;
    display->flashing_factor = 0;
    display->flashing_from = 0;
    display->flashing_to = 0;
    memcpy(display->driver, driver, sizeof(display->driver));
    memset(display->memory, 0, sizeof(display->memory)); // limpia la memoria
    display->driver->ScreenTurnOff();                    // apaga todos los digitos

    return display;
}

void DisplayWriteBCD(display_t display, uint8_t * numbers, uint8_t size) {

    // memset(display->memory, 0, sizeof(display->memory));

    for (size_t i = 0; i <= sizeof(display->memory) - 1; i++) {

        display->memory[i] &= 0b10000000;
        // display->memory[i] &= 0;
    }

    // display->memory[] &= 129;

    for (int i = 0; i < size; i++) {
        if (i >= display->digits)
            break;
        // Me estaba cleareando el msb de memory (punto)
        (display->memory[i]) |= (IMAGES[numbers[i]]);
    }
}

void DisplayRefresh(display_t display) {
    // Suponiendo un duty factor de 50%: la primera mitad del segundo apago algunos digitos y la
    // segunda mitad prendo todos

    uint8_t segments = 0;

    display->driver->ScreenTurnOff();
    display->active_digit = (display->active_digit + 1) % display->digits;

    segments = display->memory[display->active_digit];

    if (display->flashing_factor) {

        if (display->active_digit == 0) {
            display->flashing_count = (display->flashing_count + 1) %
                                      (display->flashing_factor); // f(display->flashing_factor +1)
        }

        if (display->active_digit >= display->flashing_from &&
            display->active_digit <= display->flashing_to) {
            if (display->flashing_count > (display->flashing_factor / 2)) {
                segments = 0;
                // segments = display->memory[display->active_digit] & 0b10000000;
            }
        }
    }

    display->driver->SegmentsTurnOn(segments);
    display->driver->DigitTurnOn(display->active_digit);
}

void DisplayFlashDigits(display_t display, uint8_t from, uint8_t to, uint16_t factor) {

    // Se usan los mod por si reciben valores fuera del rango permitido
    display->flashing_from = from % (DISPLAY_MAX_DIGITS + 1);
    display->flashing_to = to % (DISPLAY_MAX_DIGITS + 1);
    display->flashing_count = 0;
    display->flashing_factor = factor;
}

void DisplayToggleDot(display_t display, uint8_t digit_dot) {

    display->memory[digit_dot] ^= 1 << 7;
}

void DisplaySetDot(display_t display, uint8_t digit_dot) {

    uint8_t mask = 0x01;
    for (int i = 0; i < 8; i++) {
        if (digit_dot & mask) {
            display->memory[i] |= 1 << 7;
        }
        mask <<= 1;
    }
}

void DisplayClearDot(display_t display, uint8_t digit_dot) {

    uint8_t mask = 0x01;
    for (int i = 0; i < 8; i++) {
        if (digit_dot & mask) {
            display->memory[i] &= 0 << 7;
        }
        mask <<= 1;
    }
}

/* === End of documentation ====================================================================
 */