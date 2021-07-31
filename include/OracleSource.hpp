#ifndef ORACLESOURCE
#define ORACLESOURCE

#include <iostream>
#include <mariadb/conncpp.hpp>

namespace N {
  
  class OracleSource {

  public:
    OracleSource();
    ~OracleSource();
    sql::Connection* connect(std::string user, std::string password, std::string database, std::string host, std::string port);
    sql::ResultSet* retrieve(sql::Connection* conn, std::string proposal_type);
  };

}
#endif