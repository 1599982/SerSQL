#ifndef SERSQL_HPP
#define SERSQL_HPP

#include "../mysql-connector-c++-9.3.0-linux-glibc2.28-x86-64bit/include/jdbc/cppconn/connection.h"
#include <string>

class SerSQL {
	public:
		sql::Connection *connx() {
			return connection;
		}

		SerSQL(
			const std::string &hostname,
			const std::string &username,
			const std::string &password,
			const std::string &database
		);
	private:
		sql::Connection *connection;
};

#endif
