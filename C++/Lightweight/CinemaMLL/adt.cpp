#include "adt.h"

bool isEmptyParent(listParent L) { return (First(L) == NULL); }

bool isEmptyChild(listChild L) { return (First(L) == NULL); }

bool isEmptyRelation(listRelation L) { return (First(L) == NULL); }

void newParentList(listParent &L) { First(L) = NULL; }

void newChildList(listChild &L) { First(L) = NULL; }

void createListRelation(listRelation &L) { First(L) = NULL; }

elementParent *allocateDirector(InfoTypeParent x) {
  listRelation R1;
  createListRelation(R1);
  elementParent *P = new elementParent;
  Info(P).noDirector = x.noDirector;
  Info(P).Name = x.Name;
  Info(P).Relation = R1;
  Next(P) = NULL;
  Prev(P) = NULL;
  return P;
}

elementChild *allocateFilm(InfoTypeChild x) {
  elementChild *P = new elementChild;
  Info(P).Status = 0;
  Info(P).noFilm = x.noFilm;
  Info(P).Title = x.Title;
  Next(P) = NULL;
  Prev(P) = NULL;
  return P;
}

elementRelation *allocateRelation(elementChild *x) {
  elementRelation *P = new elementRelation;
  Film(P) = x;
  Prev(P) = NULL;
  Next(P) = NULL;
  return P;
}

void insertLastDirector(listParent &L, elementParent *P) {
  if(!isEmptyParent(L)) {
    elementParent *Q = First(L);
    while(Next(Q) != NULL) { Q = Next(Q); }
    Next(Q) = P;
    Prev(P) = Q;
  } else {
    First(L) = P;
  }
}

void insertLastFilm(listChild &L, elementChild *P) {
  if(!isEmptyChild(L)) {
    elementChild *Q = First(L);
    while(Next(Q) != NULL) { Q = Next(Q); }
    Next(Q) = P;
    Prev(P) = Q;
  } else {
    First(L) = P;
  }
}

void createRelation(listChild LFil, listParent LSut, int noSut, int noFil) {
  elementChild *Destination = seqSearchFilm(LFil, noFil);
  elementParent *Source = seqSearchDirector(LSut, noSut);

  if(Source != NULL && Destination != NULL) {
    elementRelation *Pr = allocateRelation(Destination);
    if(isEmptyRelation(Info(Source).Relation)) {
      First(Info(Source).Relation) = Pr;
    } else {
      elementRelation *Q = First(Info(Source).Relation);
      while(Next(Q) != NULL) { Q = Next(Q); }
      Next(Q) = Pr;
      Prev(Pr) = Q;
    }

    Info(Destination).Status++;
    if(Info(Destination).Status == 1) {
      Info(Destination).Main = Info(Source).Name;
      cout << "  " << Info(Destination).Main << " as the main director" << endl;
    } else {
      cout << "  " << Info(Source).Name << " as the assistant" << endl;
    }
    cout << "  CONNECTED DATA" << endl;
    system("pause");
  } else {
    cout << "  Director or Film number does not match" << endl;
  }
}

void deleteDirector(listParent &L, elementParent *&P) {
  elementRelation *R1 = First(Info(P).Relation);
  while(R1 != NULL) {
    Info(Film(R1)).Status--;
    R1 = Next(R1);
  }

  if(P == First(L)) {
    First(L) = Next(P);
    if(First(L) != NULL) { Prev(First(L)) = NULL; }
  } else {
    elementParent *Q = Prev(P);
    Next(Q) = Next(P);
    if(Next(P) != NULL) { Prev(Next(P)) = Q; }
  }
  delete P;
  P = NULL;
}

void deleteFilm(listChild &L, elementChild *&P) {
  if(P == First(L)) {
    First(L) = Next(P);
    if(First(L) != NULL) { Prev(First(L)) = NULL; }
  } else {
    elementChild *Q = Prev(P);
    Next(Q) = Next(P);
    if(Next(P) != NULL) { Prev(Next(P)) = Q; }
  }
  delete P;
  P = NULL;
}

elementParent *seqSearchDirector(listParent L, int x) {
  elementParent *P = First(L);
  while(P != NULL && Info(P).noDirector != x) { P = Next(P); }
  return P;
}

elementChild *seqSearchFilm(listChild L, int x) {
  elementChild *P = First(L);
  while(P != NULL && Info(P).noFilm != x) { P = Next(P); }
  return P;
}

void outputDirector(listParent L) {
  if(isEmptyParent(L)) {
    cout << "  Director Data Empty" << endl;
  } else {
    elementParent *P = First(L);
    cout << endl;
    while(P != NULL) {
      cout << "  No." << Info(P).noDirector << " " << Info(P).Name << endl;
      P = Next(P);
    }
  }
}

void outputFilm(listChild L) {
  if(isEmptyChild(L)) {
    cout << "  Film Data Empty" << endl;
  } else {
    elementChild *P = First(L);
    cout << endl;
    while(P != NULL) {
      cout << "  No." << Info(P).noFilm << " " << Info(P).Title << endl;
      P = Next(P);
    }
  }
}

void outputFilmSearch(listParent LSut, int noSut) {
  elementParent *Source = seqSearchDirector(LSut, noSut);
  if(Source != NULL) {
    elementRelation *P = First(Info(Source).Relation);
    if(P == NULL) {
      cout << "  No Film data for this Director " << endl;
    } else {
      cout << endl;
      while(P != NULL) {
        cout << "    No." << Info(Film(P)).noFilm << " " << Info(Film(P)).Title
             << endl;
        P = Next(P);
      }
    }
  } else {
    cout << "  Director not found" << endl;
  }
}

void outputFilmsByTwoDirectors(listChild LFil) {
  elementChild *P = First(LFil);
  int c = 0;
  while(P != NULL) {
    if(Info(P).Status == 2) {
      if(c == 0) cout << endl;
      cout << " No." << Info(P).noFilm << " " << Info(P).Title << endl;
      c++;
    }
    P = Next(P);
  }
  if(c == 0) cout << "  No films made by 2 directors " << endl;
}

void outputMostInvolvedDirector(listParent LSut) {
  if(!isEmptyParent(LSut)) {
    elementParent *P = First(LSut);
    elementParent *M = NULL;
    int f = 0;
    while(P != NULL) {
      elementRelation *Q = First(Info(P).Relation);
      int x = 0;
      while(Q != NULL) {
        x++;
        Q = Next(Q);
      }
      if(x > f) {
        M = P;
        f = x;
      }
      P = Next(P);
    }
    if(f > 0) {
      cout << "  The director most involved in film projects is: "
           << Info(M).Name << endl;
    } else {
      cout << "  No director data with the most films" << endl;
    }
  } else {
    cout << "  No director data" << endl;
  }
}

void outputLeastInvolvedAssistant(listParent LSut) {
  int x, y = 0;
  elementParent *M = NULL;
  elementParent *P = First(LSut);

  while(P != NULL) {
    x = 0;
    elementRelation *Q = First(Info(P).Relation);
    while(Q != NULL) {
      elementChild *film = Film(Q);
      if(Info(film).Main != Info(P).Name) { x++; }
      Q = Next(Q);
    }
    if(x != 0 && (y == 0 || x < y)) {
      M = P;
      y = x;
    }
    P = Next(P);
  }
  if(M != NULL) {
    cout << "  Assistant director with the least involvement: " << Info(M).Name
         << endl;
  } else {
    cout << "  No assistant data found." << endl;
  }
}

void editDirector(listParent LSut) {
  int x;
  cout << "  Enter director's number: ";
  cin >> x;
  elementParent *P = seqSearchDirector(LSut, x);

  if(P != NULL) {
    string directorName;
    cout << "  Enter director's name: ";
    cin >> directorName;
    Info(P).Name = directorName;
  } else {
    cout << "  Director not found." << endl;
  }
}

void editFilm(listChild LFil) {
  int x;
  cout << "  Enter film number: ";
  cin >> x;
  elementChild *C = seqSearchFilm(LFil, x);

  if(C != NULL) {
    string filmName;
    cout << "  Enter film title: ";
    cin >> filmName;
    Info(C).Title = filmName;
  } else {
    cout << "  Film not found." << endl;
  }
}
