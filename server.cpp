#include "server.h"
#include "proxy.h"
#include <iostream>

Server::Server(
    boost::asio::io_service &ioService,
    const tcp::endpoint &endpoint
):
    m_ioService(ioService),
    m_acceptor(ioService, endpoint)
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
            std::cout << "m_acceptor.async_accept" << std::endl;

            if (error) {
                std::cerr << error << " " << error.message() << std::endl;
                delete socket;
                return;
            }

            auto proxy = new Proxy(socket, m_ioService);
            proxy->start();

            accept();
        }
    );
}
