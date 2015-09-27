#include <iostream>

using namespace std;

#include "IO.hpp"

int main() {
    cout << "Ballistic Engine Level Editor" << endl;
    IO *io = IO::getInstance();
    io->init(io);
    io->eventLoop();
}
