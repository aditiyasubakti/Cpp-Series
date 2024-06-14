//#include <iostream>
//#include <cstring>
//#include <cstdlib>
//#include "unistd.h"
//#include "inet.h"
//#include "socket.h"
//
//int main() {
//    char hostbuffer[256];
//    char *IPbuffer;
//    struct hostent *host_entry;
//    int hostname;
//
//    // Mendapatkan nama host
//    hostname = gethostname(hostbuffer, sizeof(hostbuffer));
//    if (hostname == -1) {
//        perror("Error in gethostname");
//        return EXIT_FAILURE;
//    }
//
//    // Mendapatkan informasi host berdasarkan nama host
//    host_entry = gethostbyname(hostbuffer);
//    if (host_entry == nullptr) {
//        perror("Error in gethostbyname");
//        return EXIT_FAILURE;
//    }
//
//    // Menampilkan alamat IP
//    IPbuffer = inet_ntoa(*((struct in_addr*)host_entry->h_addr_list[0]));
//    std::cout << "Host IP: " << IPbuffer << std::endl;
//
//    return 0;
//}

