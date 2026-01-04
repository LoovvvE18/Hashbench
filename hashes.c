/*
 * Hash candidates registry for bench (no implementations here)
 */

#include <stddef.h>
#include "hashes.h"

/* wrappers implemented in adapters/ */
size_t xxh3_128_wrapper(const void* src, size_t srcSize,
                        void* dst, size_t dstCapacity,
                        void* customPayload);

size_t lemac_wrapper(const void* src, size_t srcSize,
                     void* dst, size_t dstCapacity,
                     void* customPayload);

size_t petitmac_wrapper(const void* src, size_t srcSize,
                        void* dst, size_t dstCapacity,
                        void* customPayload);

/* Update here when adding/removing algorithms */
Bench_Entry const hashCandidates[] = {
    { "XXH3_128",  xxh3_128_wrapper },
    { "lemac",     lemac_wrapper },
    { "petitmac",  petitmac_wrapper },
};

size_t const NB_HASHES = sizeof(hashCandidates) / sizeof(hashCandidates[0]);