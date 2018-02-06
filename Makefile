PROGRAM = mariadb_proxy_logger
SOURCES = main.cpp server.cpp proxy.cpp packet_header.cpp parser.cpp
HEADERS = server.h proxy.h packet_header.h parser.h

$(PROGRAM): $(SOURCES) $(HEADERS)
	g++ -Wall -W -std=c++11 -o $(PROGRAM) $(SOURCES) -lboost_system

clean:
	rm -f $(PROGRAM)
