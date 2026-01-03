/*
 * Adapter: XXH3 128-bit -> BMK_benchfn_t
 *
 * Keeps bench interface uniform:
 *   size_t fn(const void*, size_t, void*, size_t, void*)
 *
 * Returns low64 of XXH128 hash to satisfy latency bench requirement:
 * result must be expressed via return value.
 */

#include <stddef.h>
#include "../xxhash/xxhash.h"

size_t xxh3_128_wrapper(const void* src, size_t srcSize,
                        void* dst, size_t dstCapacity,
                        void* customPayload)
{
    (void)dst;
    (void)dstCapacity;
    (void)customPayload;

    XXH128_hash_t const h = XXH3_128bits(src, srcSize);
    return (size_t)h.low64;
}