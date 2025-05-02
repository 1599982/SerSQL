CXXFLAGS = -std=c++23
SOURCES = $(wildcard *.cpp)
PROGRAM = server
MYSQL_PATH = mysql-connector-c++-9.3.0-linux-glibc2.28-x86-64bit

server:
	g++ $(CXXFLAGS) $(SOURCES) \
		-I$(MYSQL_PATH)/include/ \
		-L$(MYSQL_PATH)/lib64/ \
		-L$(MYSQL_PATH)/lib64/plugin/ \
		-lmysqlcppconn \
		-o $(PROGRAM)

clean:
	rm -f $(PROGRAM)
