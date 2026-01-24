#include "../cube/cube.h"

#ifndef PERMUTATIONS_H
#define PERMUTATIONS_H

typedef enum {
    PERM_R,
    PERM_R_PRIME,
    PERM_L,
    PERM_L_PRIME,
    PERM_U,
    PERM_U_PRIME,
    PERM_D,
    PERM_D_PRIME,
    PERM_F,
    PERM_F_PRIME,
    PERM_B,
    PERM_B_PRIME
} permutation;

void apply_move(sticker_color_t cube[CUBE_ARRAY_LEN], permutation move);

#endif
