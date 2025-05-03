#include "sersql.hpp"
#include "../mysql-connector-c++-9.3.0-linux-glibc2.28-x86-64bit/include/jdbc/cppconn/driver.h"
#include "../mysql-connector-c++-9.3.0-linux-glibc2.28-x86-64bit/include/jdbc/cppconn/exception.h"
#include "../mysql-connector-c++-9.3.0-linux-glibc2.28-x86-64bit/include/jdbc/mysql_driver.h"
#include <iostream>
#include <string>

std::string check_password(const std::string &password) {
	if (password.length() == 1 && password[0] == '$') {
		return "";
	}

	return password;
}

SerSQL::SerSQL(
	const std::string &hostname,
	const std::string &username,
	const std::string &password,
	const std::string &database
) /* */ {
	try {
		sql::Driver *driver = sql::mysql::get_driver_instance();

		std::cout << "[WRN] Establishing connection: " << hostname << std::endl;
		this -> connection = driver -> connect(
			hostname,
			username,
			check_password(password)
		);
		std::cout << "[LOG] Established connection: " << hostname << std::endl;

		this -> connection -> setSchema(database);
	} catch (sql::SQLException &err) {
		std::cerr << "[ERR] " << err.what() << std::endl;
	}
}
