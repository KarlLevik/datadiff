#include <iostream> // header in standard library
#include <mariadb/conncpp.hpp>
#include "MariaDBSource.hpp" 
#include "DBSource.hpp" 

using namespace N;
using namespace std;

MariaDBSource::MariaDBSource(std::string user, std::string password, std::string database, std::string host, std::string port) : DBSource(user, password, database, host, port) {
  
  // Instantiate Driver
  sql::Driver* driver = sql::mariadb::get_driver_instance();

  // Configure Connection
  sql::SQLString url("jdbc:mariadb://" + host + ":" + port + "/" + database);
  sql::Properties properties({{"user", user}, {"password", password}});

  // Establish Connection
  cnx = driver->connect(url, properties);
  type = "MariaDB";
}

MariaDBSource::~MariaDBSource() {
  return;
}

int MariaDBSource::retrieve(std::string query, std::string param) {
  // Create a new PreparedStatement
  std::unique_ptr<sql::PreparedStatement> stmnt(cnx->prepareStatement(query));
  
  sql::ResultSet *res = nullptr;
  try {
    if (!param.empty()) {
      // Bind values to SQL statement
      stmnt->setString(1, param);
    }
    // Execute query
    res = stmnt->executeQuery();
  }
  catch(sql::SQLException& e){
    std::cerr << "Error retrieving data: " << e.what() << std::endl;
  }
  
  while (res != nullptr && res->next()) {
         cout << "experimentTypeId = " << res->getInt(1);
         cout << ", name = " << res->getString(2);
         cout << ", active = " << res->getBoolean(3) << endl;
  }

  return 0;
}
