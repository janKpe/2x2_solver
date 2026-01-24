#include "../libs/data-structures/vector/vector.h"
#include "cube/cube.h"
#include "permutations/permutations.h"
#include "stdio.h"
#include "string.h"

int main() {
  sticker_color_t testCube[CUBE_ARRAY_LEN];
  memmove(testCube, SOLVED_CUBE, CUBE_ARRAY_LEN * sizeof(sticker_color_t));

  print_cube(testCube);

  // sexy move
  apply_move(testCube, PERM_R);
  apply_move(testCube, PERM_U);
  apply_move(testCube, PERM_R_PRIME);
  apply_move(testCube, PERM_U_PRIME);

  apply_move(testCube, PERM_R);
  apply_move(testCube, PERM_U);
  apply_move(testCube, PERM_R_PRIME);
  apply_move(testCube, PERM_U_PRIME);

  apply_move(testCube, PERM_R);
  apply_move(testCube, PERM_U);
  apply_move(testCube, PERM_R_PRIME);
  apply_move(testCube, PERM_U_PRIME);

  apply_move(testCube, PERM_R);
  apply_move(testCube, PERM_U);
  apply_move(testCube, PERM_R_PRIME);
  apply_move(testCube, PERM_U_PRIME);

  apply_move(testCube, PERM_R);
  apply_move(testCube, PERM_U);
  apply_move(testCube, PERM_R_PRIME);
  apply_move(testCube, PERM_U_PRIME);

  apply_move(testCube, PERM_R);
  apply_move(testCube, PERM_U);
  apply_move(testCube, PERM_R_PRIME);
  apply_move(testCube, PERM_U_PRIME);

  print_cube(testCube);
  return 0;
}
