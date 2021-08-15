#pragma once
#include <string>
#include <vector>
#include <fstream>

struct NotesData {
  std::string title;
  std::string content;
};

enum class MainMenuOptions {kNewNote, kEditNote, kDeleteNote, kExit, kInvalid};

MainMenuOptions ScrollMainMenu(); // Infite loop that keeps asking the user for an arrok key to scroll though the menu or an enter to go the selected option
void PrintMainMenuHighlighted(MainMenuOptions); // Prints the main menu with the specified option highlighted
void ClearScreen(); // Clears the console output
void LoadSavedNotes(std::vector<NotesData>&); // Uploads in the vector with the saved notes

