#include "mysql-connector-c++-9.3.0-linux-glibc2.28-x86-64bit/include/jdbc/cppconn/connection.h"
#include "mysql-connector-c++-9.3.0-linux-glibc2.28-x86-64bit/include/jdbc/cppconn/exception.h"
#include "mysql-connector-c++-9.3.0-linux-glibc2.28-x86-64bit/include/jdbc/mysql_driver.h"
#include <iostream>
#include <memory>
#include <string>

int main(int argc, char **argv) {
	if (argc < 5) {
		std::cout << "server: ..." << std::endl;
		std::cout << "    <hostname>    ..." << std::endl;
		std::cout << "    <username>    ..." << std::endl;
		std::cout << "    <password>    ..." << std::endl;
		std::cout << "    <database>    ..." << std::endl;
		return 0;
	}

	const std::string &hostname = argv[1];
	const std::string &username = argv[2];
	const std::string &password = argv[3];
	const std::string &database = argv[4];

	try {
		sql::Driver *driver = sql::mysql::get_driver_instance();
		std::unique_ptr<sql::Connection> connx(driver -> connect(hostname, username, password));

		connx -> setSchema(database);
	} catch (sql::SQLException &err) {
		std::cerr << "[ERR] " << err.what() << std::endl;
	}

	return 0;
}
