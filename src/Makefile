CC = clang
TARGET = ../datadiff
IDIR =../include
ORAINCDIR=/usr/include/oracle/21/client64
ORALIBDIR=/usr/lib/oracle/21/client64/lib
CFLAGS = -Wall -Wextra -Werror -std=c++17 -I$(IDIR) -I$(ORAINCDIR)
ODIR=obj
LDIR =../lib
# -L$(ORALIBDIR)
LIBS=-lmariadbcpp -lstdc++ -L$(ORALIBDIR) -locci -lclntsh

_DEPS = DBSource.hpp MariaDBSource.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o DBSource.o MariaDBSource.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: $(TARGET)

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	$(RM) -f $(TARGET) $(ODIR)/*.o *~ core $(IDIR)/*~ 

