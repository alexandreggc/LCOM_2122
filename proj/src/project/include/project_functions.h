#ifndef PROJ_FUNCTIONS_H_INCLUDED
#define PROJ_FUNCTIONS_H_INCLUDED

#include <lcom/lcf.h>
#include <lcom/proj.h>

#include "libs.h"
#include "videocard.h"
#include "keyboard.h"
#include "mouse.h"
#include "timer.h"
#include "leaderboard.h"
#include "makecode_map.h"
#include "rtc.h"
#include "utils.h"
#include "project_macros.h"

/**
 * @defgroup project_functions project_functions
 * @ingroup proj
 * @brief External functions used in the project
 *
 * @{
 */

/**
 * Distance between two points passed in the arguments
 * @param x0 x position of first point
 * @param y0 y position of first point
 * @param x x position of second point
 * @param y y position of second point
 * @return distance between first and second point
 */
int (point_distance)(int x0, int y0, int x, int y);
/**
 * Get random odd number in range passed in the arguments
 * @param start start number of the range
 * @param end end number of the range
 * @return random odd number calculated
 */
int (get_odd_random_in_range)(int start, int end);
/**
 * @}
*/
#endif
