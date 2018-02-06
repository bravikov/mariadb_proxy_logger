#ifndef PARSER_H
#define PARSER_H

#include "packet_header.h"

#include <vector>
#include <string>

class Parser
{
public:
    bool queryReady() const;
    std::string getQuery();
    bool addData(const char* data, const size_t length);

private:
    std::vector<char> m_data;
    std::string m_query;
    PacketHeader m_header;

    bool parse();
    void reset();
};

#endif // PARSER_H
