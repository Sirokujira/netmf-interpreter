////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2012 Kentaro Sekimoto  All rights reserved.
////////////////////////////////////////////////////////////////////////////

#include "tinylib.h"

//#undef PLATFORM_H8
#if defined(PLATFORM_H8)
// During transferring, interrupt is disabled.
// Need to carefully decide the block size.
#define TRANS_BLOCK_SIZE    0x400
void *memcpy(void *dst, const void *src, size_t size)
{
    size_t trans = size;
    void *save = dst;

    while (size > 0) {
        if (size >= TRANS_BLOCK_SIZE)
            trans = TRANS_BLOCK_SIZE;
        else
            trans = size;
        asm("mov.l %0, er5"::"r"(src):);
        asm("mov.l %0, er4"::"r"(trans):);
        asm("push.l er6":::);
        asm("mov.l %0, er6"::"r"(dst):);
        asm("eepmov.w");
        asm("pop.l er6":::);

        dst += trans;
        src += trans;
        size -= trans;
    }
    return (void *)save;
}

void *memset(void *dst, int c, size_t size)
{
    if (size) {
        *(char *)dst = (char)c;
        memcpy(dst+1, dst, size-1);
    }
    return (void *)dst;
}
#else
void *memset(void *dst, int c, size_t len)
{
	char *p;
	for (p = (char *)dst; len > 0; len--)
		*(p++) = (char)c;
	return (void *)dst;
}

void *memcpy(void *dst, const void *src, size_t len)
{
	char *d = (char *)dst;
	const char *s = (const char *)src;
	for (; len > 0; len--)
		*(d++) = *(s++);
	return (void *)dst;
}
#endif

void *memmove(void *dst, void const *src, size_t len)
{
	char *d = (char *)dst;
	char const *s = (char const *) src;
	if (s < d)
		for (s += len, d += len; len; --len)
			*--d = *--s;
	else if (s != d) {
		for (; len; --len)
			*d++ = *s++;
	}
	return (void *)d;
}

int memcmp(const void *p1, const void *p2, size_t len)
{
	unsigned char *a, *b;
	size_t i;

	a = (unsigned char *)p1;
	b = (unsigned char *)p2;
	for(i = 0; i < len; i++) {
		if (*a != *b) {
			return (*a < *b) ? -1 : 1;
		}
		a++;
		b++;
	}
	return (int)0;
}

int strlen(const char *s)
{
	int len;
	for (len = 0; *s; s++, len++)
		;
	return len;
}

char *strchr(char *s, int c)
{
	char c1;
	if(c == 0) {
		while(*s++)
			;
		return s-1;
	}
	while(c1 = *s++)
		if(c1 == c)
			return s-1;
	return 0;
}

char *strcpy(char *dst, const char *src)
{
	char *d = dst;
	for (;; dst++, src++) {
		*dst = *src;
		if (!*src) break;
	}
	return d;
}

int strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2++)
		if (*s1++ == 0)
			return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)--s2);
}

int strncmp(const char *p1, const char *p2, int len)
{
	for (; len > 0; len--) {
		if (*(p1++) != *(p2++)) return 1;
	}
	return 0;
}

char *strncpy(char *dst, const char *src, size_t len)
{
	char *q = (char *)dst;
	const char *p = (const char *)src;
	char ch;
	while (len--) {
		*q++ = ch = *p++;
		if ( !ch )
			break;
	}
	return dst;
}

#if defined(INC_BSEARCH)
void *bsearch(void *key, void *base0, size_t nmemb, size_t size, int (*compar)())
{
	register char *base = base0;
	register int lim, cmp;
	register void *p;

	for (lim = nmemb; lim != 0; lim >>= 1) {
		p = base + (lim >> 1) * size;
		cmp = (*compar)(key, p);
		if (cmp == 0)
			return (p);
		if (cmp > 0) {  /* key > p: move right */
			base = (char *)p + size;
		lim--;
		} /* else move left */
	}
	return (NULL);
}
#endif

int atoi(const char *s)
{
	int result=0, sign=1;
	if (*s == -1) {
		sign = -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
		result = result*10 + (*(s++)-'0');
	return result*sign;
}
