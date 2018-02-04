#ifndef SERVER_H
#define SERVER_H

#include <boost/asio.hpp>
using boost::asio::ip::tcp;

class Server
{
public:
    Server(
        boost::asio::io_service& io_service,
        const tcp::endpoint& endpoint
    );

private:
    void accept();

    boost::asio::io_service& m_ioService;
    tcp::acceptor m_acceptor;
};

#endif // SERVER_H
