
// https://create.arduino.cc/projecthub/haraldholzner/angnano-visualize-nano-ble-sense-data-within-the-browser-34622d

// https://store.arduino.cc/products/arduino-mkr-iot-carrier

// UNIVERSAL DEFINITIONS
#include "common/constants.h"
// SENSOR MODULES
#include "modules/HTS221.h" // temperature and humidity
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
    initialize_sensors();
    // BLE initialization
    create_and_advertise_ble_service();
}

void loop()
{
    BLEDevice central = BLE.central();
    // character-controller update
    update();
    // push update to ble
    update_base_characteristic();
    //
    if (central && central.connected())
    {
        Serial.print("Connected to central: ");
        // print the central's MAC address:
        Serial.println(central.address());
    }
    Serial.println(make_move);
    delay(1);
}