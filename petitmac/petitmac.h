#pragma once
#include <stddef.h>
#include <stdint.h>
#include <immintrin.h>

typedef struct {
  __m128i S[6];
} petitmac_state;

typedef struct {
  petitmac_state init;
  __m128i keys[2][11];
  __m128i subkeys[15];
} petitmac_context;

void petitmac_init(petitmac_context *ctx, const uint8_t k[]);
void petitmac_MAC(petitmac_context *ctx, const uint8_t *nonce, const uint8_t *m, size_t mlen, uint8_t *tag);