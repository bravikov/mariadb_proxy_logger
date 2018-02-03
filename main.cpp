#include "server.h"

#include <cstdlib>
#include <iostream>
#include <list>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
    try {
        if (argc < 2) {
            std::cerr << "Usage: mariadb_proxy_logger <port>\n";
            return EXIT_FAILURE;
        }

        boost::asio::io_service ioService;

        tcp::endpoint endpoint(tcp::v4(), std::atoi(argv[1]));
        Server server{ioService, endpoint};

        ioService.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return EXIT_SUCCESS;
}
