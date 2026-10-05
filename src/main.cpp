#include "Server.h"
#include <cstdlib>
#include <iostream>

int main() {
    try {
        unsigned short port = 8080;
        if (const char* p = std::getenv("VIDMA_PORT")) {
            int v = std::atoi(p);
            if (v > 0 && v < 65536) port = (unsigned short)v;
        }

        std::cout << "=== Vidma VideoCall Server ===" << std::endl;
        std::cout << "Listening on port " << port << "..." << std::endl;

        VideoCallServer server(port);
        server.start();
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
