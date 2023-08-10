#ifndef GLOBALS_H
#define GLOBALS_H



// ALL THE GLOBAL DECLARATIONS

// don't use #include <QString> here, instead do this:



// that way you aren't compiling QString into every header file you put this in...
// aka faster build times.

#define MAGIC_NUM 42

 // Note the important use of extern!
extern int g_pawn_choice;

#endif // GLOBALS_H
