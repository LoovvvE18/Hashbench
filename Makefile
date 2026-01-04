# ################################################################
# xxHash benchHash Makefile
# Refactored: local vendor dirs + adapters + explicit object list
# ################################################################

CPPFLAGS += -I.      # only bench local headers (and subfolders via relative includes)

CFLAGS   ?= -O3
CFLAGS   += -Wall -Wextra -Wstrict-aliasing=1 \
            -std=c99
CFLAGS   += $(MOREFLAGS)
CFLAGS   += -maes

CXXFLAGS += -maes
CXXFLAGS ?= -O3
LDFLAGS  += $(MOREFLAGS)

OBJ_LIST  = \
  main.o \
  bhDisplay.o \
  benchHash.o \
  benchfn.o \
  timefn.o \
  hashes.o \
  adapters/xxh3_128.o \
  adapters/lemac.o \
  adapters/petitmac.o \
  xxhash/xxhash.o \
  lemac/lemac.o \
  petitmac/petitmac.o

default: benchHash
all: benchHash

benchHash32: CFLAGS   += -m32
benchHash32: CXXFLAGS += -m32

benchHash_avx2: CFLAGS   += -mavx2
benchHash_avx2: CXXFLAGS += -mavx2

benchHash_avx512: CFLAGS   += -mavx512f
benchHash_avx512: CXXFLAGS += -mavx512f

benchHash_rvv: CFLAGS   += -march=rv64gcv -O2
benchHash_rvv: CXXFLAGS += -march=rv64gcv -O2

# (Removed HARDWARE_SUPPORT mode: keep bench selection explicit via Makefile edits)

benchHash benchHash32 benchHash_avx2 benchHash_avx512 benchHash_nosimd benchHash_rvv: $(OBJ_LIST)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

main.o: bhDisplay.h hashes.h
bhDisplay.o: bhDisplay.h benchHash.h
benchHash.o: benchHash.h

# ensure subdir objects build reliably
%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	$(RM) *.o benchHash benchHash32 benchHash_avx2 benchHash_avx512 benchHash_hw benchHash_rvv
	$(RM) hashes.o
	$(RM) adapters/*.o
	$(RM) xxhash/*.o
	$(RM) lemac/*.o
	$(RM) petitmac/*.o