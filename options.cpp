#include "options.h"
#include <cstdlib>


Options::Options(const int &argc, char* const argv[])
{
    if (argc != Options::count + 1) {
        throw InvalidOptions("Ошибка: неверное количество аргументов.");
    }

    uint64_t value = 0;

    value = std::strtoul(argv[1], nullptr, 10);

    if (value <= 0 || value > UINT16_MAX) {
        throw InvalidOptions{
            "Ошибка: недопустимый порт для подключения клиента."
        };
        return;
    }

    m_port = value;

    m_databaseAddress = argv[2];

    value = std::strtoul(argv[3], nullptr, 10);

    if (value <= 0 || value > UINT16_MAX) {
        throw InvalidOptions{
            "Ошибка: недопустимый порт СУБД."
        };
        return;
    }

    m_databasePort = value;
}

uint16_t Options::port() const
{
    return m_port;
}

const std::string& Options::databaseAddress() const
{
    return m_databaseAddress;
}

uint16_t Options::databasePort() const
{
    return m_databasePort;
}
