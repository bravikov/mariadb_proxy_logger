#include "proxy.h"
#include <iostream>

Proxy::Proxy(
    tcp::socket* socket,
    boost::asio::io_service& ioService,
    const std::string& databaseAddress,
    const uint16_t& databasePort
):
    m_serverSocket(socket),
    m_clientSocket(ioService),
    m_clientEndpoint(
        boost::asio::ip::address::from_string(databaseAddress),
        databasePort
    )
{
}

void Proxy::start()
{
    m_clientSocket.async_connect(
        m_clientEndpoint,
        [this](const boost::system::error_code& error) {
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
    m_serverSocket->async_read_some(
        boost::asio::buffer(m_serverData, max_length),
        [this](boost::system::error_code error, std::size_t length) {
            if (error) {
                std::cerr << error << " " << error.message() << std::endl;
                return;
            }

            if (!m_parser.addData(m_serverData, length)) {
                return;
            }

            if (m_parser.queryReady()) {
                std::cout << m_parser.getQuery() << std::endl;
            }

            writeClient(length);
        }
    );
}

void Proxy::writeServer(const std::size_t &length)
{
    m_serverSocket->async_write_some(
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
            if (error) {
                std::cerr << error << " " << error.message() << std::endl;
                return;
            }

            writeServer(length);
        }
    );
}
