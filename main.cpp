#include "sersql/sersql.hpp"
#include "mysql-connector-c++-9.3.0-linux-glibc2.28-x86-64bit/include/jdbc/cppconn/connection.h"
#include "mysql-connector-c++-9.3.0-linux-glibc2.28-x86-64bit/include/jdbc/cppconn/prepared_statement.h"
#include "mysql-connector-c++-9.3.0-linux-glibc2.28-x86-64bit/include/jdbc/cppconn/resultset.h"
#include "mysql-connector-c++-9.3.0-linux-glibc2.28-x86-64bit/include/jdbc/cppconn/statement.h"
#include <iostream>
#include <string>

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

	SerSQL *sersql = new SerSQL(hostname, username, password, database);

	// create(sersql -> connx(), "person");
	// read(connx, "person");
	// update(connx, "person");
	// _delete(connx, "person");

	return 0;
}
