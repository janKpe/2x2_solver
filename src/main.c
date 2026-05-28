#include "cube/cube.h"
#include "permutations/permutations.h"
#include "stdio.h"
#include "string.h"
#include "solving/solving.h"

int main() {
  sticker_color_t testCube[CUBE_ARRAY_LEN];
  memmove(testCube, SOLVED_CUBE, CUBE_ARRAY_LEN * sizeof(sticker_color_t));

  apply_move(testCube, PERM_U2);
  apply_move(testCube, PERM_R);
  apply_move(testCube, PERM_F2);
  apply_move(testCube, PERM_R_PRIME);
  apply_move(testCube, PERM_F);
  apply_move(testCube, PERM_U);
  apply_move(testCube, PERM_F2);
  apply_move(testCube, PERM_R2);
  apply_move(testCube, PERM_U_PRIME);

  permutation solution[SOLUTION_ARR_SIZE] = {0};
  solve_cube(testCube, solution);

  for (size_t i = 0; i < SOLUTION_ARR_SIZE - 1; i++) {
    if (solution[i] == PERM_NONE) {
      break;
    }
    printf("%s ", perm_name(solution[i]));
  }
  printf("\n");
  
  return 0;
}
