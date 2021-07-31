#ifndef DBSOURCE
#define DBSOURCE

#include <iostream>

namespace N {
  
  class DBSource {

    protected:
      std::string user, password, database, host, port;
      std::string type;
    
    public:
      DBSource(std::string user, std::string password, std::string database, std::string host, std::string port);
      virtual ~DBSource() = 0;
      virtual int retrieve(std::string query, std::string param) = 0;
  };

}
#endif