#include <iostream> // header in standard library
#include "DBSource.hpp" 

using namespace N;
using namespace std;

DBSource::DBSource(std::string user, std::string password, std::string database, std::string host, std::string port) {
  this->user = user;
  this->password = password;
  this->database = database;
  this->host = host;
  this->port = port;
}

DBSource::~DBSource() {
  return;
}
