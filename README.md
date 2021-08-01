# DataDiff

The goal of this program is to retrieve data from two data sources, compare the
result sets, and generate SQL statements to cancel out the differences. However,
not all the features have been developed yet, and as such it is still a work in
progress.

### Requirements

* Access to a supported data source such as a MariaDB database

### Usage

Put your database connection parameters in a configuration file named 
`datadiff.cfg`. See the `datadiff.example.cfg` file for an example. Then 
execute:

    ./datadiff

While it's more practical to have the database connection parameters in a 
configuration file, you can also give the parameters on the command-line, and if
so they will override whatever values you have in the configuration file. E.g.:

    ./datadiff -t MariaDB -u user1 -p pwd1 -h localhost -P 3306 -d db1 \
      -q "SELECT empid, givenname, familyname FROM employee" \
      -t MariaDB -u user2 -p pwd2 -h localhost -P 3306 -d db2 \
      -q "SELECT empid, givenname, familyname FROM employee"

If there is only one type (-t), host (-h) or port (-P) parameter, then it will
assume those should be used for both data sources.

You can also specify a different configuration file using the -f option:

    ./datadiff -f config.cfg
