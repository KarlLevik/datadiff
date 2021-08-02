# Install

## MariaDB dependencies

For installing MariaDB dependencies, please see this page:
https://mariadb.com/docs/clients/mariadb-connectors/connector-cpp/install/

At the time of writing, installing MariaDB Connector/C can be done through 
package managers such as yum and apt, whereas MariaDB Connector/C++ requires 
manually downloading and extracting a tarball from MariaDB Corporation 
(mariadb.com) and then installing its folders and files according to 
instructions on the above page.


## Oracle dependencies

Download and install the oracle-instantclient-basic and 
oracle-instantclient-devel packages. The location of these within the Oracle 
website has changed over time, but I found them most recently at: 

https://www.oracle.com/database/technologies/instant-client/linux-x86-64-downloads.html


## Compilation and linking

Once the dependencies have been installed, you can move on to building the code. 

If you are using Fedora, you can build an RPM if you install certain additional
dependencies - see description within the 'build.sh' file. Then simply run:

    build.sh

Otherwise, you can just build an executable with:

    cd src
    make
