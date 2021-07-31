# DataDiff

Retrieves data from two data sources, compares the result sets, and generates 
SQL statements to cancel out the differences.

### Requirements

* Access to a supported data source such as a MariaDB database

### Usage

Put your database connection parameters in a configuration file named 
`datadiff.cfg`. See the `datadiff.example.cfg` file for an example. Then execute:

    ./datadiff

It's more practical to have the database connection parameters in a 
configuration file, but you can also give these on the command-line, and if so 
they will override whatever values you have in the configuration file:

    ./datadiff -u1 username1 -p1 password1 -d1 database1 -P1 port1 -h1 hostname1 \
      -u2 username2 -p2 password2 -d2 database2 -P2 port2 -h hostname2