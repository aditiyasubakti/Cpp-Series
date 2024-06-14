#include <iostream>
#include <cstdlib>  // Untuk menggunakan fungsi system()

int main() {
    std::string url = "https://www.youtube.com/";

    // Periksa sistem operasi (Windows atau Linux) untuk membuka tautan web
    #ifdef _WIN32
        // Sistem operasi Windows
        system(("start " + url).c_str());
    #elif __linux__
        // Sistem operasi Linux
        system(("xdg-open " + url).c_str());
    #else
        std::cerr << "Sistem operasi tidak didukung." << std::endl;
    #endif

    return 0;
}

