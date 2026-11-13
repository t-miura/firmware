#include "ethAsyncUDP.h"

#if HAS_ETHERNET && !defined(ARCH_ESP32)

EthAsyncUDP::EthAsyncUDP() : OSThread("AsyncUDP"), localPort(0) {}

bool EthAsyncUDP::listenMulticast(IPAddress multicastIP, uint16_t port, uint8_t ttl)
{
    (void)ttl;
    if (!isMulticast(multicastIP))
        return false;
    if (!udp.beginMulticast(multicastIP, port))
        return false;
    localPort = port;
    return true;
}

size_t EthAsyncUDP::write(uint8_t b)
{
    return udp.write(&b, 1);
}

size_t EthAsyncUDP::write(const uint8_t *data, size_t len)
{
    return udp.write(data, len);
}

void EthAsyncUDP::onPacket(const std::function<void(EthAsyncUDPPacket)> &callback)
{
    _onPacket = callback;
}

bool EthAsyncUDP::writeTo(const uint8_t *data, size_t len, IPAddress ip, uint16_t port)
{
    if (!udp.beginPacket(ip, port))
        return false;
    udp.write(data, len);
    isSending = true;
    bool ok = udp.endPacket();
    isSending = false;
    return ok;
}

void EthAsyncUDP::close()
{
    udp.stop();
    localPort = 0;
    _onPacket = nullptr;
}

// EthAsyncUDPPacket
EthAsyncUDPPacket::EthAsyncUDPPacket(EthernetUDP &source)
    : _udp(source), _remoteIP(source.remoteIP()), _remotePort(source.remotePort())
{
    if (_udp.available() > 0) {
        _readLength = _udp.read(_buffer, sizeof(_buffer));
    } else {
        _readLength = 0;
    }
}

IPAddress EthAsyncUDPPacket::remoteIP()
{
    return _remoteIP;
}

uint16_t EthAsyncUDPPacket::length()
{
    return _readLength;
}

const uint8_t *EthAsyncUDPPacket::data()
{
    return _buffer;
}

int32_t EthAsyncUDP::runOnce()
{
    if (localPort != 0 && _onPacket && !isSending && udp.parsePacket() > 0) {
        EthAsyncUDPPacket packet(udp);
        _onPacket(packet);
    }
    return 5; // check every 5ms
}

#endif // HAS_ETHERNET && !defined(ARCH_ESP32)
