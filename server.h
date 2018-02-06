#ifndef SERVER_H
#define SERVER_H

#include "options.h"

#include <boost/asio.hpp>
using boost::asio::ip::tcp;

class Server
{
public:
    Server(boost::asio::io_service& io_service, const Options &options);

private:
    void accept();

    boost::asio::io_service& m_ioService;
    const Options& m_options;
    tcp::endpoint m_endpoint;
    tcp::acceptor m_acceptor;
};

#endif // SERVER_H
