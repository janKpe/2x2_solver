#include <stdbool.h>

#ifndef CUBE_H
#define CUBE_H

#define CUBE_ARRAY_LEN 24

typedef enum {
  YELLOW,
  WHITE,
  BLUE,
  GREEN,
  RED,
  ORANGE
} sticker_color_t;

// clang-format off
enum {
    U0, U1, U2, U3,
    F0, F1, F2, F3,
    R0, R1, R2, R3,
    B0, B1, B2, B3,
    L0, L1, L2, L3,
    D0, D1, D2, D3
};
// clang-format on

// Representation of a 2×2 Rubik’s Cube as a flat array of 24 stickers.
// This solved cube is orinted with yellow to the top and green to the fron.
//
// Each face consists of 4 stickers stored in the following order:
//   [0] top-left, [1] top-right, [2] bottom-left, [3] bottom-right
//
// Procedure to map a physical cube into this array:
//
// 1. Record the top face first, reading stickers in the order:
//    top-left, top-right, bottom-left, bottom-right.
// 2. Without changing the cube’s x orientation, record the side faces
//    by moving the cube clockwise around its y axis:
//      - front face: upper row (left to right), then lower row (left to right)
//      - rotate 
//      - right face: upper row, then lower row
//      - rotate 
//      - back face: upper row, then lower row
//      - rotate 
//      - left face: upper row, then lower row
//      - rotate 
// 3. Rotate the cube 180 degree around the X-axis (X2 turn) so the bottom
//    face becomes the top.
// 4. Record this face using the same order as in step 1
//    (top-left, top-right, bottom-left, bottom-right).
extern const sticker_color_t SOLVED_CUBE[CUBE_ARRAY_LEN];

void print_cube(sticker_color_t cube[CUBE_ARRAY_LEN]);

bool is_cube_solved(sticker_color_t cube[CUBE_ARRAY_LEN]);

#endif