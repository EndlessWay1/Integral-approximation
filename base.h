#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <math.h>

#define KiB(n) ((u64)(n) << 10)
#define MiB(n) ((u64)(n) << 20)
#define GiB(n) ((u64)(n) << 30)

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) < (b)) ? (b) : (a))
#define ALIGN_UP_POW2(n, p) (((u64)(n) + ((u64)(p) - 1)) & (~((u64)(p) - 1)))

// #include "dtypes/dtypes.c"
// #include "Arena/arena.h"
#include "matrix/adv_matrix.h"
#include "matrix/adv_matrix.c"

// #include "hashes_alg/hashes.c"
// #include "bin_search_tree/bin_tree.h"
// #include "hashmap/Map.h"
// #include "hashmap/Map.c"