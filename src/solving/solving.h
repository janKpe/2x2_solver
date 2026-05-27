#include "../cube/cube.h"
#include "string.h"
#include "../permutations/permutations.h"

#ifndef SOLVING_H
#define SOLVING_H

#define PERM_ARR_SIZE 9

#define SOLUTION_ARR_SIZE 18

// Solves a cube using bi directional bfs.
// The solution is writen into solution which should be big enough to hold SOLUTION_ARR_SIZE elements of permutation.
// Only the required moves are writen into solution so soution should be 0 initialized.
void solve_cube(sticker_color_t cube[CUBE_ARRAY_LEN], permutation solution[SOLUTION_ARR_SIZE]);

#endif