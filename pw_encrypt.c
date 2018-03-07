#include "pw_encrypt.h"

static struct const_des_ctx *des_cctx;
static struct des_ctx *des_ctx;

/* my_crypt returns malloc'ed data */
char *pw_encrypt(const char *key, const char *salt)
{
	/* MD5 or SHA? */
	if (salt[0] == '$' && salt[1] && salt[2] == '$') {
		if (salt[1] == '1')
			return md5_crypt(xzalloc(MD5_OUT_BUFSIZE), (unsigned char*)key, (unsigned char*)salt);
#if ENABLE_USE_BB_CRYPT_SHA
		if (salt[1] == '5' || salt[1] == '6')
			return sha_crypt((char*)key, (char*)salt);
#endif
	}

	if (!des_cctx)
		des_cctx = const_des_init();
	des_ctx = des_init(des_ctx, des_cctx);
	return des_crypt(des_ctx, xzalloc(DES_OUT_BUFSIZE), (unsigned char*)key, (unsigned char*)salt);
}