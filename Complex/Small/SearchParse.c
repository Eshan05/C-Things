/**
 * @file   SearchParse.c
 * @brief  Parsing searches similar to GitHub
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX_TERMS 10

typedef struct {
  char *languages[MAX_TERMS]; // Array to hold languages
  char *authors[MAX_TERMS];   // Array to hold authors
  char *repos[MAX_TERMS];     // Array to hold repos
  char *orgs[MAX_TERMS];      // Array to hold orgs
  char *paths[MAX_TERMS];     // Array to hold paths
  char *contents[MAX_TERMS];  // Array to hold contents
  char *keywords[MAX_TERMS];  // Array to hold keywords
  int stars;                  // Stars count
  char *stars_op;             // Operator for stars
  int not_op;                 // Flag for NOT operation
  char *logical_op;           // To track logical operators (AND, OR)
  int language_count;
  int author_count;
  int repo_count;
  int org_count;
  int path_count;
  int content_count;
  int keyword_count;
} SearchParams;

void cls() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void red() { printf("\033[1;31m"); }
void green() { printf("\033[1;32m"); }
void yellow() { printf("\033[1;33m"); }
void blue() { printf("\033[1;34m"); }
void purple() { printf("\033[1;35m"); }
void cyan() { printf("\033[1;36m"); }
void reset() { printf("\033[0m"); }

void header();
char *strndup(const char *src, size_t n);
void print_params(const SearchParams *params);
void parse_search(char *input, SearchParams *params);

int main() {
  header();
  char search[100];
  while (1) {
    printf("\n\033[1;33mSP ->\033[0m ");
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = 0;
    if (strcmp(search, "q") == 0 || strcmp(search, "exit") == 0) {
      printf("\033[1;33mExiting...\033[0m");
      sleep(1);
      cls();
      break;
    } else if (strcmp(search, "help") == 0) {
      printf("Available commands:\n");
      printf(" - language:<language>\n");
      printf(" - author:<username>\n");
      printf(" - repo:<reponame>\n");
      printf(" - org:<orgname>\n");
      printf(" - path:<filepath>\n");
      printf(" - content:<content>\n");
      printf(" - stars:<(<|>)number>\n");
      printf(" - label:\"<label>\"\n");
      printf(" - assignee:<username>\n");
      printf(" - NOT <keyword>\n");
      printf(" - AND <keyword> <keyword>\n");
      printf(" - OR <keyword> <keyword>\n");
    } else {
      SearchParams params;
      parse_search(search, &params);
      print_params(&params);

      // Free allocated memory
      for (int i = 0; i < params.language_count; i++) free(params.languages[i]);
      for (int i = 0; i < params.author_count; i++) free(params.authors[i]);
      for (int i = 0; i < params.repo_count; i++) free(params.repos[i]);
      for (int i = 0; i < params.org_count; i++) free(params.orgs[i]);
      for (int i = 0; i < params.path_count; i++) free(params.paths[i]);
      for (int i = 0; i < params.content_count; i++) free(params.contents[i]);
      for (int i = 0; i < params.keyword_count; i++) free(params.keywords[i]);
      free(params.stars_op);
      free(params.logical_op);
    }
  }
  return 0;
}

void header() {
  cls();
  printf("\n");
  cyan();
  printf("  _________                           .__     \n"
         " /   _____/ ____ _____ _______   ____ |  |__  \n"
         " \\_____  \\_/ __ \\\\__  \\\\_  __ \\_/ ___\\|  |  \\ \n"
         " /        \\  ___/ / __ \\|  | \\/\\  \\___|   Y  \\ \n"
         "/_______  /\\___  >____  /__|    \\___  >___|  / \n"
         "        \\/     \\/     \\/            \\/     \\/  \n");
  reset();
  printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
  printf("\tWelcome to Search Parser!\n");
  printf("      Use \033[1;36mhelp\033[0m for more information.");
  printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
}

void parse_search(char *input, SearchParams *params) {
  memset(params, 0, sizeof(SearchParams));

  char *token = strtok(input, " ");
  while (token != NULL) {
    if (strncmp(token, "language:", 9) == 0) {
      if (params->language_count < MAX_TERMS) {
        params->languages[params->language_count++] = strdup(token + 9);
      }
    } else if (strncmp(token, "author:", 7) == 0) {
      if (params->author_count < MAX_TERMS) {
        params->authors[params->author_count++] = strdup(token + 7);
      }
    } else if (strncmp(token, "repo:", 5) == 0) {
      if (params->repo_count < MAX_TERMS) {
        params->repos[params->repo_count++] = strdup(token + 5);
      }
    } else if (strncmp(token, "org:", 4) == 0) {
      if (params->org_count < MAX_TERMS) {
        params->orgs[params->org_count++] = strdup(token + 4);
      }
    } else if (strncmp(token, "path:", 5) == 0) {
      if (params->path_count < MAX_TERMS) {
        params->paths[params->path_count++] = strdup(token + 5);
      }
    } else if (strncmp(token, "content:", 8) == 0) {
      if (params->content_count < MAX_TERMS) {
        params->contents[params->content_count++] = strdup(token + 8);
      }
    } else if (strncmp(token, "NOT", 3) == 0) {
      params->not_op = 1;
      token += 4; // Move past "NOT"
      if (params->keyword_count < MAX_TERMS) {
        params->keywords[params->keyword_count++] = strdup(token);
      }
    } else if (strcmp(token, "AND") == 0) {
      params->logical_op = strdup("AND");
    } else if (strcmp(token, "OR") == 0) {
      params->logical_op = strdup("OR");
    } else {
      if (params->keyword_count < MAX_TERMS) {
        params->keywords[params->keyword_count++] =
            strdup(token); // Store generic keywords
      }
    }
    token = strtok(NULL, " ");
  }
}

char *strndup(const char *src, size_t n) {
  size_t len = 0;
  while (len < n && src[len]) len++;
  char *dup = (char *)malloc(len + 1);
  if (dup) {
    strncpy(dup, src, len);
    dup[len] = '\0';
  }
  return dup;
}

void print_params(const SearchParams *params) {
  printf("--/ Parsed Search Parameters: \\--\n");

  if (params->language_count > 0) {
    printf("- Languages: ");
    for (int i = 0; i < params->language_count; i++) {
      printf("%s", params->languages[i]);
      if (i < params->language_count - 1) printf(", ");
    }
    printf("\n");
  }

  if (params->author_count > 0) {
    printf("- Authors: ");
    for (int i = 0; i < params->author_count; i++) {
      printf("%s", params->authors[i]);
      if (i < params->author_count - 1) printf(", ");
    }
    printf("\n");
  }

  if (params->repo_count > 0) {
    printf("- Repositories: ");
    for (int i = 0; i < params->repo_count; i++) {
      printf("%s", params->repos[i]);
      if (i < params->repo_count - 1) printf(", ");
    }
    printf("\n");
  }

  if (params->org_count > 0) {
    printf("- Organizations: ");
    for (int i = 0; i < params->org_count; i++) {
      printf("%s", params->orgs[i]);
      if (i < params->org_count - 1) printf(", ");
    }
    printf("\n");
  }

  if (params->path_count > 0) {
    printf("- Paths: ");
    for (int i = 0; i < params->path_count; i++) {
      printf("%s", params->paths[i]);
      if (i < params->path_count - 1) printf(", ");
    }
    printf("\n");
  }

  if (params->content_count > 0) {
    printf("- Contents: ");
    for (int i = 0; i < params->content_count; i++) {
      printf("%s", params->contents[i]);
      if (i < params->content_count - 1) printf(", ");
    }
    printf("\n");
  }

  if (params->stars_op) {
    printf("* Stars: %s%d\n", params->stars_op, params->stars);
  }

  if (params->keyword_count > 0) {
    printf("- Keywords: ");
    for (int i = 0; i < params->keyword_count; i++) {
      printf("%s", params->keywords[i]);
      if (i < params->keyword_count - 1) printf(", ");
    }
    printf("\n");
  }

  printf("- NOT Found: %s\n", params->not_op ? "Yes" : "No");
  if (params->logical_op) {
    printf("- Logical Operator: %s\n", params->logical_op);
  }
}
