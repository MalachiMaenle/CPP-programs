#ifndef utilf_H
#define utilf_H

#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <unistd.h>

#if defined (__WIN32__)
  #include <windows.h>
#else
    #include <termios.h>
    class keyInput {
    public:
        struct termios oldSettings, newSettings;
        char key;
        void input();
        void startInput();
        void stopInput();
        keyInput();
    };

    keyInput::keyInput() {
    tcgetattr( fileno( stdin ), &oldSettings );
    newSettings = oldSettings;
    newSettings.c_lflag &= (~ICANON & ~ECHO);
    }

    void keyInput::input() {
    cout.flush();
    read( fileno( stdin ), &key, 1 );
    cout.flush();
    }

    void keyInput::startInput() {
    tcsetattr( fileno( stdin ), TCSANOW, &newSettings );
    }

    void keyInput::stopInput() {
    tcsetattr( fileno( stdin ), TCSANOW, &oldSettings );
    }

    keyInput getKey;
#endif

using namespace std;

#define clearf "\033[0m"
#define disable "\x1B"

#define cursor_up "\x1B[A"
#define cursor_down "\x1B[B"
#define cursor_right "\x1B[C"
#define cursor_left "\x1B[D"
#define backspace "\x1B[D \x1B[D"

#define black "\x1B[30m"
#define red "\x1B[31m"
#define green "\x1B[32m"
#define yellow "\x1B[33m"
#define blue "\x1B[34m"
#define magenta "\x1B[35m"
#define cyan "\x1B[36m"
#define white "\x1B[37m"
#define bright_black "\x1B[90m"
#define bright_red "\x1B[91m"
#define bright_green "\x1B[92m"
#define bright_yellow "\x1B[93m"
#define bright_blue "\x1B[94m"
#define bright_magenta "\x1B[95m"
#define bright_cyan "\x1B[96m"
#define bright_white "\x1B[97m"

#define bg_black "\x1B[40m"
#define bg_red "\x1B[41m"
#define bg_green "\x1B[42m"
#define bg_yellow "\x1B[43m"
#define bg_blue "\x1B[44m"
#define bg_magenta "\x1B[45m"
#define bg_cyan "\x1B[46m"
#define bg_white "\x1B[47m"
#define bg_bright_black "\x1B[100m"
#define bg_bright_red "\x1B[101m"
#define bg_bright_green "\x1B[102m"
#define bg_bright_yellow "\x1B[103m"
#define bg_bright_blue "\x1B[104m"
#define bg_bright_magenta "\x1B[105m"
#define bg_bright_cyan "\x1B[106m"
#define bg_bright_white "\x1B[107m"

#define bold "\x1B[1m"
#define subtitle "\x1B[2m"
#define italic "\x1B[3m"
#define underline "\x1B[4m"
#define contrast "\x1B[7m"
#define invisible "\x1B[8m"

void wait(int num) {
  cout.flush();
  this_thread::sleep_for(chrono::milliseconds(num));
  cout.flush();
}

void blip() { //system("tput bel");
  cout << "\7";
}

void blip(int delay) { //system("tput bel");
  wait(delay);
  cout << "\7";
}

#endif