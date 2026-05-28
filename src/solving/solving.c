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

static inline void queue_neighbourghs(permutation path[PERM_ARR_SIZE], ll_queue *queue) {
  size_t arr_len = count_perm_arr(path);
  permutation perm_buffer[PERM_ARR_SIZE];
  memmove(perm_buffer, path, sizeof(permutation) * PERM_ARR_SIZE);
  for (size_t i = 0; i < PERM_COUNT; i++) {
    if (i == PERM_NONE) {
      continue;
    }
    if (arr_len > 0 && perm_same(path[arr_len - 1], i)) {
      continue;
    }
    if (arr_len > 1 && perm_opp_side(path[arr_len - 1], i)) {
      continue;
    }
    // append the neighbourgh move to the current path and queue it
    perm_buffer[arr_len] = i;
    ll_queue_enqueue(queue, perm_buffer);
  }
}

static void write_solution(permutation *from_unsolved,
                    permutation *from_solved, permutation dst[SOLUTION_ARR_SIZE]) {
  size_t unsolved_path_len = count_perm_arr(from_unsolved);
  for (size_t i = 0; i < unsolved_path_len; i++) {
    dst[i] = from_unsolved[i];
  }

  // reverse the path from the unsolved cube to the state where it meets with the solved path
  size_t solved_path_len = count_perm_arr(from_solved);
  for (size_t j = solved_path_len; j > 0; j--) {
    dst[unsolved_path_len + solved_path_len - j] =
        perm_opposite(from_solved[j - 1]);
  }
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

    permutation* dummy;
    if (!hashmap_get(solved_bfs_m, cube, (void**)&dummy)) {
      hashmap_put(solved_bfs_m, cube, solved_bfs_i);
  
      permutation* unsolved_bfs_solution;
      if (hashmap_get(unsolved_bfs_m, cube, (void**)&unsolved_bfs_solution)) {
        write_solution(unsolved_bfs_solution, solved_bfs_i, solution);

        free(solved_bfs_i);
        goto free_maps_and_q;
      }

      queue_neighbourghs(solved_bfs_i, solved_bfs_q);
    }
    
    // do everything from above but from the other side of the graph
    permutation* unsolved_bfs_i = ll_queue_peek_copy(unsolved_bfs_q);
    ll_queue_dequeue(unsolved_bfs_q);
    
    memmove(cube, unsolved_cube, sizeof(sticker_color_t) * CUBE_ARRAY_LEN);
    apply(unsolved_bfs_i, cube);
    
    if (!hashmap_get(unsolved_bfs_m, cube, (void**)&dummy)) {
      hashmap_put(unsolved_bfs_m, cube, unsolved_bfs_i);
  
      permutation* solved_bfs_solution;
      if (hashmap_get(solved_bfs_m, cube, (void**)&solved_bfs_solution)) {
        write_solution(unsolved_bfs_i, solved_bfs_solution, solution);

        free(unsolved_bfs_i);
        free(solved_bfs_i);
        goto free_maps_and_q;
      }
  
      queue_neighbourghs(unsolved_bfs_i, unsolved_bfs_q);
    }

    free(unsolved_bfs_i);
    free(solved_bfs_i);
  }

  free_maps_and_q:
    hashmap_free(unsolved_bfs_m);
    hashmap_free(solved_bfs_m);
    ll_queue_free(solved_bfs_q);
    ll_queue_free(unsolved_bfs_q);
}

