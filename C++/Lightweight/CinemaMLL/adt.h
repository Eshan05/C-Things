#ifndef ADT_H_INCLUDED
#define ADT_H_INCLUDED

#include <cstdlib>
#include <iostream>

#define First(L) L.First
#define Info(P)  P->Info
#define Next(P)  P->Next
#define Prev(P)  P->Prev
#define Film(P)  P->Film

using namespace std;

typedef struct elementRelation *addrRelation;
struct listRelation {
  addrRelation First;
};

struct InfoTypeParent {
  int noDirector;        // Director number
  listRelation Relation; // Relation list
  string Name;           // Director's name
};

struct InfoTypeChild {
  int noFilm;   // Film number
  int Status;   // Status
  string Title; // Film title
  string Main;  // Main director
};

typedef struct elementParent *addrP;
typedef struct elementChild *addrC;

struct elementParent {
  InfoTypeParent Info;
  addrP Next; // Next element in the parent list
  addrP Prev; // Previous element in the parent list
};

struct elementChild {
  InfoTypeChild Info;
  addrC Next; // Next element in the child list
  addrC Prev; // Previous element in the child list
};

struct elementRelation {
  addrC Film;        // Film element
  addrRelation Next; // Next relation element
  addrRelation Prev; // Previous relation element
};

struct listParent {
  addrP First; // First element in the parent list
};

struct listChild {
  addrC First; // First element in the child list
};

// Function declarations
bool isEmptyParent(listParent L);
bool isEmptyChild(listChild L);
bool isEmptyRelation(listRelation L);
void newParentList(listParent &L);
void newChildList(listChild &L);
void createListRelation(listRelation &L);
addrP allocateDirector(InfoTypeParent x);
addrC allocateFilm(InfoTypeChild x);
addrRelation allocateRelation(addrC x);
void insertLastDirector(listParent &L, addrP P);
void insertLastFilm(listChild &L, addrC P);
void createRelation(listChild LFil, listParent LSut, int noSut, int noFil);
void deleteDirector(listParent &L, addrP &P);
void deleteFilm(listChild &L, addrC &P);
addrP seqSearchDirector(listParent L, int x);
addrC seqSearchFilm(listChild L, int x);
void outputDirector(listParent L);
void outputFilm(listChild L);
void outputFilmSearch(listParent LSut, int noSut);
void outputFilmsByTwoDirectors(listChild LFil);
void outputMostInvolvedDirector(listParent LSut);
void outputLeastInvolvedAssistant(listParent LSut);
void editDirector(listParent LSut);
void editFilm(listChild LFil);

#endif // ADT_H_INCLUDED
