#include "OracleSource.hpp" 
#include <iostream> // header in standard library
#include <occi.h> 
#include <iostream> 

using namespace N;
using namespace std;


OracleSource::OracleSource() {
  Environment *env = Environment::createEnvironment();
}

OracleSource::~OracleSource() {
  Environment::terminateEnvironment(env);
}

OracleSource::Environment *env;

sql::Connection* OracleSource::connect(std::string user, std::string password, std::string database, std::string host, std::string port) {

  std::string connectString = "oracle://" +host+ ":" +port+ "/SID";
  

    
  {
     Connection *conn = env->createConnection(user, password, connectString);
     Statement *stmt = conn->createStatement("SELECT blobcol FROM mytable");
     ResultSet *rs = stmt->executeQuery();
     rs->next();
     Blob b = rs->getBlob(1);
     cout << "Length of BLOB : " << b.length();
     ...
     stmt->closeResultSet(rs);
     conn->terminateStatement(stmt);
     env->terminateConnection(conn);
  }

  
}

sql::ResultSet* DBSource::retrieve(sql::Connection* conn, std::string proposal_type) {
  // Create a new PreparedStatement
  std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT experimentTypeId, name, active FROM ExperimentType WHERE proposalType = (?)"));

  // Bind values to SQL statement
  stmnt->setString(1, proposal_type);

  // Execute query
  sql::ResultSet *res = stmnt->executeQuery();

  return res;
}