#ifndef PACKETHEADER_H
#define PACKETHEADER_H

#include <cstddef>
#include <cstdint>
#include <vector>

class PacketHeader
{
public:
    PacketHeader() = default;

    PacketHeader(std::vector<char>& data);

    bool isValid() const;
    size_t bodyLength() const;
    uint8_t sequenceNumber() const;

    static const size_t length = 4;

private:
    size_t m_bodyLength = 0;
    uint8_t m_sequenceNumber = 0;
    bool m_isValid = false;
};

#endif // PACKETHEADER_H
