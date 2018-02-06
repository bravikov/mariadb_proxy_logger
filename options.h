#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>
#include <stdexcept>

class InvalidOptions: public std::invalid_argument
{
public:
    InvalidOptions(const char* message):
        std::invalid_argument(message)
    {}
};

class Options
{
public:
    Options(const int& argc, char* const argv[]);

    uint16_t port() const;
    const std::string& databaseAddress() const;
    uint16_t databasePort() const;

    static const int count = 3;

private:
    uint16_t m_port = 0;
    std::string m_databaseAddress;
    uint16_t m_databasePort = 0;
};

#endif // OPTIONS_H
