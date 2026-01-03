/*
 * Adapter: LeMac -> BMK_benchfn_t
 *
 * - Uses a fixed key and fixed nonce for benchmarking.
 * - Optionally writes tag to dst if capacity allows.
 * - Returns low64 of tag via return value (latency path requirement).
 */

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "../lemac/lemac.h"

/* keep a global context to avoid re-init cost on every call */
static context g_lemac_ctx;
static int g_lemac_inited = 0;

static void lemac_lazy_init(void)
{
    if (g_lemac_inited) return;
    uint8_t key[16] = {0};   /* fixed key for bench */
    lemac_init(&g_lemac_ctx, key);
    g_lemac_inited = 1;
}

size_t lemac_wrapper(const void* src, size_t srcSize,
                     void* dst, size_t dstCapacity,
                     void* customPayload)
{
    (void)customPayload;
    lemac_lazy_init();

    uint8_t nonce[16] = {0}; /* fixed nonce for bench */
    uint8_t tag[16];

    lemac_MAC(&g_lemac_ctx, nonce, (const uint8_t*)src, srcSize, tag);

    if (dst != NULL && dstCapacity >= 16) {
        memcpy(dst, tag, 16);
    }

    /* return low64 */
    uint64_t lo;
    memcpy(&lo, tag, sizeof(lo));
    return (size_t)lo;
}