#include "server.h"
#include "proxy.h"
#include <iostream>

Server::Server(boost::asio::io_service &ioService, const Options &options):
    m_ioService(ioService),
    m_options(options),
    m_endpoint(tcp::v4(), m_options.port()),
    m_acceptor(ioService, m_endpoint)
{
    accept();
}

void Server::accept()
{
    // Здесь происходит утечка памяти
    tcp::socket* socket = new tcp::socket(m_ioService);

    m_acceptor.async_accept(
        *socket,
        [this, socket](boost::system::error_code error) {
            if (error) {
                std::cerr << error << " " << error.message() << std::endl;
                delete socket;
                return;
            }

            auto proxy = new Proxy(
                socket,
                m_ioService,
                m_options.databaseAddress(),
                m_options.databasePort()
            );
            proxy->start();

            accept();
        }
    );
}
