PROGRAM = mariadb_proxy_logger
SOURCES = main.cpp server.cpp proxy.cpp
HEADERS = server.h proxy.h

$(PROGRAM): $(SOURCES) $(HEADERS)
	g++ -Wall -std=c++11 -o $(PROGRAM) $(SOURCES) -lboost_system

clean:
	rm -f $(PROGRAM)
