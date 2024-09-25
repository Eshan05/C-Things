#include <stdio.h>
/**
 * strcat: String concatenate (Append second)
 * strncat: Append part of string to another
 * strchr: Returns pointer to first occurrence of character
 * strrchar: Returns pointer to last occurrence of character
 * strcmp: Compares two strings lexicographically
 * strncmp: Compares a certain amount of characters of two strings
 * strspn: String span (Length of initial segment of first present in second)
 * strcspn: String complement span
 * strpbrk: String pointer break (Pointer to first occurrence of character)
 * strstr: First occurrence of substring within string (String search)
 * strtok: String tokenization (Spilt into tokens while maintaining state)
 * strtok_r: Safer alternative to strtok
 * strcpy: Copies one string to another
 * strncpy: Copies certain amount of characters from one string to another
 * strdup: Allocates a copy of a string
 * strndup: Allocates a copy of string of specified size
 *
 * memchr: Searches an array for first occurrence of a character
 * memcmp: Compares two buffers
 * memset: Fills a buffer with a character
 * memcpy: Copies one buffer to another
 * memmove: Moves one buffer to another
 * memccpy: Copies one buffer to another, stopping after the specified delimiter
 */

char *strcat(char *dest, const char *src) {}
char *strncat(char *dest, const char *src, size_t n) {}
char *strchr(const char *str, int c) {}
char *strrchr(const char *str, int c) {}
int strcmp(const char *s1, const char *s2) {}
int strncmp(const char *s1, const char *s2, size_t n) {}
size_t strspn(const char *s1, const char *s2) {}
size_t strcspn(const char *s1, const char *s2) {}
char *strpbrk(const char *s1, const char *s2) {}
char *strstr(const char *s1, const char *s2) {}
char *strtok(char *str, const char *delim) {}
char *strcpy(char *dest, const char *src) {}
char *strncpy(char *dest, const char *src, size_t n) {}
char *strdup(const char *src) {}
char *strndup(const char *src, size_t n) {}

void *memchr(const void *ptr, int ch, size_t n) {}
int memcmp(const void *lhs, const void *rhs, size_t n) {}
void *memset(void *dest, int ch, size_t n) {}
void *memcpy(void *dest, const void *src, size_t n) {}
void *memmove(void *dest, const void *src, size_t n) {}
void *memccpy(void *dest, const void *src, int c, size_t n) {}

int main() { return 0; }
