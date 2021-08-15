#include "main.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_LEFT 75
#define ARROW_RIGHT 77
#define ENTER_KEY 13

int main() {
  MainMenuOptions user_option;
  std::vector<NotesData> notes_vector;

  LoadSavedNotes(notes_vector);
  PrintMainMenuHighlighted(MainMenuOptions::kNewNote);
  user_option = ScrollMainMenu();
  _getch();
  return 0;
}

MainMenuOptions ScrollMainMenu() {
  MainMenuOptions last_item_scrolled = MainMenuOptions::kNewNote;

  while(true) {
    /* Here we have two switch statements, with two more inside them: basically, the current position of the user in the main menu (first switch with 4 options)
    and the two possible new positions after the user enters the UP arrow, the DOWN arrow or the enter for going to the selected process */
    switch(last_item_scrolled) {
      case MainMenuOptions::kNewNote: {
        switch(_getch()) {
          case ARROW_UP: {
            PrintMainMenuHighlighted(MainMenuOptions::kExit);
            last_item_scrolled = MainMenuOptions::kExit;
            break;
          }
          case ARROW_DOWN: {
            PrintMainMenuHighlighted(MainMenuOptions::kEditNote);
            last_item_scrolled = MainMenuOptions::kEditNote;
            break;
          }
          case ENTER_KEY: {
            return last_item_scrolled;
          }
        }
        break;
      }
      case MainMenuOptions::kEditNote: {
        switch(_getch()) {
          case ARROW_UP: {
            PrintMainMenuHighlighted(MainMenuOptions::kNewNote);
            last_item_scrolled = MainMenuOptions::kNewNote;
            break;
          }
          case ARROW_DOWN: {
            PrintMainMenuHighlighted(MainMenuOptions::kDeleteNote);
            last_item_scrolled = MainMenuOptions::kDeleteNote;
            break;
          }
          case ENTER_KEY: {
            return last_item_scrolled;
          }
        }
        break;
      }
      case MainMenuOptions::kDeleteNote: {
        switch(_getch()) {
          case ARROW_UP: {
            PrintMainMenuHighlighted(MainMenuOptions::kEditNote);
            last_item_scrolled = MainMenuOptions::kEditNote;
            break;
          }
          case ARROW_DOWN: {
            PrintMainMenuHighlighted(MainMenuOptions::kExit);
            last_item_scrolled = MainMenuOptions::kExit;
            break;
          }
          case ENTER_KEY: {
            return last_item_scrolled;
          }
        }
        break;
      }
      case MainMenuOptions::kExit: {
        switch(_getch()) {
          case ARROW_UP: {
            PrintMainMenuHighlighted(MainMenuOptions::kDeleteNote);
            last_item_scrolled = MainMenuOptions::kDeleteNote;
            break;
          }
          case ARROW_DOWN: {
            PrintMainMenuHighlighted(MainMenuOptions::kNewNote);
            last_item_scrolled = MainMenuOptions::kNewNote;
            break;
          }
          case ENTER_KEY: {
            return last_item_scrolled;
          }
        }
        break;
      }
    }
  }
}

void LoadSavedNotes(std::vector<NotesData>& notes_vector) {
  std::ifstream notes_txt;
  std::string line_temporal;
  NotesData notes_temporal;

  notes_txt.open("notes.txt");
  for(auto i = 0; notes_txt.eof() == false ; ++i) {
    getline(notes_txt, line_temporal);
    if(notes_txt.eof() == true) break;
    notes_temporal.title = line_temporal;
    getline(notes_txt, line_temporal);
    notes_temporal.content = line_temporal;
    notes_vector.push_back(notes_temporal);
  }
  notes_txt.close();
  return;
}

void PrintMainMenuHighlighted(MainMenuOptions highlighted_option) {
  ClearScreen();
  switch(highlighted_option) {
    case MainMenuOptions::kNewNote: {
      std::cout << "[New note]" << std::endl << std::endl;
      std::cout << "Edit note" << std::endl << std::endl;
      std::cout << "Delete note" << std::endl << std::endl;
      std::cout << "Exit" << std::endl << std::endl;
      break;
    }
    case MainMenuOptions::kEditNote: {
      std::cout << "New note" << std::endl << std::endl;
      std::cout << "[Edit note]" << std::endl << std::endl;
      std::cout << "Delete note" << std::endl << std::endl;
      std::cout << "Exit" << std::endl << std::endl;
      break;
    }
    case MainMenuOptions::kDeleteNote: {
      std::cout << "New note" << std::endl << std::endl;
      std::cout << "Edit note" << std::endl << std::endl;
      std::cout << "[Delete note]" << std::endl << std::endl;
      std::cout << "Exit" << std::endl << std::endl;
      break;
    }
    case MainMenuOptions::kExit: {
      std::cout << "New note" << std::endl << std::endl;
      std::cout << "Edit note" << std::endl << std::endl;
      std::cout << "Delete note" << std::endl << std::endl;
      std::cout << "[Exit]" << std::endl << std::endl;
      break;
    }
  }
  return;
}

void ClearScreen() {
  HANDLE                     hStdOut;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD                      count;
  DWORD                      cellCount;
  COORD                      homeCoords = { 0, 0 };

  hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
  if (hStdOut == INVALID_HANDLE_VALUE) return;

  /* Get the number of cells in the current buffer */
  if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
  cellCount = csbi.dwSize.X *csbi.dwSize.Y;

  /* Fill the entire buffer with spaces */
  if (!FillConsoleOutputCharacter(
    hStdOut,
    (TCHAR) ' ',
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Fill the entire buffer with the current colors and attributes */
  if (!FillConsoleOutputAttribute(
    hStdOut,
    csbi.wAttributes,
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Move the cursor home */
  SetConsoleCursorPosition( hStdOut, homeCoords );
}
