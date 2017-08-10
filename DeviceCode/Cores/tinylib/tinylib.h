////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2012 Kentaro Sekimoto  All rights reserved.
////////////////////////////////////////////////////////////////////////////

#ifndef TINYLIB_H_
#define TINYLIB_H_

#ifndef NULL
#define NULL ((void *)0)
#endif

typedef __SIZE_TYPE__ size_t;

void *memset(void *dst, int c, size_t len);
void *memcpy(void *dst, const void *src, size_t len);
void *memmove(void *dst, void const *src, size_t len);
int memcmp(const void *p1, const void *p2, size_t len);
int strlen(const char *s);
char *strchr(char *s, int c);
char *strcpy(char *dst, const char *src);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *p1, const char *p2, int len);
char *strncpy(char *dst, const char *src, size_t len);
void *bsearch(void *key, void *base0, size_t nmemb, size_t size, int (*compar)());
int atoi(const char *s);

#endif /* TINYLIB_H_ */
