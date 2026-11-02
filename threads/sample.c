// sample_multithread_c_program_linux.c
// Compile with: gcc sample_multithread_c_program_linux.c -o bounce -lncurses -lpthread

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <pthread.h>
#include <ncurses.h>

#define MAX_THREADS 32

#define getrandom(min, max) ((rand() % (((max) + 1) - (min))) + (min))

void* BounceProc(void* pMyID);
void KbdFunc(void);
void ShutDown(void);
void WriteTitle(int ThreadNum);

pthread_t threads[MAX_THREADS];
pthread_mutex_t screen_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t run_mutex = PTHREAD_MUTEX_INITIALIZER;

int ThreadNr = 0;
int keep_running = 1;
int bTrails = 0;
int console_lines = 0;
int console_cols = 0;

int main(void)
{
    // Initialize ncurses UI screen
    initscr();
    cbreak();             // Line buffering disabled, pass on everything
    noecho();             // Don't echo keypresses
    curs_set(0);          // Hide cursor
    start_color();        // Enable color mode

    // Set up 16 distinct foreground color pairs
    for (int i = 1; i <= 16; i++) {
        init_pair(i, (i % 7) + 1, COLOR_BLACK);
    }

    getmaxyx(stdscr, console_lines, console_cols);
    clear();
    refresh();

    WriteTitle(0);

    // Lock run_mutex to signal threads to keep running
    pthread_mutex_lock(&run_mutex);

    // Start keyboard handling loop
    KbdFunc();

    // Cleanup ncurses when finished
    endwin();

    pthread_mutex_destroy(&screen_mutex);
    pthread_mutex_destroy(&run_mutex);

    return 0;
}

void ShutDown(void)
{
    // Signal threads to stop running
    keep_running = 0;
    pthread_mutex_unlock(&run_mutex);

    // Join/Wait for all active worker threads
    while (ThreadNr > 0) {
        pthread_join(threads[--ThreadNr], NULL);
    }

    pthread_mutex_lock(&screen_mutex);
    clear();
    refresh();
    pthread_mutex_unlock(&screen_mutex);
}

void KbdFunc(void)
{
    int KeyInfo;

    do {
        KeyInfo = getch();
        if (tolower(KeyInfo) == 'a' && ThreadNr < MAX_THREADS) {
            int thread_id = ThreadNr + 1;
            if (pthread_create(&threads[ThreadNr], NULL, BounceProc, (void*)(intptr_t)thread_id) == 0) {
                ThreadNr++;
                WriteTitle(ThreadNr);
            }
        }

        if (tolower(KeyInfo) == 't') {
            bTrails = !bTrails;
        }

    } while (tolower(KeyInfo) != 'q');

    ShutDown();
}

void* BounceProc(void* pMyID)
{
    int MyID = (int)(intptr_t)pMyID;
    char MyCell;
    int MyColorPair = (MyID % 16) + 1;
    int x, y, delta_x, delta_y;
    int old_x = 0, old_y = 0;

    srand(MyID * 3);

    x = getrandom(0, console_cols - 1);
    y = getrandom(1, console_lines - 1); // Row 0 is reserved for title
    delta_x = getrandom(-3, 3);
    delta_y = getrandom(-3, 3);
    if (delta_x == 0) delta_x = 1;
    if (delta_y == 0) delta_y = 1;

    if (MyID > 16)
        MyCell = (char)(0x60 + MyID - 16); // Lowercase
    else
        MyCell = (char)(0x40 + MyID);      // Uppercase

    while (keep_running) {
        pthread_mutex_lock(&screen_mutex);

        if (!bTrails) {
            // Erase previous position if it was occupied by this character
            char ch_at_old = mvinch(old_y, old_x) & A_CHARTEXT;
            if (ch_at_old == MyCell) {
                mvaddch(old_y, old_x, ' ');
            }
        }

        // Draw new character with color attribute
        attron(COLOR_PAIR(MyColorPair));
        mvaddch(y, x, MyCell);
        attroff(COLOR_PAIR(MyColorPair));

        refresh();
        pthread_mutex_unlock(&screen_mutex);

        old_x = x;
        old_y = y;
        x += delta_x;
        y += delta_y;

        // Bounce at boundaries
        if (x < 0 || x >= console_cols) {
            delta_x = -delta_x;
            x += delta_x;
            beep(); // Terminal bell replacement for Beep()
        }
        if (y < 1 || y >= console_lines) {
            delta_y = -delta_y;
            y += delta_y;
            beep();
        }

        // Sleep for 75 milliseconds (replacing WaitForSingleObject timeout)
        usleep(75000);
    }

    return NULL;
}

void WriteTitle(int ThreadNum)
{
    pthread_mutex_lock(&screen_mutex);
    mvprintw(0, 0, "Threads running: %02d. Press 'A' to start thread, 'T' to toggle trails, 'Q' to quit.", ThreadNum);
    clrtoeol(); // Clear to end of line
    refresh();
    pthread_mutex_unlock(&screen_mutex);
}