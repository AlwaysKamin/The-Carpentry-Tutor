//
// Created by Kamin Fay on 2/20/18.
//

#include <iostream>
#include "window.h"

int main(int argc, char *argv[]) {

    window testWindow("Test Window");

    testWindow.render();

    std::cout << "Main function" << std::endl;

    return EXIT_SUCCESS;
}