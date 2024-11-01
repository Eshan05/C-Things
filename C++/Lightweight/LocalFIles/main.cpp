#include "MLL.h"
#include "utils.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
  bool flag = true;
  filesystem::path cwd;
  MultiLinkedList myMLList;

  while(flag) {
    system("cls");
    cout << "---/ Welcome \\---\n\n";

    // Ask for the valid path only once
    if(cwd.empty()) {
      cout << "NOTE: Do not use backslashes\n";
      cout << "Enter a valid path:\n";
      cout << "-> ";
      string input_path;
      cin >> input_path;
      cout << endl;
      cwd = input_path;
      int file_count;
      vector<vector<string>> files = files2dVector(cwd, file_count);

      for(int i = 0; i < file_count; i++) {
        myMLList.addNode(files[i][0], files[i][1], files[i][2]);
      }
    }

    myMLList.printInfosName();

    cout << "\n=== Options: ===\n"
         << "  1: Search filename\n"
         << "  2: Search extension\n"
         << "  3: Search file size\n"
         << "  4: Remove filename from list\n"
         << "  5: Update the list\n"
         << "  6: Traverse list\n"
         << "  7: Exit." << endl;

    cout << "  * Choose an option: ";
    int arg;
    cin >> arg;
    int input_traverse_list;
    string input_name, input_ext, input_size, upper_input_size;

    switch(arg) {
      case 1:
        cout << "  Enter file name:\n  -> ";
        cin >> input_name;
        myMLList.searchFileName(input_name);
        break;
      case 2:
        cout << "  Enter file extension:\n  -> ";
        cin >> input_ext;
        myMLList.searchFileExt(input_ext);
        break;
      case 3:
        cout << "  Enter file size:\n  -> ";
        cin >> input_size;
        cout << "  Enter upper file size (Optional):\n  -> ";
        cin.ignore();                   // Clear the input buffer
        getline(cin, upper_input_size); // Read a line, allowing for empty input
        myMLList.searchFileSize(input_size, upper_input_size);
        break;
      case 4:
        cout << "  Enter file name:\n  -> ";
        cin.ignore(); // Clear buffer before input
        cin >> input_name;
        myMLList.deleteNode(input_name);
        break;
      case 5: {
        myMLList.destroyList();
        int file_count;
        vector<vector<string>> files = files2dVector(cwd, file_count);
        for(int i = 0; i < file_count; i++) {
          myMLList.addNode(files[i][0], files[i][1], files[i][2]);
        }
        break;
      }
      case 6:
        cout << "  -> Please enter sorting order:\n"
             << "    1: Ordered by filename\n"
             << "    2: Ordered by file extension\n"
             << "    3: Ordered by file size\n";
        cout << "    Enter -> ";
        cin >> input_traverse_list;
        switch(input_traverse_list) {
          case 1: myMLList.printInfosName(); break;
          case 2: myMLList.printInfosExt(); break;
          case 3: myMLList.printInfosSize(); break;
          default: cout << "Invalid option." << endl; break;
        }
        break;
      case 7:
        cout << "  * Exiting...\n";
        flag = false;
        break;
      default: cout << "Invalid argument, run again!\n"; break;
    }

    // Pause to let the user see results before clearing the screen
    cout << "\nPress Enter to continue...";
    cin.ignore(); // Ignore the previous newline character
    cin.get();    // Wait for Enter
  }

  return 0;
}
