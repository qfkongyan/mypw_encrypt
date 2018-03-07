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

struct des_ctx {
	const struct const_des_ctx *const_ctx;
	uint32_t saltbits; /* referenced 5 times */
#if USE_REPETITIVE_SPEEDUP
	uint32_t old_salt; /* 3 times */
	uint32_t old_rawkey0, old_rawkey1; /* 3 times each */
#endif
	uint8_t	un_pbox[32]; /* 2 times */
	uint8_t	inv_comp_perm[56]; /* 3 times */
	uint8_t	inv_key_perm[64]; /* 3 times */
	uint32_t en_keysl[16], en_keysr[16]; /* 2 times each */
#if USE_de_keys
	uint32_t de_keysl[16], de_keysr[16]; /* 2 times each */
#endif
#if USE_ip_mask
	uint32_t ip_maskl[8][256], ip_maskr[8][256]; /* 9 times each */
#endif
	uint32_t fp_maskl[8][256], fp_maskr[8][256]; /* 9 times each */
	uint32_t key_perm_maskl[8][128], key_perm_maskr[8][128]; /* 9 times */
	uint32_t comp_maskl[8][128], comp_maskr[8][128]; /* 9 times each */
	uint32_t psbox[4][256]; /* 5 times */
};

#define  ENABLE_DEBUG 1
#define ALWAYS_INLINE inline
#define  ENABLE_USE_BB_CRYPT_SHA 1
#define MD5_OUT_BUFSIZE 36
#define DES_OUT_BUFSIZE 21

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

void  md5_begin(md5_ctx_t *ctx);
void  md5_end(md5_ctx_t *ctx, void *resbuf);
char *md5_crypt(char result[MD5_OUT_BUFSIZE], const unsigned char *pw, const unsigned char *salt);
void md5_hash(md5_ctx_t *ctx, const void *buffer, size_t len);
void sha1_end(sha1_ctx_t *ctx, void *resbuf);
void sha256_begin(sha256_ctx_t *ctx);
void sha512_begin(sha512_ctx_t *ctx);
void sha512_hash(sha512_ctx_t *ctx, const void *buffer, size_t len);
void sha512_end(sha512_ctx_t *ctx, void *resbuf);
char *sha_crypt(/*const*/ char *key_data, /*const*/ char *salt_data);
struct const_des_ctx *const_des_init(void);
char *des_crypt(struct des_ctx *ctx, char output[DES_OUT_BUFSIZE], const unsigned char *key, const unsigned char *setting);
struct des_ctx *des_init(struct des_ctx *ctx, const struct const_des_ctx *cctx);
char *pw_encrypt(const char *key, const char *salt);

#endif
