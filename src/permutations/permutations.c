#include "permutations.h"
#include "../cube/cube.h"

void apply_move(sticker_color_t cube[CUBE_ARRAY_LEN], permutation move) {
    sticker_color_t temp1, temp2, temp;

    switch (move) {
        case PERM_R:
            temp1 = cube[U3];
            temp2 = cube[U1];

            cube[U1] = cube[F1];
            cube[U3] = cube[F3];

            cube[F1] = cube[D1];
            cube[F3] = cube[D3];

            cube[D1] = cube[B2];
            cube[D3] = cube[B0];

            cube[B0] = temp1;
            cube[B2] = temp2;

            temp = cube[R0];
            cube[R0] = cube[R2];
            cube[R2] = cube[R3];
            cube[R3] = cube[R1];
            cube[R1] = temp;
            break;

        case PERM_R_PRIME:
            temp1 = cube[U1];
            temp2 = cube[U3];

            cube[U1] = cube[B2];
            cube[U3] = cube[B0];

            cube[B0] = cube[D3];
            cube[B2] = cube[D1];

            cube[D1] = cube[F1];
            cube[D3] = cube[F3];

            cube[F1] = temp1;
            cube[F3] = temp2;

            temp = cube[R0];
            cube[R0] = cube[R1];
            cube[R1] = cube[R3];
            cube[R3] = cube[R2];
            cube[R2] = temp;
            break;

        case PERM_R2:
            temp = cube[U1];
            cube[U1] = cube[D1];
            cube[D1] = temp;
            temp = cube[U3];
            cube[U3] = cube[D3];
            cube[D3] = temp;

            temp = cube[F1];
            cube[F1] = cube[B2];
            cube[B2] = temp;
            temp = cube[F3];
            cube[F3] = cube[B0];
            cube[B0] = temp;

            temp = cube[R0];
            cube[R0] = cube[R3];
            cube[R3] = temp;
            temp = cube[R1];
            cube[R1] = cube[R2];
            cube[R2] = temp;
            break;

        case PERM_L:
            temp1 = cube[U0];
            temp2 = cube[U2];

            cube[U0] = cube[B3];
            cube[U2] = cube[B1];

            cube[B1] = cube[D2];
            cube[B3] = cube[D0];

            cube[D0] = cube[F0];
            cube[D2] = cube[F2];

            cube[F0] = temp1;
            cube[F2] = temp2;

            temp = cube[L0];
            cube[L0] = cube[L2];
            cube[L2] = cube[L3];
            cube[L3] = cube[L1];
            cube[L1] = temp;
            break;

        case PERM_L_PRIME:
            temp1 = cube[U2];
            temp2 = cube[U0];

            cube[U0] = cube[F0];
            cube[U2] = cube[F2];

            cube[F0] = cube[D0];
            cube[F2] = cube[D2];

            cube[D0] = cube[B3];
            cube[D2] = cube[B1];

            cube[B1] = temp1;
            cube[B3] = temp2;

            temp = cube[L0];
            cube[L0] = cube[L1];
            cube[L1] = cube[L3];
            cube[L3] = cube[L2];
            cube[L2] = temp;
            break;

        case PERM_L2:
            temp = cube[U0];
            cube[U0] = cube[D0];
            cube[D0] = temp;
            temp = cube[U2];
            cube[U2] = cube[D2];
            cube[D2] = temp;

            temp = cube[F0];
            cube[F0] = cube[B3];
            cube[B3] = temp;
            temp = cube[F2];
            cube[F2] = cube[B1];
            cube[B1] = temp;

            temp = cube[L0];
            cube[L0] = cube[L3];
            cube[L3] = temp;
            temp = cube[L1];
            cube[L1] = cube[L2];
            cube[L2] = temp;
            break;

        case PERM_U:
            temp1 = cube[F0];
            temp2 = cube[F1];

            cube[F0] = cube[R0];
            cube[F1] = cube[R1];

            cube[R0] = cube[B0];
            cube[R1] = cube[B1];

            cube[B0] = cube[L0];
            cube[B1] = cube[L1];

            cube[L0] = temp1;
            cube[L1] = temp2;

            temp = cube[U0];
            cube[U0] = cube[U2];
            cube[U2] = cube[U3];
            cube[U3] = cube[U1];
            cube[U1] = temp;
            break;

        case PERM_U_PRIME:
            temp1 = cube[F0];
            temp2 = cube[F1];

            cube[F0] = cube[L0];
            cube[F1] = cube[L1];

            cube[L0] = cube[B0];
            cube[L1] = cube[B1];

            cube[B0] = cube[R0];
            cube[B1] = cube[R1];

            cube[R0] = temp1;
            cube[R1] = temp2;

            temp = cube[U0];
            cube[U0] = cube[U1];
            cube[U1] = cube[U3];
            cube[U3] = cube[U2];
            cube[U2] = temp;
            break;

        case PERM_U2:
            temp = cube[F0];
            cube[F0] = cube[B0];
            cube[B0] = temp;
            temp = cube[F1];
            cube[F1] = cube[B1];
            cube[B1] = temp;

            temp = cube[R0];
            cube[R0] = cube[L0];
            cube[L0] = temp;
            temp = cube[R1];
            cube[R1] = cube[L1];
            cube[L1] = temp;

            temp = cube[U0];
            cube[U0] = cube[U3];
            cube[U3] = temp;
            temp = cube[U1];
            cube[U1] = cube[U2];
            cube[U2] = temp;
            break;

        case PERM_D:
            temp1 = cube[F2];
            temp2 = cube[F3];

            cube[F2] = cube[L2];
            cube[F3] = cube[L3];

            cube[L2] = cube[B2];
            cube[L3] = cube[B3];

            cube[B2] = cube[R2];
            cube[B3] = cube[R3];

            cube[R2] = temp1;
            cube[R3] = temp2;

            temp = cube[D0];
            cube[D0] = cube[D2];
            cube[D2] = cube[D3];
            cube[D3] = cube[D1];
            cube[D1] = temp;
            break;

        case PERM_D_PRIME:
            temp1 = cube[F2];
            temp2 = cube[F3];

            cube[F2] = cube[R2];
            cube[F3] = cube[R3];

            cube[R2] = cube[B2];
            cube[R3] = cube[B3];

            cube[B2] = cube[L2];
            cube[B3] = cube[L3];

            cube[L2] = temp1;
            cube[L3] = temp2;

            temp = cube[D0];
            cube[D0] = cube[D1];
            cube[D1] = cube[D3];
            cube[D3] = cube[D2];
            cube[D2] = temp;
            break;

        case PERM_D2:
            temp = cube[F2];
            cube[F2] = cube[B2];
            cube[B2] = temp;
            temp = cube[F3];
            cube[F3] = cube[B3];
            cube[B3] = temp;

            temp = cube[R2];
            cube[R2] = cube[L2];
            cube[L2] = temp;
            temp = cube[R3];
            cube[R3] = cube[L3];
            cube[L3] = temp;

            temp = cube[D0];
            cube[D0] = cube[D3];
            cube[D3] = temp;
            temp = cube[D1];
            cube[D1] = cube[D2];
            cube[D2] = temp;
            break;

        case PERM_F:
            temp1 = cube[U2];
            temp2 = cube[U3];

            cube[U2] = cube[L1];
            cube[U3] = cube[L3];

            cube[L1] = cube[D0];
            cube[L3] = cube[D1];

            cube[D0] = cube[R2];
            cube[D1] = cube[R0];

            cube[R0] = temp1;
            cube[R2] = temp2;

            temp = cube[F0];
            cube[F0] = cube[F2];
            cube[F2] = cube[F3];
            cube[F3] = cube[F1];
            cube[F1] = temp;
            break;

        case PERM_F_PRIME:
            temp1 = cube[U3];
            temp2 = cube[U2];

            cube[U2] = cube[R0];
            cube[U3] = cube[R2];

            cube[R0] = cube[D1];
            cube[R2] = cube[D0];

            cube[D0] = cube[L1];
            cube[D1] = cube[L3];

            cube[L1] = temp1;
            cube[L3] = temp2;

            temp = cube[F0];
            cube[F0] = cube[F1];
            cube[F1] = cube[F3];
            cube[F3] = cube[F2];
            cube[F2] = temp;
            break;

        case PERM_F2:
            temp = cube[U2];
            cube[U2] = cube[D1];
            cube[D1] = temp;
            temp = cube[U3];
            cube[U3] = cube[D0];
            cube[D0] = temp;

            temp = cube[L1];
            cube[L1] = cube[R0];
            cube[R0] = temp;
            temp = cube[L3];
            cube[L3] = cube[R2];
            cube[R2] = temp;

            temp = cube[F0];
            cube[F0] = cube[F3];
            cube[F3] = temp;
            temp = cube[F1];
            cube[F1] = cube[F2];
            cube[F2] = temp;
            break;

        case PERM_B:
            temp1 = cube[U1];
            temp2 = cube[U0];

            cube[U0] = cube[R1];
            cube[U1] = cube[R3];

            cube[R1] = cube[D3];
            cube[R3] = cube[D2];

            cube[D2] = cube[L0];
            cube[D3] = cube[L2];

            cube[L0] = temp1;
            cube[L2] = temp2;

            temp = cube[B0];
            cube[B0] = cube[B2];
            cube[B2] = cube[B3];
            cube[B3] = cube[B1];
            cube[B1] = temp;
            break;

        case PERM_B_PRIME:
            temp1 = cube[U0];
            temp2 = cube[U1];

            cube[U0] = cube[L2];
            cube[U1] = cube[L0];

            cube[L0] = cube[D2];
            cube[L2] = cube[D3];

            cube[D2] = cube[R3];
            cube[D3] = cube[R1];

            cube[R1] = temp1;
            cube[R3] = temp2;

            temp = cube[B0];
            cube[B0] = cube[B1];
            cube[B1] = cube[B3];
            cube[B3] = cube[B2];
            cube[B2] = temp;
            break;

        case PERM_B2:
            temp = cube[U0];
            cube[U0] = cube[D3];
            cube[D3] = temp;
            temp = cube[U1];
            cube[U1] = cube[D2];
            cube[D2] = temp;

            temp = cube[R1];
            cube[R1] = cube[L2];
            cube[L2] = temp;
            temp = cube[R3];
            cube[R3] = cube[L0];
            cube[L0] = temp;

            temp = cube[B0];
            cube[B0] = cube[B3];
            cube[B3] = temp;
            temp = cube[B1];
            cube[B1] = cube[B2];
            cube[B2] = temp;
            break;
        default:
            break;
    }
}
