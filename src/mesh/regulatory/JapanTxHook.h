#pragma once

#include "MeshRadio.h"
#include "MeshTypes.h"
#include "RadioTxHook.h"
#include "configuration.h"

class RadioInterface;

/// RadioTxHook enforcing ARIB STD-T108 carrier sensing and inter-transmission pause for Japan.
class JapanTxHook : public RadioTxHook
{
  public:
    static constexpr int16_t CARRIER_SENSE_THRESHOLD_DBM = -80;
    static constexpr uint32_t CARRIER_SENSE_TIME_MS = 5;
    static constexpr uint32_t INTER_TX_PAUSE_MS = 50;
    static constexpr uint32_t MAX_TX_DURATION_MS = 4000;
    static constexpr uint32_t BACKOFF_BASE_MS = 250;
    static constexpr uint32_t BACKOFF_MAX_MS = 4000;
    // Upper bound accommodates SX126x and SX127x maximum absolute RF input (10 dBm)
    static constexpr int16_t RSSI_VALID_MAX = 10;
    // Lower bound accommodates SX126x (-141 dBm), SX127x (-164 dBm HF offset), and LR11x0, above SPI errors (< -500).
    static constexpr int16_t RSSI_VALID_MIN = -192;
    static constexpr int16_t RSSI_INVALID_DRIVER_ERROR = -706;

    JapanTxHook();
    virtual ~JapanTxHook();

    PreTxAction beforeTransmit(RadioInterface *iface, meshtastic_MeshPacket *p) override;
    void postTransmit(RadioInterface *iface, const meshtastic_MeshPacket *p) override;
    void packetReleased(RadioInterface *iface, const meshtastic_MeshPacket *p) override;

    static uint32_t getTxPauseDurationMs();
    static uint32_t getTxPauseDurationMs(meshtastic_Config_LoRaConfig_RegionCode region);
    static uint32_t getMaxTxDurationMs();
    static uint32_t getMaxTxDurationMs(meshtastic_Config_LoRaConfig_RegionCode region);
    static bool isJapanRegion();
    static uint32_t computeBackoffMs(uint32_t count);

    // Valid RSSI must be within possible range.
    // FIXME: Treat "invalid RSSI" 0 dBm as valid here, backoff will be applied as it is above the carrier sense threshold anyways
    static bool isValidRssi(int16_t rssi) { return rssi <= RSSI_VALID_MAX && rssi >= RSSI_VALID_MIN; }

    bool performCarrierSense(RadioInterface *iface);

    uint32_t getLastTxEndTime() const { return lastTxEndTime; }
    void setLastTxEndTime(uint32_t t) { lastTxEndTime = t; }
    uint32_t getBusyCount() const { return busyCount; }
    void resetBusyCount() { busyCount = 0; }
    void reset()
    {
        lastTxEndTime = 0;
        busyCount = 0;
    }

  private:
    uint32_t lastTxEndTime = 0;
    uint32_t busyCount = 0;
};

extern JapanTxHook *japanTxHook;
void initJapanTxHook();
