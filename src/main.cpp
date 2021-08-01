/*
  Program to compare SQL query result-sets row by row

  Connection configuration is read from the .cfg file.

  Karl Levik - 2021-05-16

*/

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <unistd.h>
#include <getopt.h>
#include "DBSource.hpp"
#include "MariaDBSource.hpp"

using std::map, std::cout, std::cerr, std::endl, std::string, std::ifstream, std::pair, std::getline;

string trim(string str) {
  const char* whitespaces = " \t\n\r\f\v";
  str.erase(str.find_last_not_of(whitespaces) + 1);
  str.erase(0,str.find_first_not_of(whitespaces));
  return str;
}

map<string,string>* read_config(string fname) {
    map<string,string> *config = nullptr;
    ifstream cFile (fname);
    if (cFile.is_open())
    {
        string line;
        string lastkey = "";
        config = new map<string,string>;
        string whitespaces = " \t\n\r\f\v";
        while(getline(cFile, line)) {
            if (whitespaces.find(line[0]) == std::string::npos) {
              line = trim(line);
              //line.erase(std::remove_if(line.begin(), line.end(), isspace),
              //                     line.end());
              if( line.empty() || line[0] == '#' || line[0] == ';'
                || (line.length() >= 2 && line[0] == '/' && line[1] == '/'))
              {
                  continue;
              }
              int delimiterPos = line.find("=");
              string key = line.substr(0, delimiterPos);
              string value = line.substr(delimiterPos + 1);
              config->insert ( pair<string,string>(key,value) );
              lastkey = key;
            }
            // line begins with whitespace, so add line to end of last line's
            else if (!lastkey.empty()) {
              (*config)[lastkey] += " " + trim(line);
            }
        }
    }
    return config;
}

static void show_usage(string name)
{
    cerr << "Usage: " << name << " <option(s)>"
              << "Options:\n"
              << "\t-?          Show this help message\n"
              << "\t-t TYPE     Specify DS type (MariaDB, OracleDB, csvfile)\n"
              << "\t-u USER     Specify DS user (ignored for csvfile)\n"
              << "\t-d DATABASE Specify DS name (ignored for csvfile)\n"
              << "\t-h HOST     Specify DS host (ignored for csvfile)\n"
              << "\t-P PORT     Specify ds port (ignored for csvfile)\n"
              << "\t-q QUERY    Specify DS query (ignored for csvfile)\n"
              << "\t-f FILE     Specify configuration file\n"
              << "\n"
              << "Data source (DS) parameters can be given twice. The first is used for DS1, the second for DS2.\n"
              << "By default parameters are read from the " << name << ".cfg file, but these can be overridden by command-line options.\n"
              << "\n"
              << "Valid parameter names inside the configuration file are:\n"
              << "type1, user1, password1, database1, host1, port1, query1, type2, user2, password2, database2, host2, port2, query2\n"
              << "\n"
              << "Example command-lines:"
              << name << "-f config.cfg -t OracleDB -t MariaDB\n"
              << name << "-f config.cfg -t csvfile -t MariaDB\n"
              << endl;
}


int main(int argc, char* argv[])
{
  bool debug = false;

  string t1, u1, p1, d1, h1, P1, q1;
  string t2, u2, p2, d2, h2, P2, q2;
  int opt;
  const char *optstr = "f:t:u:p:d:h:P:q:D?";
  string cfile = argv[0] + string(".cfg");
  string optcfile = "";

  // Read command-line options into t1, t2, u1, u2, p1, p2, ...
  while ( (opt = getopt(argc, argv, optstr)) != -1) {
      switch (opt) {
      case 'f':
          cfile = optarg;
          optcfile = optarg;
          break;
      case 't':
          if (t1.empty())
            t1 = optarg;
          else if (t2.empty())
            t2 = optarg;
          break;
      case 'u':
          if (u1.empty())
            u1 = optarg;
          else if (u2.empty())
            u2 = optarg;
          break;
      case 'p':
          if (p1.empty())
            p1 = optarg;
          else if (p2.empty())
            p2 = optarg;
          break;
      case 'd':
          if (d1.empty())
            d1 = optarg;
          else if (d2.empty())
            d2 = optarg;
          break;
      case 'h':
          if (h1.empty())
            h1 = optarg;
          else if (h2.empty())
            h2 = optarg;
          break;
      case 'P':
          if (P1.empty())
            P1 = optarg;
          else if (P2.empty())
            P2 = optarg;
          break;
      case 'q':
          if (q1.empty())
            q1 = optarg;
          else if (q2.empty())
            q2 = optarg;
          break;

      case 'D':
          debug = true;
          break;

      default: /* '?' */
          show_usage(argv[0]);
          exit(EXIT_FAILURE);
      }
  }

  // Try to read config file
  map<string,string> *config = read_config(cfile);

  // Exit with error if config file not readable except if all params are given
  // as command-line options
  if (
      (config == nullptr && !optcfile.empty()) || 
      (config == nullptr && (
          t1.empty() || t2.empty() || u1.empty() || u2.empty() || p1.empty() || 
          p2.empty() || d1.empty() || d2.empty() || h1.empty() || h2.empty() || 
          P1.empty() || P2.empty() || q1.empty() || q2.empty()
        )
      )
    ) {
    cerr << "Couldn't open config file " +cfile+ " for reading.\n";
    exit(EXIT_FAILURE);
  }

  string type1, user1, password1, database1, host1, port1, query1;
  string type2, user2, password2, database2, host2, port2, query2;

  // Read params from config file into the above param strings
  if (config != nullptr) {
    map<string,string>::iterator it;
    for (it=config->begin(); it!=config->end(); ++it) {
      string key = it->first;
      if (key.compare("type1") == 0)
          type1 = it->second;
      else if (key.compare("user1") == 0)
          user1 = it->second;
      else if (key.compare("password1") == 0)
          password1 = it->second;
      else if (key.compare("database1") == 0)
          database1 = it->second;
      else if (key.compare("host1") == 0)
          host1 = it->second;
      else if (key.compare("port1") == 0)
          port1 = it->second;
      else if (key.compare("query1") == 0)
          query1 = it->second;
      if (key.compare("type2") == 0)
          type2 = it->second;
      else if (key.compare("user2") == 0)
          user2 = it->second;
      else if (key.compare("password2") == 0)
          password2 = it->second;
      else if (key.compare("database2") == 0)
          database2 = it->second;
      else if (key.compare("host2") == 0)
          host2 = it->second;
      else if (key.compare("port2") == 0)
          port2 = it->second;
      else if (key.compare("query2") == 0)
          query2 = it->second;
    }
  }

  // Override param strings with any command-line params
  if (!t1.empty())
    type1 = t1;
  if (!u1.empty())
    user1 = u1;
  if (!p1.empty())
    password1 = p1;
  if (!d1.empty())
    database1 = d1;
  if (!h1.empty())
    host1 = h1;
  if (!P1.empty())
    port1 = P1;
  if (!q1.empty())
    query1 = q1;

  if (!t2.empty())
    type2 = t2;
  if (!u2.empty())
    user2 = u2;
  if (!p2.empty())
    password2 = p2;
  if (!d2.empty())
    database2 = d2;
  if (!h2.empty())
    host2 = h2;
  if (!P2.empty())
    port2 = P2;
  if (!q2.empty())
    query2 = q2;

  // If the -t (type) or -h (host) or -P (port) parameters for data source 2
  // are missing, use the ones given for data source 1
  if (type2.empty())
    type2 = type1;
  if (host2.empty())
    host2 = host1;
  if (port2.empty())
    port2 = port1;

  using namespace N;

  DBSource *src = nullptr;
  
  if (type1.compare("MariaDB") == 0) {
    src = new MariaDBSource(user1, password1, database1, host1, port1);
  }
  else if (type1.compare("OracleDB") == 0) {
    cerr << "OracleDB not implemented" << endl;
    exit(EXIT_FAILURE);  
  }
  else {
    cerr << "Database " << type1 << " not recognised" << endl;
    exit(EXIT_FAILURE);
  }
  if (src != nullptr) {
    src->retrieve(query1, "");
    delete src;
  }
  return 0;
}
