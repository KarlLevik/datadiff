#ifndef MARIADBSOURCE
#define MARIADBSOURCE

#include <iostream>
#include "DBSource.hpp"
#include <mariadb/conncpp.hpp>

namespace N {
  
  class MariaDBSource: public DBSource {

    protected:
      sql::Connection* cnx;
    
    public:
      MariaDBSource(std::string user, std::string password, std::string database, std::string host, std::string port);
      ~MariaDBSource();
      int retrieve(std::string query, std::string param);
  };

}
#endif