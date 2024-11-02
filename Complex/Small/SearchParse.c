/**
 * @file   SearchParse.c
 * @brief  Parsing searches similar to github
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX_KEYWORDS 10

typedef struct {
  char *language;
  char *author;
  char *repo;
  char *org;
  char *path;
  char *content;
  char *keyword;
  int stars;        // Stars count
  char *stars_op;   // Operator for stars
  int not_op;       // Flag for NOT operation
  char *logical_op; // To track logical operators (AND, OR)
} SearchParams;

void cls() {
  // clang-format off
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
  // clang-format on
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
void parse_search();

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
      printf(" - user:<username>\n");
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

      free(params.language);
      free(params.author);
      free(params.repo);
      free(params.org);
      free(params.path);
      free(params.content);
      free(params.keyword);
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
  // Initialize params
  memset(params, 0, sizeof(SearchParams));

  char *token = strtok(input, " ");
  while (token != NULL) {
    // Handle special commands and their values
    if (strncmp(token, "language:", 9) == 0) {
      params->language = strdup(token + 9);
    } else if (strncmp(token, "author:", 7) == 0) {
      params->author = strdup(token + 7);
    } else if (strncmp(token, "repo:", 5) == 0) {
      params->repo = strdup(token + 5);
    } else if (strncmp(token, "org:", 4) == 0) {
      params->org = strdup(token + 4);
    } else if (strncmp(token, "path:", 5) == 0) {
      params->path = strdup(token + 5);
    } else if (strncmp(token, "content:", 8) == 0) {
      params->content = strdup(token + 8);
    } else if (strncmp(token, "stars:", 6) == 0) {
      char *stars_value = token + 6;
      if (stars_value[0] == '>' || stars_value[0] == '<') {
        params->stars_op = strndup(stars_value, 1);
        params->stars = atoi(stars_value + 1);
      } else {
        params->stars = atoi(stars_value);
        params->stars_op = strdup("="); // Default to equality
      }
    } else if (strncmp(token, "NOT", 3) == 0) {
      params->not_op = 1;
      token += 4; // Move past "NOT"
      params->keyword = strdup(token);
    } else if (strcmp(token, "AND") == 0) {
      params->logical_op = strdup("AND");
    } else if (strcmp(token, "OR") == 0) {
      params->logical_op = strdup("OR");
    } else if (strstr(token, ":")) {
      // Handle cases like label:"Bug fix" OR assignee:octocat
      char *colon = strchr(token, ':');
      *colon = '\0'; // Split the command
      char *command = token;
      char *value = colon + 1;

      // Trim quotes from value if present
      if (value[0] == '"' && value[strlen(value) - 1] == '"') {
        value[strlen(value) - 1] = '\0';
        value++;
      }

      // Assign based on command
      if (strcmp(command, "label") == 0) {
        params->keyword = strdup(value); // Use keyword for labels
      } else if (strcmp(command, "assignee") == 0) {
        params->keyword = strdup(value); // Use keyword for assignee
      }
    } else {
      params->keyword = strdup(token); // Generic keyword
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
  if (params->language) printf("- Language: %s\n", params->language);
  if (params->author) printf("- User: %s\n", params->author);
  if (params->repo) printf("- Repo: %s\n", params->repo);
  if (params->org) printf("- Org: %s\n", params->org);
  if (params->path) printf("- Path: %s\n", params->path);
  if (params->content) printf("- Content: %s\n", params->content);
  if (params->stars_op)
    printf("* Stars: %s%d\n", params->stars_op, params->stars);
  if (params->keyword) printf("- Keyword: %s\n", params->keyword);
  printf("- NOT Found: %s\n", params->not_op ? "Yes" : "No");
  if (params->logical_op)
    printf("- Logical Operator: %s\n", params->logical_op);
}