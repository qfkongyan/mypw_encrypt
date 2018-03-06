#include "pw_encrypt.h"

void* xzalloc(size_t size)
{
	void *ptr = xmalloc(size);
	memset(ptr, 0, size);
	return ptr;
}

const char* strchrnul(const char* s, int ch) {
  while (*s && *s != ch) {
    ++s;
  }
  return s;
}

char* xstrndup(const char *s, int n)
{
	int m;
	char *t;

	if (ENABLE_DEBUG && s == NULL)
		bb_error_msg_and_die("%s:%s:%d",__FILE__,__FUNCTION__,__LINE__);

	/* We can just xmalloc(n+1) and strncpy into it, */
	/* but think about xstrndup("abc", 10000) wastage! */
	m = n;
	t = (char*) s;
	while (m) {
		if (!*t) break;
		m--;
		t++;
	}
	n -= m;
	t = xmalloc(n + 1);
	t[n] = '\0';

	return memcpy(t, s, n);
}

// Die if we can't copy a string to freshly allocated memory.
char* xstrdup(const char *s)
{
	char *t;

	if (s == NULL)
		return NULL;

	t = strdup(s);

	if (t == NULL)
		bb_error_msg_and_die("%s:%s:%d",__FILE__,__FUNCTION__,__LINE__);

	return t;
}

void* xmalloc(size_t size)
{
	void *ptr = malloc(size);
	if (ptr == NULL && size != 0)
		bb_error_msg_and_die("%s:%s:%d",__FILE__,__FUNCTION__,__LINE__);
	return ptr;
}

char* to64(char *s, unsigned v, int n)
{
	while (--n >= 0) {
		/* *s++ = ascii64[v & 0x3f]; */
		*s++ = i64c(v);
		v >>= 6;
	}
	return s;
}

int i64c(int i)
{
	i &= 0x3f;
	if (i == 0)
		return '.';
	if (i == 1)
		return '/';
	if (i < 12)
		return ('0' - 2 + i);
	if (i < 38)
		return ('A' - 12 + i);
	return ('a' - 38 + i);
}
