#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned char uc;
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

size_t strlen(const char *str);
char *strcat(char *dest, const char *src);
char *strncat(char *dest, const char *src, size_t n);
char *strchr(const char *str, int c);
char *strrchr(const char *str, int c);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);
size_t strspn(const char *s1, const char *s2);
size_t strcspn(const char *s1, const char *s2);
char *strpbrk(const char *s1, const char *s2);
char *strstr(const char *s1, const char *s2);
char *strtok(char *str, const char *delim);
char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, size_t n);
char *strdup(const char *src);
char *strndup(const char *src, size_t n);

void *memchr(const void *ptr, int ch, size_t n);
int memcmp(const void *lhs, const void *rhs, size_t n);
void *memset(void *dest, int ch, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);
void *memccpy(void *dest, const void *src, int c, size_t n);

int main() {
  // String manipulation tests
  char str1[50] = "Hello";
  char str2[] = " World!";
  char str3[50];
  char *result;

  // Testing strcat Expect: Hello World!
  strcat(str1, str2);
  printf("strcat: %s\n", str1); //

  // Testing strncat Expect: Hello World! How
  strncat(str1, " How are you?", 5);
  printf("strncat: %s\n", str1);

  // Testing strchr Expect: o World! How...
  result = strchr(str1, 'o');
  printf("strchr: %s\n", result);

  // Testing strrchr Expect: ow because of above
  result = strrchr(str1, 'o');
  printf("strrchr: %s\n", result);

  // Testing strcmp Expect: 0 (equal) and -1
  int cmpResult = strcmp("abc", "abc");
  printf("strcmp: %d\n", cmpResult);

  cmpResult = strcmp("abc", "abd");
  printf("strcmp: %d\n", cmpResult);

  // Testing strncmp Expect: 0
  cmpResult = strncmp("abc", "abc", 3);
  printf("strncmp: %d\n", cmpResult);

  // Testing strspn Expect: 3
  size_t span = strspn("abc123", "abc");
  printf("strspn: %zu\n", span);

  // Testing strcspn Expect: 3
  size_t cspan = strcspn("abc123", "123");
  printf("strcspn: %zu\n", cspan);

  // Testing strpbrk Expect: 123
  result = strpbrk("abc123", "123");
  printf("strpbrk: %s\n", result);

  // Testing strstr Expect: World!
  result = strstr("Hello World!", "World");
  printf("strstr: %s\n", result);

  // Testing strtok Expect: Hello World This Is C
  char str4[] = "Hello,World,This,Is,C";
  char *token = strtok(str4, ",");
  while(token) {
    printf("strtok: %s\n", token);
    token = strtok(NULL, ",");
  }

  // Testing strcpy
  char dest[50];
  strcpy(dest, "Copy this!");
  printf("strcpy: %s\n", dest);

  // Testing strncpy Expect: Hello
  char dest2[50];
  strncpy(dest2, "Hello, World!", 5);
  dest2[5] = '\0';
  printf("strncpy: %s\n", dest2);
  // Memory manipulation tests
  char buffer[50];

  // Testing memset
  memset(buffer, 'A', sizeof(buffer) - 1);
  buffer[49] = '\0';              // Null-terminate
  printf("memset: %s\n", buffer); // Expect: AAAAAAAAAA...

  // Testing memcpy
  char src[] = "Copy this!";
  memcpy(buffer, src, strlen(src) + 1); // +1 for null terminator
  printf("memcpy: %s\n", buffer);       // Expect: Copy this!

  // Testing memmove (overlapping regions)
  char overlap[] = "1234567890";
  memmove(overlap + 2, overlap, 8); // Move "12345678" to overlap + 2
  printf("memmove: %s\n", overlap); // Expect: 1231234568

  // Testing memccpy
  char destMem[50];
  char *memResult = memccpy(destMem, src, ' ', strlen(src));
  if(memResult) {
    *memResult = '\0'; // Null-terminate the string at the stop character
    printf("memccpy: %s\n", destMem); // Expect: Copy
  } else {
    printf("memccpy: character not found\n");
  }

  return 0;
}
// String Manipulation Functions

size_t strlen(const char *str) {
  const char *s = str;
  while(*s) { s++; }
  return s - str; // Return the length of the string
}

char *strcat(char *dest, const char *src) {
  char *d = dest;
  while(*d) d++;
  while((*d++ = *src++));
  return dest;
}

char *strncat(char *dest, const char *src, size_t n) {
  char *d = dest;
  while(*d) d++;
  while(n-- && (*d++ = *src++));
  *d = '\0';
  return dest;
}

char *strchr(const char *str, int c) {
  while(*str) {
    if(*str == (char)c) return (char *)str;
    str++;
  }
  return (*str == (char)c) ? (char *)str : NULL; // Check for '\0'
}

char *strrchr(const char *str, int c) {
  const char *last = NULL;
  while(*str) {
    if(*str == (char)c) last = str;
    str++;
  }
  return (char *)last; // Return last occurrence or NULL
}

int strcmp(const char *s1, const char *s2) {
  while(*s1 && (*s1 == *s2)) {
    s1++;
    s2++;
  }
  return *(uc *)s1 - *(uc *)s2; // Return difference
}

int strncmp(const char *s1, const char *s2, size_t n) {
  while(n && *s1 && (*s1 == *s2)) {
    s1++;
    s2++;
    n--;
  }
  return (n == 0) ? 0 : *(uc *)s1 - *(uc *)s2;
}

size_t strspn(const char *s1, const char *s2) {
  size_t count = 0;
  while(*s1 && strchr(s2, *s1)) {
    count++;
    s1++;
  }
  return count;
}

size_t strcspn(const char *s1, const char *s2) {
  size_t count = 0;
  while(*s1 && !strchr(s2, *s1)) {
    count++;
    s1++;
  }
  return count;
}

char *strpbrk(const char *s1, const char *s2) {
  while(*s1) {
    if(strchr(s2, *s1)) return (char *)s1; // Found character
    s1++;
  }
  return NULL; // No match found
}

char *strstr(const char *s1, const char *s2) {
  if(!*s2) return (char *)s1; // Empty substring
  while(*s1) {
    const char *p1 = s1, *p2 = s2;
    while(*p1 && (*p1 == *p2)) {
      p1++;
      p2++;
    }
    if(!*p2) return (char *)s1; // Found substring
    s1++;
  }
  return NULL; // Not found
}

char *strtok(char *str, const char *delim) {
  static char *nextToken = NULL;
  if(str) nextToken = str; // Initialize on first call
  if(!nextToken) return NULL;
  // Skip leading delimiters
  while(*nextToken && strchr(delim, *nextToken)) nextToken++;
  if(!*nextToken) return NULL; // No tokens left
  char *token = nextToken;     // Start of token
  // Find end of token
  while(*nextToken && !strchr(delim, *nextToken)) nextToken++;
  if(*nextToken) { *nextToken++ = '\0'; } // Null-terminate the token
  return token;
}

char *strcpy(char *dest, const char *src) {
  char *d = dest;
  while((*d++ = *src++)); // Copy until null terminator
  return dest;
}

char *strncpy(char *dest, const char *src, size_t n) {
  char *d = dest;
  while(n && (*d++ = *src++)) n--;
  while(n--) *d++ = '\0';
  return dest;
}

char *strdup(const char *src) {
  size_t len = 0;
  while(src[len]) len++; // Calculate length
  char *dup = (char *)malloc(len + 1);
  if(dup) strcpy(dup, src); // Allocate and copy
  return dup;
}

char *strndup(const char *src, size_t n) {
  size_t len = 0;
  while(len < n && src[len]) len++; // Calculate length
  char *dup = (char *)malloc(len + 1);
  if(dup) {
    strncpy(dup, src, len);
    dup[len] = '\0'; // Null-terminate
  }
  return dup;
}

// Memory Manipulation Functions

void *memchr(const void *ptr, int ch, size_t n) {
  const uc *p = ptr;
  while(n--) {
    if(*p == (uc)ch) return (void *)p;
    p++;
  }
  return NULL; // Not found
}

int memcmp(const void *lhs, const void *rhs, size_t n) {
  const uc *p1 = lhs;
  const uc *p2 = rhs;
  while(n--) {
    if(*p1 != *p2) return *p1 - *p2; // Return first difference
    p1++;
    p2++;
  }
  return 0; // Equal
}

void *memset(void *dest, int ch, size_t n) {
  uc *d = dest;
  while(n--) *d++ = (uc)ch; // Set byte
  return dest;
}

void *memcpy(void *dest, const void *src, size_t n) {
  uc *d = dest;
  const uc *s = src;
  while(n--) *d++ = *s++; // Copy byte by byte
  return dest;
}

void *memmove(void *dest, const void *src, size_t n) {
  uc *d = dest;
  const uc *s = src;
  if(d < s) {
    while(n--) *d++ = *s++; // Copy forwards
  } else {
    d += n;
    s += n;
    while(n--) *(--d) = *(--s); // Copy backwards
  }
  return dest;
}

void *memccpy(void *dest, const void *src, int c, size_t n) {
  uc *d = dest;
  const uc *s = src;
  for(size_t i = 0; i < n; i++) {
    *d++ = *s++;
    if(*(d - 1) == (uc)c) return d; // Return pointer after copied character
  }
  return NULL; // Not found
}