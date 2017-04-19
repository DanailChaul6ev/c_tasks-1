#ifndef MENUHEADER
#define MENUHEADER

#include <stddef.h> 

typedef struct 
{
	const char* name;
	void (*action)(void*);
	void* actionData;
} MenuEntry;

typedef struct
{
	MenuEntry entries[100];
}  Menu;

// display the menu in the terminal, wait for input and execute the entry selected by the user
void executeMenu(const Menu* m);

// initialize the menu
void setNULL(int start,Menu* m);


// helper functions
// create a menuentry for showing a sub-menu and return the created entry
MenuEntry createSubMenuEntry(const char* name, const Menu* subMenu);

// create a menuentry to print the given text on the terminal
MenuEntry createPrintEntry(const char* name, const char* text);

// fill the given menu entry so when the entry is selected, then it will show the given sub-menu
void fillSubMenuEntry(MenuEntry* outEntry, const char* name, const Menu* subMenu);

// fill the given menuentry so it prints the given text when selected
void fillPrintEntry(MenuEntry* outEntry, const char* name, const char* text);

#endif
