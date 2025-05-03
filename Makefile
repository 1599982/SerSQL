CXXFLAGS = -std=c++23
SOURCES = $(wildcard *.cpp) $(wildcard sersql/*.cpp)
PROGRAM = server

MYSQL_PATH = mysql-connector-c++-9.3.0-linux-glibc2.28-x86-64bit

$(PROGRAM):
	g++ $(CXXFLAGS) $(SOURCES) \
		-I$(MYSQL_PATH)/include/ \
		-I$(PROGRAM)/ \
		-L$(MYSQL_PATH)/lib64/ \
		-lmysqlcppconn \
		-o $(PROGRAM)

clean:
	rm -f $(PROGRAM)
