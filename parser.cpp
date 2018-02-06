#include "parser.h"


bool Parser::queryReady() const
{
    return !m_query.empty();
}

std::string Parser::getQuery()
{
    const std::string query = m_query;
    m_query.clear();
    return query;
}

bool Parser::addData(const char *data, const size_t length)
{
    m_data.insert(m_data.end(), data, data + length);
    return parse();
}

bool Parser::parse()
{
    if (m_data.size() < PacketHeader::length) {
        return true;
    }

    m_header = PacketHeader{m_data};

    if (!m_header.isValid()) {
        reset();
        return false;
    }

    if (m_data.size() < PacketHeader::length + m_header.bodyLength()) {
        return true;
    }

    if (m_data.size() > PacketHeader::length + m_header.bodyLength()) {
        reset();
        return false;
    }

    if (m_header.bodyLength() == 0) {
        reset();
        return true;
    }

    static const size_t comQueryHeaderSize = 1;
    static const size_t comQueryHeaderIndex = PacketHeader::length;
    static const size_t comQueryHeaderSqlStatementIndex
            = comQueryHeaderIndex + comQueryHeaderSize;
    static const uint8_t comQueryHeader = 0x03;

    const uint8_t comQueryHeaderValue = m_data[comQueryHeaderIndex];

    if (comQueryHeaderValue != comQueryHeader) {
        reset();
        return true;
    }

    const size_t sqlStatementSize
            = m_header.bodyLength() - comQueryHeaderSize;

    reset();

    const char* sqlStatement =
            &m_data.data()[comQueryHeaderSqlStatementIndex];

    m_query = std::string{sqlStatement, sqlStatementSize};

    return true;
}

void Parser::reset()
{
    m_data.clear();
    m_query.clear();
    m_header = PacketHeader{};
}
