/*
 * Hash algorithms list for bench
 * Refactored: declarations only (no implementations, no feature macros)
 */

#pragma once

#include <stddef.h>        /* size_t */
#include "bhDisplay.h"     /* Bench_Entry */

#ifdef __cplusplus
extern "C" {
#endif

/* Number of hash candidates in `hashCandidates` */
extern size_t const NB_HASHES;

/* Bench candidates table */
extern Bench_Entry const hashCandidates[];

#ifdef __cplusplus
}
#endif