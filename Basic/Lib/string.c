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

void trim_newline(char *str);
void stringManipulationMenu();
void memoryManipulationMenu();

int main() {
  while(1) {
    printf("\n--- Main Menu ---\n");
    printf("1. String Manipulation\n");
    printf("2. Memory Manipulation\n");
    printf("0. Exit\n");
    printf("Choose an option: ");

    int choice;
    scanf("%d", &choice);
    getchar(); // To consume the newline character

    switch(choice) {
      case 1: stringManipulationMenu(); break;
      case 2: memoryManipulationMenu(); break;
      case 0: return 0;
      default: printf("Invalid option! Please try again.\n");
    }
  }
}
// String Manipulation Functions

size_t strlen(const char *str) {
  const char *s = str;
  while(*s) { s++; }
  return s - str;
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
  return (*str == (char)c) ? (char *)str : NULL;
}

char *strrchr(const char *str, int c) {
  const char *last = NULL;
  while(*str) {
    if(*str == (char)c) last = str;
    str++;
  }
  return (char *)last;
}

int strcmp(const char *s1, const char *s2) {
  while(*s1 && (*s1 == *s2)) {
    s1++;
    s2++;
  }
  return *(uc *)s1 - *(uc *)s2;
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
    if(strchr(s2, *s1)) return (char *)s1;
    s1++;
  }
  return NULL;
}

char *strstr(const char *s1, const char *s2) {
  if(!*s2) return (char *)s1;
  while(*s1) {
    const char *p1 = s1, *p2 = s2;
    while(*p1 && (*p1 == *p2)) {
      p1++;
      p2++;
    }
    if(!*p2) return (char *)s1;
    s1++;
  }
  return NULL;
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
  while((*d++ = *src++));
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
  while(src[len]) len++;
  char *dup = (char *)malloc(len + 1);
  if(dup) strcpy(dup, src);
  return dup;
}

char *strndup(const char *src, size_t n) {
  size_t len = 0;
  while(len < n && src[len]) len++;
  char *dup = (char *)malloc(len + 1);
  if(dup) {
    strncpy(dup, src, len);
    dup[len] = '\0';
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
  return NULL;
}

int memcmp(const void *lhs, const void *rhs, size_t n) {
  const uc *p1 = lhs;
  const uc *p2 = rhs;
  while(n--) {
    if(*p1 != *p2) return *p1 - *p2;
    p1++;
    p2++;
  }
  return 0;
}

void *memset(void *dest, int ch, size_t n) {
  uc *d = dest;
  while(n--) *d++ = (uc)ch;
  return dest;
}

void *memcpy(void *dest, const void *src, size_t n) {
  uc *d = dest;
  const uc *s = src;
  while(n--) *d++ = *s++;
  return dest;
}

void *memmove(void *dest, const void *src, size_t n) {
  uc *d = dest;
  const uc *s = src;
  if(d < s) {
    while(n--) *d++ = *s++;
  } else {
    d += n;
    s += n;
    while(n--) *(--d) = *(--s);
  }
  return dest;
}

void *memccpy(void *dest, const void *src, int c, size_t n) {
  uc *d = dest;
  const uc *s = src;
  for(size_t i = 0; i < n; i++) {
    *d++ = *s++;
    if(*(d - 1) == (uc)c) return d;
  }
  return NULL;
}

void trim_newline(char *str) {
  size_t len = strlen(str);
  if(len > 0 && str[len - 1] == '\n') str[len - 1] = '\0';
}

void stringManipulationMenu() {
  char str1[100], str2[100];
  char ch;

  while(1) {
    printf("\n--- String Manipulation Menu ---\n");
    printf("1. Length (strlen)\n");
    printf("2. Concatenate (strcat)\n");
    printf("3. Concatenate N characters (strncat)\n");
    printf("4. Find character (strchr)\n");
    printf("5. Find last character (strrchr)\n");
    printf("6. Compare strings (strcmp)\n");
    printf("7. Compare N characters (strncmp)\n");
    printf("8. Span of characters (strspn)\n");
    printf("9. Span until characters (strcspn)\n");
    printf("10. Find first occurrence of any character (strpbrk)\n");
    printf("11. Find substring (strstr)\n");
    printf("12. Tokenize string (strtok)\n");
    printf("13. Copy string (strcpy)\n");
    printf("14. Copy N characters (strncpy)\n");
    printf("15. Duplicate string (strdup)\n");
    printf("16. Duplicate N characters (strndup)\n");
    printf("0. Return to main menu\n");
    printf("Choose an option: ");

    int choice;
    scanf("%d", &choice);
    getchar(); // To consume the newline character

    switch(choice) {
      case 1: // strlen
        printf("Enter string: ");
        fgets(str1, sizeof(str1), stdin);
        trim_newline(str1);
        printf("Length: %zu\n", strlen(str1));
        break;
      case 2: // strcat
        printf("Enter first string: ");
        fgets(str1, sizeof(str1), stdin);
        trim_newline(str1);
        printf("Enter second string: ");
        fgets(str2, sizeof(str2), stdin);
        trim_newline(str2);
        printf("Result: %s\n", strcat(str1, str2));
        break;
      case 3: // strncat
        printf("Enter base string: ");
        fgets(str1, sizeof(str1), stdin);
        trim_newline(str1);
        printf("Enter string to concatenate: ");
        fgets(str2, sizeof(str2), stdin);
        trim_newline(str2);
        printf("Result: %s\n",
               strncat(str1, str2, 5)); // Concatenate first 5 characters
        break;
      case 4: // strchr
        printf("Enter string: ");
        fgets(str1, sizeof(str1), stdin);
        trim_newline(str1);
        printf("Enter character to find: ");
        scanf(" %c", &ch);
        char *foundChar = strchr(str1, ch);
        if(foundChar) {
          printf("Found: %s\n", foundChar);
        } else {
          printf("Character not found.\n");
        }
        break;
      case 5: // strrchr
        printf("Enter string: ");
        fgets(str1, sizeof(str1), stdin);
        trim_newline(str1);
        printf("Enter character to find: ");
        scanf(" %c", &ch);
        char *lastChar = strrchr(str1, ch);
        if(lastChar) {
          printf("Last found: %s\n", lastChar);
        } else {
          printf("Character not found.\n");
        }
        break;
      case 6: // strcmp
        printf("Enter first string: ");
        fgets(str1, sizeof(str1), stdin);
        trim_newline(str1);
        printf("Enter second string: ");
        fgets(str2, sizeof(str2), stdin);
        trim_newline(str2);
        printf("Comparison result: %d\n", strcmp(str1, str2));
        break;
      case 7: // strncmp
        printf("Enter first string: ");
        fgets(str1, sizeof(str1), stdin);
        trim_newline(str1);
        printf("Enter second string: ");
        fgets(str2, sizeof(str2), stdin);
        trim_newline(str2);
        printf("Enter number of characters to compare: ");
        int n;
        scanf("%d", &n);
        printf("Comparison result: %d\n", strncmp(str1, str2, n));
        break;
      case 8: // strspn
        printf("Enter string: ");
        fgets(str1, sizeof(str1), stdin);
        trim_newline(str1);
        printf("Enter characters to check: ");
        fgets(str2, sizeof(str2), stdin);
        trim_newline(str2);
        printf("Span length: %zu\n", strspn(str1, str2));
        break;
      case 9: // strcspn
        printf("Enter string: ");
        fgets(str1, sizeof(str1), stdin);
        trim_newline(str1);
        printf("Enter characters to check: ");
        fgets(str2, sizeof(str2), stdin);
        trim_newline(str2);
        printf("Span length: %zu\n", strcspn(str1, str2));
        break;
      case 10: // strpbrk
        printf("Enter string: ");
        fgets(str1, sizeof(str1), stdin);
        trim_newline(str1);
        printf("Enter characters to find: ");
        fgets(str2, sizeof(str2), stdin);
        trim_newline(str2);
        char *firstOccurrence = strpbrk(str1, str2);
        if(firstOccurrence) {
          printf("First occurrence: %s\n", firstOccurrence);
        } else {
          printf("No characters found.\n");
        }
        break;
      case 11: // strstr
        printf("Enter haystack: ");
        fgets(str1, sizeof(str1), stdin);
        trim_newline(str1);
        printf("Enter needle: ");
        fgets(str2, sizeof(str2), stdin);
        trim_newline(str2);
        char *substring = strstr(str1, str2);
        if(substring) {
          printf("Substring found: %s\n", substring);
        } else {
          printf("Substring not found.\n");
        }
        break;
      case 12: // strtok
        printf("Enter string to tokenize: ");
        fgets(str1, sizeof(str1), stdin);
        trim_newline(str1);
        printf("Enter delimiters: ");
        fgets(str2, sizeof(str2), stdin);
        trim_newline(str2);
        char *token = strtok(str1, str2);
        printf("Tokens:\n");
        while(token) {
          printf("%s\n", token);
          token = strtok(NULL, str2);
        }
        break;
      case 13: // strcpy
        printf("Enter source string: ");
        fgets(str1, sizeof(str1), stdin);
        trim_newline(str1);
        char dest[100];
        printf("Copied: %s\n", strcpy(dest, str1));
        break;
      case 14: // strncpy
        printf("Enter source string: ");
        fgets(str1, sizeof(str1), stdin);
        trim_newline(str1);
        printf("Enter number of characters to copy: ");
        scanf("%d", &n);
        char dest2[100];
        printf("Copied: %s\n", strncpy(dest2, str1, n));
        dest2[n] = '\0'; // Ensure null-termination
        break;
      case 15: // strdup
        printf("Enter source string: ");
        fgets(str1, sizeof(str1), stdin);
        trim_newline(str1);
        char *duplicatedStr = strdup(str1);
        printf("Duplicated: %s\n", duplicatedStr);
        free(duplicatedStr); // Free allocated memory
        break;
      case 16: // strndup
        printf("Enter source string: ");
        fgets(str1, sizeof(str1), stdin);
        trim_newline(str1);
        printf("Enter number of characters to duplicate: ");
        scanf("%d", &n);
        char *nduplicatedStr = strndup(str1, n);
        printf("Duplicated: %s\n", nduplicatedStr);
        free(nduplicatedStr); // Free allocated memory
        break;
      case 0: return;
      default: printf("Invalid option! Please try again.\n");
    }
  }
}

void memoryManipulationMenu() {
  char buffer1[100], buffer2[100];
  int ch;
  size_t n;

  while(1) {
    printf("\n--- Memory Manipulation Menu ---\n");
    printf("1. Find character in memory (memchr)\n");
    printf("2. Compare memory blocks (memcmp)\n");
    printf("3. Set memory (memset)\n");
    printf("4. Copy memory (memcpy)\n");
    printf("5. Move memory (memmove)\n");
    printf("6. Copy until a character (memccpy)\n");
    printf("0. Return to main menu\n");
    printf("Choose an option: ");

    int choice;
    scanf("%d", &choice);
    getchar(); // To consume the newline character

    switch(choice) {
      case 1: // memchr
        printf("Enter string: ");
        fgets(buffer1, sizeof(buffer1), stdin);
        trim_newline(buffer1);
        printf("Enter character to find: ");
        scanf(" %c", &ch);
        char *foundChar = memchr(buffer1, ch, strlen(buffer1));
        if(foundChar) {
          printf("Found character at: %s\n", foundChar);
        } else {
          printf("Character not found.\n");
        }
        break;
      case 2: // memcmp
        printf("Enter first memory block (string): ");
        fgets(buffer1, sizeof(buffer1), stdin);
        trim_newline(buffer1);
        printf("Enter second memory block (string): ");
        fgets(buffer2, sizeof(buffer2), stdin);
        trim_newline(buffer2);
        printf("Comparing memory blocks...\n");
        int cmpResult =
            memcmp(buffer1, buffer2,
                   sizeof(buffer1) < sizeof(buffer2) ? sizeof(buffer1)
                                                     : sizeof(buffer2));
        printf("Comparison result: %d\n", cmpResult);
        break;
      case 3: // memset
        printf("Enter character to set memory with (ASCII): ");
        scanf(" %c", &ch);
        printf("Enter number of bytes to set: ");
        scanf("%zu", &n);
        void *memSetResult = memset(buffer1, ch, n);
        printf("Memory set: %s\n", (char *)memSetResult);
        break;
      case 4: // memcpy
        printf("Enter source string: ");
        fgets(buffer2, sizeof(buffer2), stdin);
        trim_newline(buffer2);
        printf("Enter number of bytes to copy: ");
        scanf("%zu", &n);
        void *memCopyResult = memcpy(buffer1, buffer2, n);
        printf("Copied memory: %s\n", (char *)memCopyResult);
        break;
      case 5: // memmove
        printf("Enter string to move: ");
        fgets(buffer2, sizeof(buffer2), stdin);
        trim_newline(buffer2);
        printf("Enter number of bytes to move: ");
        scanf("%zu", &n);
        void *memMoveResult =
            memmove(buffer1 + 5, buffer2, n); // Example of overlapping regions
        printf("Moved memory: %s\n", (char *)buffer1);
        break;
      case 6: // memccpy
        printf("Enter source string: ");
        fgets(buffer2, sizeof(buffer2), stdin);
        trim_newline(buffer2);
        printf("Enter character to stop at: ");
        scanf(" %c", &ch);
        printf("Enter number of bytes to copy: ");
        scanf("%zu", &n);
        char *memccpyResult = memccpy(buffer1, buffer2, ch, n);
        if(memccpyResult) {
          printf("Copied memory up to character: %s\n", (char *)buffer1);
        } else {
          printf("Character not found in the source string.\n");
        }
        break;
      case 0: return;
      default: printf("Invalid option! Please try again.\n");
    }
  }
}