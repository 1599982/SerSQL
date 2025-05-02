#include "mysql-connector-c++-9.3.0-linux-glibc2.28-x86-64bit/include/jdbc/cppconn/connection.h"
#include "mysql-connector-c++-9.3.0-linux-glibc2.28-x86-64bit/include/jdbc/cppconn/exception.h"
#include "mysql-connector-c++-9.3.0-linux-glibc2.28-x86-64bit/include/jdbc/cppconn/prepared_statement.h"
#include "mysql-connector-c++-9.3.0-linux-glibc2.28-x86-64bit/include/jdbc/cppconn/statement.h"
#include "mysql-connector-c++-9.3.0-linux-glibc2.28-x86-64bit/include/jdbc/mysql_driver.h"
#include <iostream>
#include <string>

std::string check_password(const std::string &password) {
	if (password.length() == 1 && password[0] == '$') {
		return "";
	}

	return password;
}

/*
* CRUD
*/
// Create:
void create(sql::Connection *connx, const std::string &table) {
	sql::PreparedStatement *pstmt = connx -> prepareStatement("INSERT INTO " + table + " (name, lastname) VALUES (?, ?)");
	pstmt -> setString(1, "Yorch");
	pstmt -> setString(2, "Cachaestela");
	pstmt -> executeUpdate();
}
// Read:
void read(sql::Connection *connx, const std::string &table) {
	sql::Statement *stmt = connx -> createStatement();
	sql::ResultSet *resp = stmt -> executeQuery("SELECT * FROM " + table);

	while (resp -> next()) {
 		std::cout << resp -> getInt("id") << std::endl;
		std::cout << resp -> getString("name") << std::endl;
		std::cout << resp -> getString("lastname") << std::endl;
	}
}
// Update:
void update(sql::Connection *connx, const std::string &table) {
	sql::PreparedStatement *pstmt = connx -> prepareStatement("UPDATE " + table + " SET name = ?, lastname = ? WHERE id = ?");
	pstmt -> setString(1, "Turbo");
	pstmt -> setString(2, "Niel");
	pstmt -> setInt(3, 3);
	pstmt -> executeUpdate();
}
// Delete
void _delete(sql::Connection *connx, const std::string &table) {
	sql::PreparedStatement *pstmt = connx -> prepareStatement("DELETE FROM " + table + " WHERE id = ?");
	pstmt -> setInt(1, 3);
	pstmt -> executeUpdate();
}

int main(int argc, char **argv) {
	if (argc < 5) {
		std::cout << "server: ..." << std::endl;
		std::cout << "    <hostname>    ..." << std::endl;
		std::cout << "    <username>    ..." << std::endl;
		std::cout << "    <password>    use $ for no password" << std::endl;
		std::cout << "    <database>    ..." << std::endl;
		return 0;
	}

	const std::string hostname = argv[1];
	const std::string username = argv[2];
	const std::string password = argv[3];
	const std::string database = argv[4];

	sql::Connection *connx;

	try {
		sql::Driver *driver = sql::mysql::get_driver_instance();

		std::cout << "[WRN] Establishing connection: " << hostname << std::endl;
		connx = driver -> connect(hostname, username, check_password(password));
		std::cout << "[LOG] Established connection: " << hostname << std::endl;

		connx -> setSchema(database);
	} catch (sql::SQLException &err) {
		std::cerr << "[ERR] " << err.what() << std::endl;
	}

	// create(connx, "person");
	// read(connx, "person");
	// update(connx, "person");
	_delete(connx, "person");

	return 0;
}
