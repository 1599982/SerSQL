#include "sersql/sersql.hpp"
#include "mysql-connector-c++-9.3.0-linux-glibc2.28-x86-64bit/include/jdbc/cppconn/connection.h"
#include "mysql-connector-c++-9.3.0-linux-glibc2.28-x86-64bit/include/jdbc/cppconn/prepared_statement.h"
#include "mysql-connector-c++-9.3.0-linux-glibc2.28-x86-64bit/include/jdbc/cppconn/resultset.h"
#include "mysql-connector-c++-9.3.0-linux-glibc2.28-x86-64bit/include/jdbc/cppconn/statement.h"
#include <exception>
#include <nlohmann/json.hpp>
#include <httplib.h>
#include <iostream>
#include <string>

using json = nlohmann::json;

/*
* CRUD
*/
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
		std::cout << "SerSQL: ..." << std::endl;
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

	httplib::Server server;

	// Create
	server.Post("/create", [&sersql] (const httplib::Request &request, httplib::Response &response) {
		try {
			json entry = json::parse(request.body);
			sql::PreparedStatement *stmt = sersql -> connx() -> prepareStatement("INSERT INTO person (name, lastname) VALUES (?, ?)");
			stmt -> setString(1, entry["name"].get<std::string>());
			stmt -> setString(2, entry["lastname"].get<std::string>());
			stmt -> executeUpdate();

			response.set_content("{\"status\": \"created\"}", "application/json");
		} catch (std::exception &err) {
			response.status = 500;
			response.set_content("{\"status\": \"" + std::string(err.what()) + "\"}", "application/json");
		}
	});

	// Read
	server.Get("/read", [&sersql] (const httplib::Request &request, httplib::Response &response) {
		try {
			json result = json::array();
			sql::Statement *stmt = sersql -> connx() -> createStatement();
			sql::ResultSet *resp = stmt -> executeQuery("SELECT * FROM person");

			while (resp -> next()) {
				result.push_back({
					{"id", resp -> getInt("id")},
					{"name", resp -> getString("name")},
					{"lastname", resp -> getString("lastname")}
				});
			}

			response.set_content(result.dump(), "application/json");
		} catch (std::exception &err) {
			response.status = 500;
			response.set_content("{\"status\": \"" + std::string(err.what()) + "\"}", "application/json");
		}
	});

	server.Post("/update", [] (const httplib::Request &request, httplib::Response &response) {
		response.set_content("Received: " + request.body, "text/plain");
	});

	server.Post("/insert", [] (const httplib::Request &request, httplib::Response &response) {
		json entry = json::parse(request.body);

		json result = {
			{"message", entry["name"]}
		};

		response.set_content(result.dump(), "application/json");
	});

	std::cout << "[LOG] Server listening on: 0.0.0.0:8080" << std::endl;
	server.listen("0.0.0.0", 8080);

	return 0;
}
