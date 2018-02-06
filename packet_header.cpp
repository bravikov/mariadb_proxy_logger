#include "packet_header.h"

PacketHeader::PacketHeader(std::vector<char> &data)
{
    if (data.size() < length) {
        return;
    }
    m_bodyLength =
            (uint8_t)data[0]
            + ((uint8_t)data[1] << 8)
            + ((uint8_t)data[2] << 16)
            ;
    m_sequenceNumber = data[3];
    m_isValid = true;
}

bool PacketHeader::isValid() const
{
    return m_isValid;
}

size_t PacketHeader::bodyLength() const
{
    return m_bodyLength;
}

uint8_t PacketHeader::sequenceNumber() const
{
    return m_sequenceNumber;
}

