#ifndef NCURSES_WRAPPER_H
#define NCURSES_WRAPPER_H

// This wrapper takes care of setting up unicode support for ncurses.

// activate ncurses unicode support
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#pragma clang diagnostic ignored "-Wunused-macros"
#define _XOPEN_SOURCE_EXTENDED 1
#pragma clang diagnostic pop

#include <ncursesw/ncurses.h>

#endif /* NCURSES_WRAPPER_H */
