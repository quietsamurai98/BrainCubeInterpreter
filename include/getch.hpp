/* Multi-platform getch() */
#ifndef MULTI_PLATFORM_GETCH
#define MULTI_PLATFORM_GETCH

#ifdef _WIN32
/*
    Windows compatible getch() is just from conio.h
*/
#include <conio.h>

#endif //Windows compatible getch
#ifdef __unix

/*
    Linux compatible getch() gode written by Stenodyon. https://github.com/Stenodyon
    Reproduced with permission.
*/
#pragma once

#include <stdint.h>
#include <stdio.h>
#include <termios.h>


static struct termios old, new_termios;

char _getch(void)
{
    tcgetattr(0, &old); /* grab old terminal i/o settings */
    new_termios = old; /* make new_termios settings same as old settings */
    new_termios.c_lflag &= ~ICANON; /* disable buffered i/o */
    new_termios.c_lflag &= ~ECHO; /* set echo mode */
    tcsetattr(0, TCSANOW, &new_termios); /* use these new_termios terminal i/o settings now */
    char ch = getchar();
    tcsetattr(0, TCSANOW, &old); /* Restore old terminal i/o settings */
    return ch;
}

char getch(void)
{
    char c = _getch();
    return c == '\n' ? '\r' : c;
}
#endif // Linux compatible getch

#endif // MULTI_PLATFORM_GETCH
