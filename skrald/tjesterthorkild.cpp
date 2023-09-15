#include <ncurses.h>
#include <curses.h>
#include <menu.h>
#include <stdlib.h>
#include <iostream>

int main(void) 
{ 
  initscr(); 
  addstr("Goodbye, cruel C programming!"); 
  refresh(); 
  getch();

  endwin(); 
  return 0;

  // std::cout << "Hello Worwdwld!";
  // return 0; 
}