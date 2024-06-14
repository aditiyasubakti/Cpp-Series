#include <iostream>
#include "mysql.h"
//#include <mysql_connection.h>

int main() {
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;

    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "username", "password");

    // Pilih database yang akan digunakan
    con->setSchema("nama_database");

    // Query SQL
    sql::Statement *stmt;
    sql::ResultSet *res;

    stmt = con->createStatement();
    res = stmt->executeQuery("SELECT * FROM nama_tabel");

    // Loop untuk menampilkan hasil query
    while (res->next()) {
        std::cout << "Data: " << res->getString("nama_kolom") << std::endl;
    }

    // Tutup koneksi dan dealokasi sumber daya
    delete res;
    delete stmt;
    delete con;

    return 0;
}

