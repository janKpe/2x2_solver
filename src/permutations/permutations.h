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

// Returns the opposite permutation the reverses p.
// Eg. perm_opposite(PERM_R) returns PERM_R_PRIME
permutation perm_opposite(permutation p);

// Returns the name as a constant string.
const char* perm_name(permutation p);

// Returns true if both permutations are one the same side,
// and could therefore be put into one.
bool perm_same(permutation p1, permutation p2);

// Returns true if p1 turns the opposide side as p2.
// E.g PERM_L and PERM_R
bool perm_opp_side(permutation p1, permutation p2);

#endif
