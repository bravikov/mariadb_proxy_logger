#include "proxy.h"
#include <iostream>

Proxy::Proxy(tcp::socket socket, boost::asio::io_service &ioService)
:
    m_serverSocket(std::move(socket)),
    m_clientSocket(ioService),
    m_clientEndpoint(boost::asio::ip::address::from_string("127.0.0.1"), 3306)
{
}

void Proxy::start()
{
    m_clientSocket.async_connect(
        m_clientEndpoint,
        [this](const boost::system::error_code& error) {
            std::cout << "m_clientSocket.async_connect" << std::endl;
            if (error) {
                std::cerr << error << " " << error.message() << std::endl;
                return;
            }
            readClient();
        }
    );

    readServer();
}

void Proxy::writeClient(const std::size_t &length)
{
    m_clientSocket.async_write_some(
        boost::asio::buffer(m_serverData, length),
        [this](boost::system::error_code error, std::size_t /*length*/)
        {
            if (error) {
                std::cerr << error << " " << error.message() << std::endl;
                return;
            }

            readServer();
        }
    );
}

void Proxy::readServer()
{
    m_serverSocket.async_read_some(
        boost::asio::buffer(m_serverData, max_length),
        [this](boost::system::error_code error, std::size_t length) {
            std::cout << "m_serverSocket.async_read_some" << std::endl;

            if (error) {
                std::cerr << error << " " << error.message() << std::endl;
                return;
            }

            for (decltype(length) i = 0; i < length; i++) {
                std::cout << m_serverData[i];
            }

            std::cout << std::endl;

            writeClient(length);
        }
    );
}

void Proxy::writeServer(const std::size_t &length)
{
    m_serverSocket.async_write_some(
        boost::asio::buffer(m_clientData, length),
        [this](boost::system::error_code error, std::size_t /*length*/) {
            if (error) {
                std::cerr << error << " " << error.message() << std::endl;
                return;
            }

            readClient();
        }
    );
}

void Proxy::readClient()
{
    m_clientSocket.async_read_some(
        boost::asio::buffer(m_clientData, max_length),
        [this](boost::system::error_code error, std::size_t length) {
            std::cout << "m_clientSocket.async_read_some" << std::endl;

            if (error) {
                std::cerr << error << " " << error.message() << std::endl;
                return;
            }

            for (decltype(length) i = 0; i < length; i++) {
                std::cout << m_clientData[i];
            }

            std::cout << std::endl;

            writeServer(length);
        }
    );
}
