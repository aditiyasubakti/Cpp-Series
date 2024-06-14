#include <windows.h>
#include <iostream>

bool IsRunAsAdmin() {
    HANDLE token;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token)) {
        return false;
    }

    TOKEN_ELEVATION elevation;
    DWORD size;
    if (GetTokenInformation(token, TokenElevation, &elevation, sizeof(elevation), &size)) {
        CloseHandle(token);
        return elevation.TokenIsElevated != 0;
    } else {
        CloseHandle(token);
        return false;
    }
}

int main() {
    // memastikan program berjalan sebagai administrator
    if (!IsRunAsAdmin()) {
        std::cerr << "program harus dijalankan sebagai administrator!" << std::endl;
        return 1;
    }

    // mendapatkan handle jendela konsol
    HWND console = GetConsoleWindow();

    // menyembunyikan jendela konsol
    ShowWindow(console, SW_HIDE);

    // mematikan masukan pengguna
    BlockInput(true);

    // menunggu selama 5 detik
    Sleep(5000);

    // mengaktifkan kembali masukan pengguna
    BlockInput(false);

    // menampilkan "hello, world!" setelah masukan diaktifkan kembali
    std::cout << "hello, world!";
}


