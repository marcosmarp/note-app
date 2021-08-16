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
  while (user_option != MainMenuOptions::kExit) {
    user_option = ScrollMainMenu();
    switch (user_option) {
      case MainMenuOptions::kNewNote: {
        NewNote(notes_vector);
        break;
      }
      case MainMenuOptions::kDisplayNotes: {
        DisplayNotes(notes_vector, true);
        break;
      }
      case MainMenuOptions::kEditNote: {
        EditNote(notes_vector);
        break;
      }
      case MainMenuOptions::kExit: {
        break;
      }
    }
  }
  return 0;
}

MainMenuOptions ScrollMainMenu() {
  MainMenuOptions last_item_scrolled = MainMenuOptions::kNewNote;
  PrintMainMenuHighlighted(MainMenuOptions::kNewNote);

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
            PrintMainMenuHighlighted(MainMenuOptions::kDisplayNotes);
            last_item_scrolled = MainMenuOptions::kDisplayNotes;
            break;
          }
          case ENTER_KEY: {
            return last_item_scrolled;
          }
        }
        break;
      }
      case MainMenuOptions::kDisplayNotes: {
        switch(_getch()) {
          case ARROW_UP: {
            PrintMainMenuHighlighted(MainMenuOptions::kNewNote);
            last_item_scrolled = MainMenuOptions::kNewNote;
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
            PrintMainMenuHighlighted(MainMenuOptions::kDisplayNotes);
            last_item_scrolled = MainMenuOptions::kDisplayNotes;
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
  while(notes_txt.eof() == false){
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
      std::cout << "Display notes" << std::endl << std::endl;
      std::cout << "Edit note" << std::endl << std::endl;
      std::cout << "Delete note" << std::endl << std::endl;
      std::cout << "Exit" << std::endl << std::endl;
      break;
    }
    case MainMenuOptions::kDisplayNotes: {
      std::cout << "New note" << std::endl << std::endl;
      std::cout << "[Display notes]" << std::endl << std::endl;
      std::cout << "Edit note" << std::endl << std::endl;
      std::cout << "Delete note" << std::endl << std::endl;
      std::cout << "Exit" << std::endl << std::endl;
      break;
    }
    case MainMenuOptions::kEditNote: {
      std::cout << "New note" << std::endl << std::endl;
      std::cout << "Display notes" << std::endl << std::endl;
      std::cout << "[Edit note]" << std::endl << std::endl;
      std::cout << "Delete note" << std::endl << std::endl;
      std::cout << "Exit" << std::endl << std::endl;
      break;
    }
    case MainMenuOptions::kDeleteNote: {
      std::cout << "New note" << std::endl << std::endl;
      std::cout << "Display notes" << std::endl << std::endl;
      std::cout << "Edit note" << std::endl << std::endl;
      std::cout << "[Delete note]" << std::endl << std::endl;
      std::cout << "Exit" << std::endl << std::endl;
      break;
    }
    case MainMenuOptions::kExit: {
      std::cout << "New note" << std::endl << std::endl;
      std::cout << "Display notes" << std::endl << std::endl;
      std::cout << "Edit note" << std::endl << std::endl;
      std::cout << "Delete note" << std::endl << std::endl;
      std::cout << "[Exit]" << std::endl << std::endl;
      break;
    }
  }
  return;
}

void NewNote(std::vector<NotesData>& stored_notes) {
  ClearScreen();
  std::cout << "NEW NOTE" << std::endl << std::endl;

  NotesData new_note_temporal;
  std::cout << "Title: ";
  getline(std::cin, new_note_temporal.title);
  std::cout << std::endl;
  std::cout << "Content: ";
  getline(std::cin, new_note_temporal.content);
  std::cout << std::endl << std::endl;
  stored_notes.push_back(new_note_temporal);

  std::ofstream notes_txt;
  notes_txt.open("notes.txt", std::ios::app);
  notes_txt << new_note_temporal.title << std::endl;
  notes_txt << new_note_temporal.content << std::endl;
  std::cout << "SUCCESFULLY UPLOADED NEW NOTE, RETURNING TO MAIN MENU";
  PrintDotsWithDelay(5, 500);
  return;
}

bool DisplayNotes(std::vector<NotesData>& stored_notes, bool calling_from_main) {
  /* This function can be called from the main menu or from the Edit note sector, in this case
  we dont want to delete the Edit note intro */
  if (calling_from_main == true) ClearScreen();
  std::cout << "STORED NOTES" << std::endl << std::endl;
  if(stored_notes.size() == 0) {
    std::cout << "You don't have any notes. You can create one in the main menu" << std::endl << std::endl;
    std::cout << "Press any key to return to main menu";
    _getch();
    return false;
  } 
  else {
    for(auto& it : stored_notes) {
      std::cout << "  Title: " << it.title << std::endl;
      std::cout << "  Content: " << it.content << std::endl << std::endl;
    }
  }
  if(calling_from_main == true) {
    std::cout << "Press any key to return to main menu";
    _getch();
  }
  return true;
}

void EditNote(std::vector<NotesData>& stored_notes) {
  auto user_option{EditOptions::kEditTitle};
  while (user_option != EditOptions::kExitToMainMenu) {
    ClearScreen();
    std::cout << "THIS ARE YOUR ";
    if(DisplayNotes(stored_notes, false) == false) {
      return;
    }
    std::string title_to_edit;
    auto note_to_edit = SearchForNoteByTitle(title_to_edit, stored_notes);
    while(note_to_edit == stored_notes.end()) {
      std::cout << "Enter the title of the note to edit [tipe 'exit' to return to main menu]: ";
      getline(std::cin, title_to_edit);
      std::cout << std::endl;
      if(title_to_edit == "exit") return;
      note_to_edit = SearchForNoteByTitle(title_to_edit, stored_notes);
      if(note_to_edit == stored_notes.end()) std::cout << "Inexistent title, try again. ";
    }

    user_option = ScrollEditMenu(title_to_edit);
    switch(user_option) {
      case EditOptions::kEditTitle: {
        EditTitle(note_to_edit->title, title_to_edit);
        break;
      }
      case EditOptions::kEditContent: {
        EditContent(note_to_edit->content, title_to_edit);
        break;
      }
    }
  }
  PrintNotesInTxt(stored_notes);
  return;
}

void PrintNotesInTxt(const std::vector<NotesData>& notes) {
  std::ofstream txt_file;
  txt_file.open("notes.txt");
  for(auto& it : notes) {
    txt_file << it.title << std::endl;
    txt_file << it.content << std::endl;
  }
  txt_file.close();
  return;
}

void EditTitle(std::string& title, std::string& original_title) {
  ClearScreen();
  std::cout << "NOTE '" << original_title << "'" << std::endl << std::endl;
  std::cout << "Enter new title: ";
  getline(std::cin, title);
  std::cout << std::endl;
  original_title = title;
  return;
}

void EditContent(std::string& content, const std::string title) {
  ClearScreen();
  std::cout << "NOTE '" << title << "'" << std::endl << std::endl;
  std::cout <<"Enter new content: ";
  getline(std::cin, content);
  std::cout << std::endl;
  return;
}

std::vector<NotesData>::iterator SearchForNoteByTitle(const std::string title, std::vector<NotesData>& notes) {
  auto it = notes.begin();
  while(it != notes.end()) {
    if(it->title == title) break;
    ++it;
  }
  return it;
}

EditOptions ScrollEditMenu(const std::string title) {
  auto last_item_scrolled{EditOptions::kEditTitle};
  PrintEditMenuHighlighted(EditOptions::kEditTitle, title);
  while(true) {
    /* Here we have two switch statements, with two more inside them: basically, the current position of the user in the main menu (first switch with 4 options)
    and the two possible new positions after the user enters the UP arrow, the DOWN arrow or the enter for going to the selected process */
    switch(last_item_scrolled) {
      case EditOptions::kEditTitle: {
        switch(_getch()) {
          case ARROW_UP: {
            PrintEditMenuHighlighted(EditOptions::kExitToMainMenu, title);
            last_item_scrolled = EditOptions::kExitToMainMenu;
            break;
          }
          case ARROW_DOWN: {
            PrintEditMenuHighlighted(EditOptions::kEditContent, title);
            last_item_scrolled = EditOptions::kEditContent;
            break;
          }
          case ENTER_KEY: {
            return last_item_scrolled;
          }
        }
        break;
      }
      case EditOptions::kEditContent: {
        switch(_getch()) {
          case ARROW_UP: {
            PrintEditMenuHighlighted(EditOptions::kEditTitle, title);
            last_item_scrolled = EditOptions::kEditTitle;
            break;
          }
          case ARROW_DOWN: {
            PrintEditMenuHighlighted(EditOptions::kExitToEditScreen, title);
            last_item_scrolled = EditOptions::kExitToEditScreen;
            break;
          }
          case ENTER_KEY: {
            return last_item_scrolled;
          }
        }
        break;
      }
      case EditOptions::kExitToEditScreen: {
        switch(_getch()) {
          case ARROW_UP: {
            PrintEditMenuHighlighted(EditOptions::kEditContent, title);
            last_item_scrolled = EditOptions::kEditContent;
            break;
          }
          case ARROW_DOWN: {
            PrintEditMenuHighlighted(EditOptions::kExitToMainMenu, title);
            last_item_scrolled = EditOptions::kExitToMainMenu;
            break;
          }
          case ENTER_KEY: {
            return last_item_scrolled;
          }
        }
        break;
      }
      case EditOptions::kExitToMainMenu: {
        switch(_getch()) {
          case ARROW_UP: {
            PrintEditMenuHighlighted(EditOptions::kExitToEditScreen, title);
            last_item_scrolled = EditOptions::kExitToEditScreen;
            break;
          }
          case ARROW_DOWN: {
            PrintEditMenuHighlighted(EditOptions::kEditTitle, title);
            last_item_scrolled = EditOptions::kEditTitle;
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

void PrintEditMenuHighlighted(const EditOptions highlighted_option, const std::string note_title) {
  ClearScreen();
  std::cout << "NOTE '" << note_title << "'" << std::endl << std::endl;
  switch(highlighted_option) {
    case EditOptions::kEditTitle: {
      std::cout << "[Edit title]" << std::endl << std::endl;
      std::cout << "Edit content" << std::endl << std::endl;
      std::cout << "Return to edit menu" << std::endl << std::endl;
      std::cout << "Return to main menu" << std::endl << std::endl;
      break;
    }
    case EditOptions::kEditContent: {
      std::cout << "Edit title" << std::endl << std::endl;
      std::cout << "[Edit content]" << std::endl << std::endl;
      std::cout << "Return to edit menu" << std::endl << std::endl;
      std::cout << "Return to main menu" << std::endl << std::endl;
      break;
    }
    case EditOptions::kExitToEditScreen: {
      std::cout << "Edit title" << std::endl << std::endl;
      std::cout << "Edit content" << std::endl << std::endl;
      std::cout << "[Return to edit menu]" << std::endl << std::endl;
      std::cout << "Return to main menu" << std::endl << std::endl;
      break;
    }
    case EditOptions::kExitToMainMenu: {
      std::cout << "Edit title" << std::endl << std::endl;
      std::cout << "Edit content" << std::endl << std::endl;
      std::cout << "Return to edit menu" << std::endl << std::endl;
      std::cout << "[Return to main menu]" << std::endl << std::endl;
      break;
    }
  }
  return;
}

void PrintDotsWithDelay(int amount_of_dots, int delay) {
  for(auto i = 0 ; i < amount_of_dots ; ++i) {
    std::cout << ".";
    Sleep(delay);
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
