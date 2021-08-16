#pragma once
#include <string>
#include <vector>
#include <fstream>

struct NotesData {
  std::string title;
  std::string content;
};

enum class MainMenuOptions {
  kNewNote, 
  kDisplayNotes, 
  kEditNote, 
  kDeleteNote, 
  kExit, 
  kInvalid,
};

enum class EditOptions {
  kEditTitle,
  kEditContent,
  kExitToEditScreen,
  kExitToMainMenu,
};

MainMenuOptions ScrollMainMenu(); // Infite loop that keeps asking the user for an arrok key to scroll though the menu or an enter to go the selected option
void PrintMainMenuHighlighted(MainMenuOptions); // Prints the main menu with the specified option highlighted
void PrintDotsWithDelay(int, int); // Prints the specified amount of dots with the specified delay
void ClearScreen(); // Clears the console output
void LoadSavedNotes(std::vector<NotesData>&); // Updates the vector with the saved txt notes
void NewNote(std::vector<NotesData>&); // Uploads new note to the vector
bool DisplayNotes(std::vector<NotesData>&, bool calling_from_main); // Displays in console the stored notes
void EditNote(std::vector<NotesData>&); // Lets the user edit the content of a note or even the title
void EditTitle(std::string&, std::string&); // Replaces the title of a note with a new one
void EditContent(std::string&, const std::string); // Replaces the content of a note with a new one
void PrintNotesInTxt(const std::vector<NotesData>&); // Replaces the existing txt file with a new one with updated content and titles
std::vector<NotesData>::iterator SearchForNoteByTitle(const std::string, std::vector<NotesData>&); // Returns an iterator in the position of the named note
EditOptions ScrollEditMenu(const std::string); // Infinote loop to keep asking for an arrow or enter in the edit menu
void PrintEditMenuHighlighted(const EditOptions, const std::string); // Prints the edit menu with the specified option highlighted

