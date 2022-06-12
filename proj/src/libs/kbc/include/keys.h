#ifndef KEYS_H_INCLUDED
#define KEYS_H_INCLUDED

#include <lcom/lcf.h>
#include "keys.h"

/**
 * @defgroup keys keys
 * @ingroup kbc
 * @{
 */

typedef struct keys keys_t;
struct keys{
    uint8_t up_pressed;
    uint8_t left_pressed;
    uint8_t down_pressed;
    uint8_t right_pressed;
    uint8_t space_pressed;
};

/**
 * Keys constructor
 * @return keys struct pointer
 */
keys_t* (keys_ctor)();
/**
 * Keys destructor
 * @param keys keys struct pointer
 */
void (keys_dtor)(keys_t *keys);
/**
 * Clear the keys struct, resetting keys to unpressed state
 * @param keys keys struct pointer
 */
void(clear_keys)(keys_t *keys);

/**
 * @}
 */
#endif
