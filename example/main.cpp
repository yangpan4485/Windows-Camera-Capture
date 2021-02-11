#include <iostream>

#include "main_window.h"

int main(int argc, char** argv) {
    MainWindow main_window;
    main_window.Init();
    main_window.CreateDuiWindow();
    main_window.Show();
    return 0;
}