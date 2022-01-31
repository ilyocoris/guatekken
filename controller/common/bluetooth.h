#include <ArduinoBLE.h>

// BLE SetUp
BLEService controller_service(controller_service_uuid);

// Base
BLECharacteristic base_characteristic(base_characteristic_uuid, BLERead | BLENotify, BUFFER_BASE_ABILITIES_LENGTH, /*fixedLength*/ true);

bool initialize_ble()
{
    return BLE.begin();
}

void update_base_characteristic()
{
    memcpy(&base_characteristic_buffer[MOVE], &make_move, 1);
    memcpy(&base_characteristic_buffer[JUMP], &make_jump, 1);
    memcpy(&base_characteristic_buffer[DODGE], &make_dodge, 1);
    memcpy(&base_characteristic_buffer[BASIC_ATTACK], &make_basic_attack, 1);

    if (base_characteristic.writeValue(base_characteristic_buffer, BUFFER_BASE_ABILITIES_LENGTH))
    {
        digitalWrite(LED_BUILTIN, HIGH);
    }
    else
    {
        digitalWrite(LED_BUILTIN, LOW);
    }
}

void create_and_advertise_ble_service()
{
    // Create BLE service and characteristics.
    BLE.setLocalName(controller_name);
    BLE.setAdvertisedService(controller_service);
    controller_service.addCharacteristic(base_characteristic);
    BLE.addService(controller_service);

    // Bluetooth LE connection handlers.
    // BLE.setEventHandler(BLEConnected, onBLEConnected);
    // BLE.setEventHandler(BLEDisconnected, onBLEDisconnected);

    // Let's tell devices about us.
    BLE.advertise();
}