#include "server.h"
#include "options.h"

#include <cstdlib>
#include <iostream>
#include <list>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

const char* helpMessage()
{
    return
        "Вызов:\n"
        "\n"
        "    mariadb_proxy_logger <Порт> <Адрес СУБД> <Порт СУБД>\n"
        "\n"
        "Где:\n"
        "    <Порт>       Порт для подключения клиента. От 1 до 65535. \n"
        "    <Адрес СУБД> IPv4-адрес СУБД.\n"
        "    <Порт СУБД>  Порт СУБД. От 1 до 65535.\n"
        "\n"
        "Пример:\n"
        "\n"
        "    mariadb_proxy_logger 1234 127.0.0.1 3306\n"
    ;
}

int main(int argc, char* argv[])
{
    try {
        Options options{argc, argv};

        boost::asio::io_service ioService;
        tcp::endpoint endpoint(tcp::v4(), options.port());

        Server server{ioService, endpoint};

        ioService.run();
    }
    catch (InvalidOptions& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << helpMessage();
        return EXIT_FAILURE;
    }
    catch (std::exception& e) {
        std::cerr << "Исключение: " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
