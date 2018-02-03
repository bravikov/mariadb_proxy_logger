#include "server.h"
#include "proxy.h"
#include <iostream>

Server::Server(
    boost::asio::io_service &ioService,
    const tcp::endpoint &endpoint
):
    m_ioService(ioService),
    m_acceptor(ioService, endpoint),
    m_socket(ioService)
{
    accept();
}

void Server::accept()
{
    m_acceptor.async_accept(
        m_socket,
        [this](boost::system::error_code error) {
            std::cout << "m_acceptor.async_accept" << std::endl;

            if (error) {
                return;
            }

            auto proxy = new Proxy(std::move(m_socket), m_ioService);
            proxy->start();

            accept();
        }
    );
}
