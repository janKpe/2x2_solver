#include "cube.h"
#include "stdio.h"

// clang-format off
const sticker_color_t SOLVED_CUBE[CUBE_ARRAY_LEN] = {
    // Top face
    YELLOW, // top left
    YELLOW, // top right
    YELLOW, // bottom left
    YELLOW, // bottom right
    GREEN,  GREEN,  GREEN,  GREEN,  // Front face
    ORANGE, ORANGE, ORANGE, ORANGE, // Right face
    BLUE,   BLUE,   BLUE,   BLUE,   // Back face
    RED,    RED,    RED,    RED,    // Left face
    WHITE,  WHITE,  WHITE,  WHITE   // Bottom face
};
// clang-format on

void print_cube(sticker_color_t cube[CUBE_ARRAY_LEN]) {
  for (size_t i = 0; i < CUBE_ARRAY_LEN; i++) {
    switch (cube[i]) {
    case YELLOW:
      printf("Y");
      break;
    case WHITE:
      printf("W");
      break;
    case BLUE:
      printf("B");
      break;
    case GREEN:
      printf("G");
      break;
    case RED:
      printf("R");
      break;
    case ORANGE:
      printf("O");
      break;
    default:
      printf("?");
      break;
    }

    if ((i + 1) % 4 == 0) {
      printf(" ");
    }
  }
  printf("\n");
}
