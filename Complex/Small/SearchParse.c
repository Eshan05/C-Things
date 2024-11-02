#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX_TERMS  10
#define MAX_GROUPS 10

typedef struct {
  char *languages[MAX_TERMS];
  char *authors[MAX_TERMS];
  char *repos[MAX_TERMS];
  char *orgs[MAX_TERMS];
  char *paths[MAX_TERMS];
  char *contents[MAX_TERMS];
  char *keywords[MAX_TERMS];
  int stars;
  char *stars_op;
  int not_op;
  int language_count;
  int author_count;
  int repo_count;
  int org_count;
  int path_count;
  int content_count;
  int keyword_count;
} SearchParams;

typedef struct {
  SearchParams params;
  char *logical_op;
} LogicalGroup;

typedef struct {
  LogicalGroup groups[MAX_GROUPS];
  int group_count;
} SearchQuery;

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
void print_params(const SearchQuery *query);
void parse_search(char *input, SearchQuery *query);

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
      SearchQuery query;
      parse_search(search, &query);
      print_params(&query);

      // Free allocated memory
      for (int i = 0; i < query.group_count; i++) {
        SearchParams *params = &query.groups[i].params;
        for (int j = 0; j < params->language_count; j++)
          free(params->languages[j]);
        for (int j = 0; j < params->author_count; j++) free(params->authors[j]);
        for (int j = 0; j < params->repo_count; j++) free(params->repos[j]);
        for (int j = 0; j < params->org_count; j++) free(params->orgs[j]);
        for (int j = 0; j < params->path_count; j++) free(params->paths[j]);
        for (int j = 0; j < params->content_count; j++)
          free(params->contents[j]);
        for (int j = 0; j < params->keyword_count; j++)
          free(params->keywords[j]);
        free(query.groups[i].logical_op);
      }
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

void parse_search(char *input, SearchQuery *query) {
  memset(query, 0, sizeof(SearchQuery));

  char *token = strtok(input, " ");
  SearchParams current_params;
  memset(&current_params, 0, sizeof(SearchParams)); // Initialize current_params

  while (token != NULL) {
    if (strcmp(token, "AND") == 0 || strcmp(token, "OR") == 0) {
      if (current_params.language_count > 0 ||
          current_params.author_count > 0 || current_params.repo_count > 0 ||
          current_params.org_count > 0 || current_params.path_count > 0 ||
          current_params.content_count > 0 ||
          current_params.keyword_count > 0 || current_params.stars > 0) {

        query->groups[query->group_count].params = current_params;
        query->groups[query->group_count].logical_op = strdup(token);
        query->group_count++;
        memset(&current_params, 0,
               sizeof(SearchParams)); // Reset current_params
      }
    } else {
      // Handle parameter types
      if (strncmp(token, "language:", 9) == 0) {
        if (current_params.language_count < MAX_TERMS) {
          current_params.languages[current_params.language_count++] =
              strdup(token + 9);
        }
      } else if (strncmp(token, "author:", 7) == 0) {
        if (current_params.author_count < MAX_TERMS) {
          current_params.authors[current_params.author_count++] =
              strdup(token + 7);
        }
      } else if (strncmp(token, "repo:", 5) == 0) {
        if (current_params.repo_count < MAX_TERMS) {
          current_params.repos[current_params.repo_count++] = strdup(token + 5);
        }
      } else if (strncmp(token, "org:", 4) == 0) {
        if (current_params.org_count < MAX_TERMS) {
          current_params.orgs[current_params.org_count++] = strdup(token + 4);
        }
      } else if (strncmp(token, "path:", 5) == 0) {
        if (current_params.path_count < MAX_TERMS) {
          current_params.paths[current_params.path_count++] = strdup(token + 5);
        }
      } else if (strncmp(token, "content:", 8) == 0) {
        if (current_params.content_count < MAX_TERMS) {
          current_params.contents[current_params.content_count++] =
              strdup(token + 8);
        }
      } else if (strncmp(token, "stars:", 6) == 0) {
        current_params.stars_op =
            strdup(token + 6); // Store the stars operation
        current_params.stars = 1;
      } else if (strncmp(token, "NOT", 3) == 0) {
        current_params.not_op = 1;
        token += 4; // Move past "NOT"
        if (current_params.keyword_count < MAX_TERMS) {
          current_params.keywords[current_params.keyword_count++] =
              strdup(token);
        }
      } else {
        if (current_params.keyword_count < MAX_TERMS) {
          current_params.keywords[current_params.keyword_count++] =
              strdup(token);
        }
      }
    }
    token = strtok(NULL, " ");
  }

  // Add the last group if it contains any parameters
  if (current_params.language_count > 0 || current_params.author_count > 0 ||
      current_params.repo_count > 0 || current_params.org_count > 0 ||
      current_params.path_count > 0 || current_params.content_count > 0 ||
      current_params.keyword_count > 0 || current_params.stars > 0) {

    query->groups[query->group_count].params = current_params;
    query->groups[query->group_count].logical_op =
        NULL; // No logical operator for last group
    query->group_count++;
  }
}

void print_params(const SearchQuery *query) {
  printf("--/ Parsed Search Parameters: \\--\n");
  for (int i = 0; i < query->group_count; i++) {
    if (query->groups[i].logical_op) {
      printf("Logical Operator: %s\n", query->groups[i].logical_op);
    }

    const SearchParams *params = &query->groups[i].params;
    int has_params = 0;
    // Check and print each category only if it has parameters
    if (params->language_count > 0) {
      has_params = 1;
      printf("- Languages: ");
      for (int j = 0; j < params->language_count; j++) {
        printf("%s", params->languages[j]);
        if (j < params->language_count - 1) printf(", ");
      }
      printf("\n");
    }

    if (params->author_count > 0) {
      has_params = 1;
      printf("- Authors: ");
      for (int j = 0; j < params->author_count; j++) {
        printf("%s", params->authors[j]);
        if (j < params->author_count - 1) printf(", ");
      }
      printf("\n");
    }

    if (params->repo_count > 0) {
      has_params = 1;
      printf("- Repositories: ");
      for (int j = 0; j < params->repo_count; j++) {
        printf("%s", params->repos[j]);
        if (j < params->repo_count - 1) printf(", ");
      }
      printf("\n");
    }

    if (params->org_count > 0) {
      has_params = 1;
      printf("- Orgs: ");
      for (int j = 0; j < params->org_count; j++) {
        printf("%s", params->orgs[j]);
        if (j < params->org_count - 1) printf(", ");
      }
      printf("\n");
    }

    if (params->path_count > 0) {
      has_params = 1;
      printf("- Paths: ");
      for (int j = 0; j < params->path_count; j++) {
        printf("%s", params->paths[j]);
        if (j < params->path_count - 1) printf(", ");
      }
      printf("\n");
    }

    if (params->content_count > 0) {
      has_params = 1;
      printf("- Contents: ");
      for (int j = 0; j < params->content_count; j++) {
        printf("%s", params->contents[j]);
        if (j < params->content_count - 1) printf(", ");
      }
      printf("\n");
    }

    // Print stars information
    if (params->stars_op) {
      has_params = 1;
      printf("* Stars: %s\n", params->stars_op);
    }

    if (params->keyword_count > 0) {
      has_params = 1;
      printf("- Keywords: ");
      for (int j = 0; j < params->keyword_count; j++) {
        printf("%s", params->keywords[j]);
        if (j < params->keyword_count - 1) printf(", ");
      }
      printf("\n");
    }

    printf("- NOT Found: %s\n", params->not_op ? "Yes" : "No");
    // Only print a group if it has parameters
    if (!has_params) { printf("- No parameters found for this group.\n"); }
  }
}
