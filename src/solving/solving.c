#include "../../libs/data-structures/ll_queue/ll_queue.h"
#include "../../libs/data-structures/hashset/hashset.h"
#include "../cube/cube.h"
#include "../permutations/permutations.h"
#include "stdbool.h"
#include "string.h"
#include "solving.h"
#include <stdint.h>
#include <stdio.h>

static hash_value_t cube_hash(void const* ptr) {
  if (!ptr) {
    return 0;
  }

  const uint64_t* v = (const uint64_t*)ptr;
  const uint64_t c1 = 0x87c37b91114253d5ULL;
  const uint64_t c2 = 0x4cf5ad432745937fULL;

  uint64_t h = 0;
  for (int i = 0; i < 3; i++) {
    uint64_t k = v[i] * c1;
    k = (k << 31) | (k >> 33);
    k *= c2;
    h ^= k;
    h = (h << 27) | (h >> 37);
    h = h * 5 + 0x52dce729ULL;
  }

  // Final avalanche mix
  h ^= h >> 33;
  h *= 0xff51afd7ed558ccdULL;
  h ^= h >> 33;
  h *= 0xc4ceb9fe1a85ec53ULL;
  h ^= h >> 33;

  return h;
}

static bool cube_eq(void const* p1, void const* p2) {  
  if (!p1 || !p2) {  
    return false;  
  }  
  return memcmp(p1, p2, sizeof(sticker_color_t) * CUBE_ARRAY_LEN) == 0;
}

static void apply(permutation moves[PERM_ARR_SIZE], sticker_color_t cube[CUBE_ARRAY_LEN]) {
  for (size_t i = 0; i < PERM_ARR_SIZE; i++) {    
    if (moves[i] == PERM_NONE) {
      return;
    }
    apply_move(cube, moves[i]);
  }
}

static size_t count_perm_arr(permutation arr[PERM_ARR_SIZE]) {
  for (size_t i = 0; i < PERM_ARR_SIZE; i++) {
    if (arr[i] == PERM_NONE) {
      return i;
    }
  }
  // we never get here
  exit(2);
}

void solve_cube(sticker_color_t unsolved_cube[CUBE_ARRAY_LEN], permutation solution[SOLUTION_ARR_SIZE]) {
  hashmap* solved_bfs_m;
  hashmap_init(sizeof(sticker_color_t) * CUBE_ARRAY_LEN, sizeof(permutation) * PERM_ARR_SIZE, cube_hash, cube_eq, &solved_bfs_m);

  hashmap* unsolved_bfs_m;
  hashmap_init(sizeof(sticker_color_t) * CUBE_ARRAY_LEN, sizeof(permutation) *  PERM_ARR_SIZE, cube_hash, cube_eq, &unsolved_bfs_m);

  // TODO ways to make this faster:
  // - dont just queue a list of permutations, make a struct that contains the cube and a move to apply that move to
  // - or create a hashmap with a list of solves as keys and a cube as value

  ll_queue* solved_bfs_q = ll_queue_init(sizeof(permutation) * PERM_ARR_SIZE);
  ll_queue* unsolved_bfs_q = ll_queue_init(sizeof(permutation)* PERM_ARR_SIZE);

  permutation empty_perms[PERM_ARR_SIZE] = {0};
  ll_queue_enqueue(solved_bfs_q, empty_perms);
  ll_queue_enqueue(unsolved_bfs_q, empty_perms);

  while (!ll_queue_is_empty(solved_bfs_q) || !ll_queue_is_empty(unsolved_bfs_q)) {
    permutation* solved_bfs_i = ll_queue_peek_copy(solved_bfs_q);
    ll_queue_dequeue(solved_bfs_q);

    sticker_color_t cube[CUBE_ARRAY_LEN];
    memmove(cube, SOLVED_CUBE, sizeof(sticker_color_t) * CUBE_ARRAY_LEN);
    apply(solved_bfs_i, cube);

    hashmap_put(solved_bfs_m, cube, solved_bfs_i);

    permutation* unsolved_bfs_solution;
    if (hashmap_get(unsolved_bfs_m, cube, (void**)&unsolved_bfs_solution)) {
      size_t unsolved_path_len = count_perm_arr(unsolved_bfs_solution);
      for (size_t i = 0; i < unsolved_path_len; i++) {
        solution[i] = unsolved_bfs_solution[i];
      }

      size_t solved_path_len = count_perm_arr(solved_bfs_i);
      for (size_t j = solved_path_len; j > 0; j--) {
        solution[unsolved_path_len + solved_path_len - j] = perm_opposite(solved_bfs_i[j -1]);
      }

      hashmap_free(unsolved_bfs_m);
      hashmap_free(solved_bfs_m);
      ll_queue_free(solved_bfs_q);
      ll_queue_free(unsolved_bfs_q);
      return;
    }

    size_t arr_len = count_perm_arr(solved_bfs_i);
    permutation perm_buffer[PERM_ARR_SIZE];
    memmove(perm_buffer, solved_bfs_i, sizeof(permutation) * PERM_ARR_SIZE);
    for (size_t i = 0; i < PERM_COUNT; i++) {
      if (i == PERM_NONE || perm_same(solved_bfs_i[arr_len-1], i)) {
        continue;
      }
      if (arr_len > 1 && perm_opp_side(solved_bfs_i[arr_len - 1], i)) {
        continue;
      }
      // append the neighbourgh move to the current path
      perm_buffer[arr_len] = i;
      // TODO create a hashset to check if we already have tried a row of permutatoins
      ll_queue_enqueue(solved_bfs_q, perm_buffer);
    }

    // now do everithing from above but from the other side of the graph
    permutation* unsolved_bfs_i = ll_queue_peek_copy(unsolved_bfs_q);
    ll_queue_dequeue(unsolved_bfs_q);

    memmove(cube, unsolved_cube, sizeof(sticker_color_t) * CUBE_ARRAY_LEN);
    apply(unsolved_bfs_i, cube);

    hashmap_put(unsolved_bfs_m, cube, unsolved_bfs_i);

    permutation* solved_bfs_solution;
    if (hashmap_get(solved_bfs_m, cube, (void**)&solved_bfs_solution)) {
      size_t unsolved_path_len = count_perm_arr(unsolved_bfs_i);
      for (size_t i = 0; i < unsolved_path_len; i++) {
        solution[i] = unsolved_bfs_i[i];
      }
      
      size_t solved_path_len = count_perm_arr(solved_bfs_solution);
      for (size_t j = solved_path_len; j > 0 ; j--) {
        solution[unsolved_path_len + solved_path_len - j] = perm_opposite(solved_bfs_solution[j -1]);
      }

      hashmap_free(unsolved_bfs_m);
      hashmap_free(solved_bfs_m);
      ll_queue_free(solved_bfs_q);
      ll_queue_free(unsolved_bfs_q);
      return;
    }

    arr_len = count_perm_arr(unsolved_bfs_i);

    memmove(perm_buffer, unsolved_bfs_i, sizeof(permutation) * PERM_ARR_SIZE);
    for (size_t i = 0; i < PERM_COUNT; i++) {
      if (i == PERM_NONE || perm_same(unsolved_bfs_i[arr_len-1], i)) {
        continue;
      }
      if (arr_len > 1 && perm_opp_side(unsolved_bfs_i[arr_len - 1], i)) {
        continue;
      }
      // append the neighbourgh move to the current path
      perm_buffer[arr_len] = i;
      ll_queue_enqueue(unsolved_bfs_q, perm_buffer);
    }

    free(unsolved_bfs_i);
    free(solved_bfs_i);
  }


}
