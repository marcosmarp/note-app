#pragma once
#include <string>
#include <vector>
#include <fstream>

struct NotesData {
  std::string title;
  std::string content;
};

enum class MainMenuOptions {kNewNote, kDisplayNotes, kEditNote, kDeleteNote, kExit, kInvalid};

MainMenuOptions ScrollMainMenu(); // Infite loop that keeps asking the user for an arrok key to scroll though the menu or an enter to go the selected option
void PrintMainMenuHighlighted(MainMenuOptions); // Prints the main menu with the specified option highlighted
void PrintDotsWithDelay(int, int); // Prints the specified amount of dots with the specified delay
void ClearScreen(); // Clears the console output
void LoadSavedNotes(std::vector<NotesData>&); // Updates the vector with the saved txt notes
void NewNote(std::vector<NotesData>&); // Uploads new note to the vector
void DisplayNotes(std::vector<NotesData>&); // Displays in console the stored notes

