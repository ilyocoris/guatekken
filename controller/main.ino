
// https://create.arduino.cc/projecthub/haraldholzner/angnano-visualize-nano-ble-sense-data-within-the-browser-34622d

// https://store.arduino.cc/products/arduino-mkr-iot-carrier

// UNIVERSAL DEFINITIONS
#include "common/constants.h"
// SENSOR MODULES
#include "modules/HTS221.h"  // temperature and humidity
#include "modules/LSM9DS1.h" // gyro & accel
// CHARACTER
#include "character/test.h"
//#include "character/opla_kid.h"
// BLUETOOTH
#include "common/bluetooth.h"

void setup()
{
    Serial.begin(9600);
    while (!Serial)
        ;
    if (!initialize_ble())
    {
        Serial.println("Starting BLE failed!");
        while (true)
            ;
    }
    // character-controller initialization
    initialize_character();
    // BLE initialization
    create_and_advertise_ble_service();
    BLEDevice central = BLE.central();
}

void loop()
{
    //
    if (central && central.connected())
    {
        // character-controller update
        update_character();
        // push update to ble
        update_base_characteristic();
        Serial.print("Connected to central: ");
        // print the central's MAC address:
        Serial.println(central.address());
    }
    // Serial.println(make_move);
    delay(1);
}