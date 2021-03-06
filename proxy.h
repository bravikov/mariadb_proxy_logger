#ifndef PROXY_H
#define PROXY_H

#include "parser.h"

#include <boost/asio.hpp>
using boost::asio::ip::tcp;

class Proxy
{
public:
    Proxy(
        tcp::socket* socket,
        boost::asio::io_service& ioService,
        const std::string& databaseAddress,
        const uint16_t& databasePort
    );

    void start();

private:
    void readServer();
    void readClient();
    void writeServer(const std::size_t& length);
    void writeClient(const std::size_t& length);

    tcp::socket* m_serverSocket;
    tcp::socket m_clientSocket;
    tcp::endpoint m_clientEndpoint;

    Parser m_parser;

    enum { max_length = 1024 };
    char m_serverData[max_length];
    char m_clientData[max_length];
};

#endif // PROXY_H
