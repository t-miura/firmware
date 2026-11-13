#ifndef ETH_ASYNC_UDP_H
#define ETH_ASYNC_UDP_H

#include "configuration.h"

#if HAS_ETHERNET && !defined(ARCH_ESP32)

#include "concurrency/OSThread.h"
#include <IPAddress.h>
#include <Print.h>
#ifdef USE_ARDUINO_ETHERNET
#include <Ethernet.h>
#else
#include <RAK13800_W5100S.h>
#endif
#include <cstdint>
#include <functional>

class EthAsyncUDPPacket;

class EthAsyncUDP : public Print, private concurrency::OSThread
{
  public:
    EthAsyncUDP();
    explicit operator bool() const { return localPort != 0; }

    bool listenMulticast(IPAddress multicastIP, uint16_t port, uint8_t ttl = 64);
    bool writeTo(const uint8_t *data, size_t len, IPAddress ip, uint16_t port);
    void close();

    size_t write(uint8_t b) override;
    size_t write(const uint8_t *data, size_t len) override;
    void onPacket(const std::function<void(EthAsyncUDPPacket)> &callback);

  private:
    EthernetUDP udp;
    uint16_t localPort;
    volatile bool isSending = false;
    std::function<void(EthAsyncUDPPacket)> _onPacket;
    virtual int32_t runOnce() override;
};

class EthAsyncUDPPacket
{
  public:
    explicit EthAsyncUDPPacket(EthernetUDP &source);

    IPAddress remoteIP();
    uint16_t length();
    const uint8_t *data();

  private:
    EthernetUDP &_udp;
    IPAddress _remoteIP;
    uint16_t _remotePort;
    size_t _readLength = 0;

    static constexpr size_t BUF_SIZE = 512;
    uint8_t _buffer[BUF_SIZE];
};

using AsyncUDP = EthAsyncUDP;
using AsyncUDPPacket = EthAsyncUDPPacket;

inline bool isMulticast(const IPAddress &ip)
{
    return (ip[0] & 0xF0) == 0xE0;
}

#endif // HAS_ETHERNET && !defined(ARCH_ESP32)

#endif // ETH_ASYNC_UDP_H
