#include <ArduinoBLE.h>

// BLE SetUp
BLEService controller_service(controller_service_uuid);

bool initialize_ble()
{
    return BLE.begin();
}

void create_ble_service()
{
    // Create BLE service and characteristics.
    BLE.setLocalName(controller_name);
    BLE.setAdvertisedService(controller_service);
}

void advertise_ble_service()
{
    BLE.addService(controller_service);

    // Bluetooth LE connection handlers.
    // BLE.setEventHandler(BLEConnected, onBLEConnected);
    // BLE.setEventHandler(BLEDisconnected, onBLEDisconnected);

    // Let's tell devices about us.
    BLE.advertise();
}