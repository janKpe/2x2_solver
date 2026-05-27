#include "../cube/cube.h"

#ifndef PERMUTATIONS_H
#define PERMUTATIONS_H

typedef enum {
    PERM_NONE,
    PERM_R,
    PERM_R_PRIME,
    PERM_R2,
    PERM_L,
    PERM_L_PRIME,
    PERM_L2,
    PERM_U,
    PERM_U_PRIME,
    PERM_U2,
    PERM_D,
    PERM_D_PRIME,
    PERM_D2,
    PERM_F,
    PERM_F_PRIME,
    PERM_F2,
    PERM_B,
    PERM_B_PRIME,
    PERM_B2,
    PERM_COUNT,
} permutation;

void apply_move(sticker_color_t cube[CUBE_ARRAY_LEN], permutation move);

#endif
