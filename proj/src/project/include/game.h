#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <lcom/lcf.h>

#include <lcom/proj.h>
#include "project_functions.h"
#include "videocard.h"
#include "keyboard.h"
#include "mouse.h"
#include "timer.h"
#include "rtc.h"
#include "leaderboard.h"
#include "makecode_map.h"
#include "utils.h"
#include "project_macros.h"
#include "keys.h"

/**
 * @defgroup game game
 * @ingroup proj
 * @{
 */

/**
 * Game state enumeration
 */
enum GameState{MENU, PLAY, LEADERBOARD, WON, LOST, EXIT};
/**
 * Game main loop funtion
 * @return 0 if successful exit or 1 otherwise
 */
int(mainLoop)();
/**
 * @}
 */
#endif
