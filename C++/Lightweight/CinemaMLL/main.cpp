#include "adt.cpp"

int directorCount = 0;
int filmCount = 0;

void menu(listParent &directorList, listChild &filmList) {
  int choice;
  do {
    cout << "\n=== Select a menu ===" << endl;
    cout << "  1. Input Data" << endl;
    cout << "  2. Delete Data" << endl;
    cout << "  3. Display Data" << endl;
    cout << "  4. Link Data" << endl;
    cout << "  5. Edit Data" << endl;
    cout << "  0. Exit" << endl << endl;
    cout << "  Your choice: ";
    cin >> choice;

    switch(choice) {
      case 1: { // Input Data
        system("cls");
        int dataType;
        cout << "  Chosen option 1" << endl;
        cout << "  -> Input Data:" << endl;
        cout << "    1. Director" << endl;
        cout << "    2. Film" << endl;
        cout << "    3. Go back" << endl;
        cout << "    Your choice: ";
        cin >> dataType;

        if(dataType == 1) {
          system("cls");
          InfoTypeParent x;
          cout << "Enter Director's Name: ";
          cin.ignore();
          getline(cin, x.Name);
          x.noDirector = ++directorCount; // Increment before assignment
          elementParent *P = allocateDirector(x);
          insertLastDirector(directorList, P);
        } else if(dataType == 2) {
          system("cls");
          InfoTypeChild x;
          cout << "Enter Film Title: ";
          cin.ignore();
          getline(cin, x.Title);
          x.noFilm = ++filmCount; // Increment before assignment
          elementChild *P = allocateFilm(x);
          insertLastFilm(filmList, P);
        } else if(dataType == 3) {
          system("cls");
          break;
        }
        break;
      }

      case 2: { // Delete Data
        system("cls");
        outputDirector(directorList);
        cout << "  Chosen option 2" << endl;
        cout << "  -> Delete Data:" << endl;
        cout << "    1. Director" << endl;
        cout << "    2. Film" << endl;
        cout << "    3. Go back" << endl;
        cout << "    Your choice: ";
        int dataType;
        cin >> dataType;

        if(dataType == 1) {
          system("cls");
          int id;
          cout << " Enter the Director ID to delete: ";
          cin >> id;
          elementParent *P = seqSearchDirector(directorList, id);
          if(P != NULL) {
            deleteDirector(directorList, P);
            cout << " Director deleted successfully" << endl;
          } else {
            cout << " Director not found" << endl;
          }
        } else if(dataType == 2) {
          system("cls");
          int id;
          cout << " Enter the Film ID to delete: ";
          cin >> id;
          elementChild *P = seqSearchFilm(filmList, id);
          if(P != NULL) {
            deleteFilm(filmList, P);
            cout << " Film deleted successfully" << endl;
          } else {
            cout << " Film not found" << endl;
          }
        } else if(dataType == 3) {
          system("cls");
          break;
        }
        break;
      }

      case 3: { // Display Data
        system("cls");
        cout << "  Chosen option 3" << endl;
        cout << "  -> Display data:" << endl;
        cout << "    1. Director" << endl;
        cout << "    2. Film" << endl;
        cout << "    3. Films by a specific Director" << endl;
        cout << "    4. Films made by 2 Directors" << endl;
        cout << "    5. Director with the most films" << endl;
        cout << "    6. Assistant director with the least involvement" << endl;
        cout << "    7. Go back" << endl;
        cout << "    Your choice: ";
        int x;
        cin >> x;

        switch(x) {
          case 1: outputDirector(directorList); break;
          case 2: outputFilm(filmList); break;
          case 3: {
            if(isEmptyParent(directorList) || isEmptyChild(filmList)) {
              cout << " Director or Film data is empty" << endl;
            } else {
              int directorId;
              cout << " Choose a Director: " << endl;
              outputDirector(directorList);
              cout << " Enter Director ID: ";
              cin >> directorId;
              outputFilmSearch(directorList, directorId);
            }
            break;
          }
          case 4: outputFilmsByTwoDirectors(filmList); break;
          case 5: outputMostInvolvedDirector(directorList); break;
          case 6: outputLeastInvolvedAssistant(directorList); break;
          case 7: system("cls"); break;
          default: cout << "Invalid choice." << endl;
        }
        system("pause");
        break;
      }

      case 4: { // Link Data
        system("cls");
        cout << "  Chosen option 4" << endl;
        if(isEmptyParent(directorList) || isEmptyChild(filmList)) {
          cout << "  No Director or Film data " << endl;
        } else {
          int directorNo, filmNo;
          cout << "  Choose a Director: " << endl;
          outputDirector(directorList);
          cout << "  Enter Director ID: ";
          cin >> directorNo;
          cout << "  Choose a Film: " << endl;
          outputFilm(filmList);
          cout << "  Enter Film ID: ";
          cin >> filmNo;
          createRelation(filmList, directorList, directorNo, filmNo);
        }
        break;
      }

      case 5: { // Edit Data
        system("cls");
        cout << "  Chosen option 5" << endl;
        cout << "  -> Edit Data:" << endl;
        cout << "    1. Director" << endl;
        cout << "    2. Film" << endl;
        cout << "    3. Go back" << endl;
        cout << "    Your choice: ";
        int x;
        cin >> x;

        if(x == 1) {
          outputDirector(directorList);
          cout << " Enter the Director ID to edit: ";
          int directorId;
          cin >> directorId;
          editDirector(directorList);
        } else if(x == 2) {
          outputFilm(filmList);
          cout << " Enter the Film ID to edit: ";
          int filmId;
          cin >> filmId;
          editFilm(filmList);
        } else if(x == 3) {
          system("cls");
          break;
        }
        break;
      }

      case 0: // Exit
        cout << "  Exiting...";
        break;

      default: cout << "  Invalid choice. Please try again." << endl; break;
    }
  } while(choice != 0);
}

int main() {
  listParent directorList;
  listChild filmList;

  system("cls");
  cout << "\t---------WELCOME TO---------\n";
  cout << "\t-------MOVIE DATABASE-------\n\n";

  newParentList(directorList);
  newChildList(filmList);

  menu(directorList, filmList);
  return 0;
}
