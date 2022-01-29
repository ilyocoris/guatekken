/*
  Button LED

  This example creates a BLE peripheral with service that contains a
  characteristic to control an LED and another characteristic that
  represents the state of the button.

  The circuit:
  - Arduino MKR WiFi 1010, Arduino Uno WiFi Rev2 board, Arduino Nano 33 IoT,
    Arduino Nano 33 BLE, or Arduino Nano 33 BLE Sense board.
  - Button connected to pin 4

  You can use a generic BLE central app, like LightBlue (iOS and Android) or
  nRF Connect (Android), to interact with the services and characteristics
  created in this sketch.

  This example code is in the public domain.
*/

#include <ArduinoBLE.h>

const int led_pin = LED_BUILTIN;
const char *controller_name = "Basic Controller";
const char *controller_service_uuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char *basic_characteristic_uuid = "19b10001-e8f2-537e-4f6c-d104768a1214";

uint8_t test_int = 0;

BLEService controller_service(controller_service_uuid);

// 0 face right
// 1 face left
// 2 dash
// 3 crouch
// 5 jump
// 6 punch
// 8 kick

// create switch characteristic and allow remote device to read and write
BLECharacteristic test_characteristic(test_characteristic_uuid, BLERead | BLEWrite);
// create button characteristic and allow remote device to get notifications
// BLEByteCharacteristic buttonCharacteristic("19B10012-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify);

void setup()
{
    Serial.begin(9600);
    while (!Serial)
        ;

    pinMode(led_pin, OUTPUT);

    // begin initialization
    if (!BLE.begin())
    {
        Serial.println("starting BLE failed!");
    }

    // set the local name peripheral advertises
    BLE.setLocalName("Controller");
    // set the UUID for the service this peripheral advertises:
    BLE.setAdvertisedService(controller_service);

    // add the characteristics to the service
    controller_service.addCharacteristic(test_characteristic);

    // add the service
    BLE.addService(controller_service);

    test_characteristic.writeValue(0);

    // start advertising
    BLE.advertise();

    Serial.println("Bluetooth device active, waiting for connections...");
}

void loop()
{
    // listen for BLE peripherals to connect:
    BLECentral central = blePeripheral.central();

    // if a central is connected to peripheral:
    if (central)
    {
        Serial.print("Connected to central: ");
        // print the central's MAC address:
        Serial.println(central.address());

        // while the central is still connected to peripheral:
        while (central.connected())
        {
            // if the remote device wrote to the characteristic,
            // use the value to control the LED:
            if (switchCharacteristic.written())
            {
            }
            else
            {
                BLE.poll();
                if (test_int)
                {
                    test_characteristic.writeValue(test_int);
                    test_int = 0;
                }
                else
                {
                    test_characteristic.writeValue(test_int);
                    test_int = 1;
                }
                Serial.println(test_int);
                delay(2);
            }
        }

        // when the central disconnects, print it out:
        Serial.print(F("Disconnected from central: "));
        Serial.println(central.address());
    }
}
