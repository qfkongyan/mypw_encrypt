#ifndef __PW_ENCRYPT_H__
#define __PW_ENCRYPT_H__


#define IS_IN_UBOOT 0

#if IS_IN_UBOOT
#include <common.h>
#include <malloc.h>
#include <linux/string.h>
#define strtoul simple_strtoul
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#endif

# define FIX_ALIASING __attribute__((__may_alias__))
typedef uint64_t bb__aliased_uint64_t FIX_ALIASING;

typedef struct md5_ctx_t {
        uint8_t wbuffer[64]; /* always correctly aligned for uint64_t */
        void (*process_block)(struct md5_ctx_t*);
        uint64_t total64;    /* must be directly before hash[] */
        uint32_t hash[8];    /* 4 elements for md5, 5 for sha1, 8 for sha256 */
} md5_ctx_t;
typedef struct md5_ctx_t sha1_ctx_t;
typedef struct md5_ctx_t sha256_ctx_t;
typedef struct sha512_ctx_t {
        uint64_t total64[2];  /* must be directly before hash[] */
        uint64_t hash[8];
        uint8_t wbuffer[128]; /* always correctly aligned for uint64_t */
} sha512_ctx_t;


#define ALWAYS_INLINE inline
#define  ENABLE_USE_BB_CRYPT_SHA 1
#define  ENABLE_DEBUG 1

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) ((unsigned)(sizeof(x) / sizeof((x)[0])))
#endif

/* SWAP_LEnn means "convert CPU<->little_endian by swapping bytes" */
#define BB_BIG_ENDIAN 0
#define BB_LITTLE_ENDIAN (!BB_BIG_ENDIAN)
#define	bswap_8(x)	((x) & 0xff)
#define	bswap_16(x)	((bswap_8(x) << 8) | bswap_8((x) >> 8))
#define	bswap_32(x)	((bswap_16(x) << 16) | bswap_16((x) >> 16))
#define	bswap_64(x)	((bswap_32(x) << 32) | bswap_32((x) >> 32))
#if BB_BIG_ENDIAN
# define SWAP_BE16(x) (x)
# define SWAP_BE32(x) (x)
# define SWAP_BE64(x) (x)
# define SWAP_LE16(x) bswap_16(x)
# define SWAP_LE32(x) bswap_32(x)
# define SWAP_LE64(x) bswap_64(x)
# define IF_BIG_ENDIAN(...) __VA_ARGS__
# define IF_LITTLE_ENDIAN(...)
#else
# define SWAP_BE16(x) bswap_16(x)
# define SWAP_BE32(x) bswap_32(x)
# define SWAP_BE64(x) bswap_64(x)
# define SWAP_LE16(x) (x)
# define SWAP_LE32(x) (x)
# define SWAP_LE64(x) (x)
# define IF_BIG_ENDIAN(...)
# define IF_LITTLE_ENDIAN(...) __VA_ARGS__
#endif

#define bb_strtou strtoul

#define bb_error_msg_and_die printf
#define sha256_hash md5_hash
#define sha256_end  sha1_end

void* xmalloc(size_t size);
void* xzalloc(size_t size);
const char* strchrnul(const char* s, int ch);
char* xstrndup(const char *s, int n);
char* xstrdup(const char *s);
char* to64(char *s, unsigned v, int n);
int i64c(int i);

void md5_hash(md5_ctx_t *ctx, const void *buffer, size_t len);
void sha1_end(sha1_ctx_t *ctx, void *resbuf);
void sha256_begin(sha256_ctx_t *ctx);
void sha512_begin(sha512_ctx_t *ctx);
void sha512_hash(sha512_ctx_t *ctx, const void *buffer, size_t len);
void sha512_end(sha512_ctx_t *ctx, void *resbuf);
char *sha_crypt(/*const*/ char *key_data, /*const*/ char *salt_data);
char *pw_encrypt(const char *key, const char *salt);

#endif
