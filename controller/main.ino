
// https://create.arduino.cc/projecthub/haraldholzner/angnano-visualize-nano-ble-sense-data-within-the-browser-34622d

// https://store.arduino.cc/products/arduino-mkr-iot-carrier

#include <ArduinoBLE.h>
// UNIVERSAL DEFINITIONS
#include "common/constants.h"
// SENSOR MODULES
//#include "modules/sensor.h"
//#include "modules/HTS221.h"  // temperature and humidity
#include "modules/LSM9DS1.h" // gyro & accel
// CHARACTER
#include "character/test.h"
//#include "character/opla_kid.h"
// BLUETOOTH
#include "common/bluetooth.h"
// const char *LSM9DS1_gyroscope_characteristic_uuid = "19b10001-e8f2-537e-4f6c-d104768a1214";

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
    create_ble_service();
    add_characteristics_to_service(controller_service);
    advertise_ble_service();
    Serial.println("Setup Successful!");
}

void loop()
{
    BLEDevice central = BLE.central();
    //
    if (central && central.connected())
    {
        // perform readings
        update_readings();
        //
        push_characteristics();
        // Serial.print("Connected to central: ");
        // // print the central's MAC address:
        // Serial.println(central.address());
    }
    // Serial.println(make_move);
}