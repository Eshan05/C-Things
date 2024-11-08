#include <stdio.h>
#include <stdlib.h>

void cls();
int main() {
  system("cls");
  printf("\033[0;35mBun\033[0m is a fast JavaScript runtime, package manager, "
         "bundler and test runner. \033[1;30m(1.1.30+7996d06b8)\033[0m");
  printf("\n\n\033[1mUsage: bun <command> \033[1;36m[...flags]\033[1;37m "
         "[...args]\n\n");
  printf("Commands:\033[0m\n");
  printf("  \033[1;35mrun       \033[38;5;242m./my-script.ts       "
         "\033[0mExecute a file with Bun\n");
  printf("  \033[38;5;242m          lint                 \033[0mRun a "
         "package.json script\n");
  printf("  \033[1;35mtest                           \033[0mRun unit tests "
         "with Bun\n");
  printf(
      "  \033[1;35mx         \033[38;5;242mprettier             \033[0mExecute "
      "a package binary (CLI), installing if needed \033[38;5;242m(bunx)\n");
  printf("  \033[1;35mrepl                           \033[0mStart a REPL "
         "session with Bun\n");
  printf("  \033[1;35mexec                           \033[0mRun a shell script "
         "directly with Bun\n");
  printf("\n");
  printf("  \033[1;34minstall                        \033[0mInstall "
         "dependencies for a package.json \033[38;5;242m(bun i)\n");
  printf("  \033[1;34madd       \033[38;5;242mtailwindcss          \033[0mAdd "
         "a dependency to package.json \033[38;5;242m(bun a)\n");
  printf(
      "  \033[1;34mremove    \033[38;5;242mjquery               "
      "\033[0mRemove a dependency from package.json \033[38;5;242m(bun rm)\n");
  printf("  \033[1;34mupdate    \033[38;5;242melysia               "
         "\033[0mUpdate outdated dependencies\n");
  printf("  \033[1;34moutdated                       \033[0mDisplay latest "
         "versions of outdated dependencies\n");
  printf("  \033[1;34mlink      \033[38;5;242m[<package>]          "
         "\033[0mRegister or link a local npm package\n");
  printf("  \033[1;34munlink                         \033[0mUnregister a local "
         "npm package\n");
  printf("  \033[1;34mpublish                        \033[0mPublish a package "
         "to the npm registry\n");
  // rgb(59, 120, 255)
  // rgb(29, 60, 127)
  printf("  \033[1;34mpatch \033[38;2;29;60;127m<pkg>                    "
         "\033[0mPrepare a package for patching\n");
  printf("  \033[1;34mpm \033[38;2;29;60;127m<subcommand>                "
         "\033[0mAdditional package management utilities\n");
  printf("\n");
  printf("  \033[1;33mbuild     \033[1;30m./a.ts ./b.jsx       \033[0mBundle "
         "TypeScript & JavaScript into a single file\n");
  printf("\n");
  printf("  \033[1;36minit                           \033[0mStart an empty Bun "
         "project from a blank template\n");
  printf("  \033[1;36mcreate    \033[1;30msvelte               \033[0mCreate a "
         "new project from a template \033[38;5;242m(bun c)\n");
  printf("  \033[1;36mupgrade                        \033[0mUpgrade to latest "
         "version of Bun.\n");
  printf("  \033[1;30m<command> \033[1;36m--help               \033[0mPrint "
         "help text for command.\n");

  printf("\033[0m");
  printf("\nLearn more about Bun:            \033[0;35mhttps://bun.sh/docs\n");
  printf("\033[0mJoin our Discord community:      "
         "\033[1;34mhttps://bun.sh/discord");
  printf("\033[0m\n");

  return 0;
}

// 33 Spaces from left for description
// 12 for middle things in gray

void cls() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}