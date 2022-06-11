#include "project_functions.h"
#include <math.h>

int (point_distance)(int x0, int y0, int x, int y){
  double x1 = pow((double)(x0-x), 2);
  double y1 = pow((double)(y0-y), 2);
  return (int)sqrt(x1 + y1);
}

int (get_odd_random_in_range)(int start, int end) {
   int num = (rand() % (end - start)) + start; 
   if ((num & 0x1) == 0) num--; 
   return num;
}

