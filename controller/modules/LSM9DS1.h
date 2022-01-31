#include <Arduino_LSM9DS1.h>

/*
    This sensor has an accelerometer, a gyroscope and a magnetometer.
    All three characteristics have this structure, returning an (averaged/dampened) float for each direction.

    |    x    |    y    |    z      |
    | 0 1 2 3 | 4 5 6 7 | 8 9 10 11 |

*/

// Bluetooth Characteristics UUID
const char *LSM9DS1_gyroscope_characteristic_uuid = "19b10001-e8f2-537e-4f6c-d104768a1214";
const char *LSM9DS1_accelerometer_characteristic_uuid = "19b10002-e8f2-537e-4f6c-d104768a1214";
const char *LSM9DS1_magnetometer_characteristic_uuid = "19b10003-e8f2-537e-4f6c-d104768a1214";

// Bluetooth Characteristics
BLECharacteristic LSM9DS1_gyroscope_characteristic(LSM9DS1_gyroscope_characteristic_uuid, BLERead | BLENotify, 12, /*fixedLength*/ true);

// Bluetooth Characteristic Buffers
uint8_t LSM9DS1_gyroscope_characteristic_buffer[12];

// values to update
float gyroscope_x;
float gyroscope_y;
float gyroscope_z;

void LSM9DS1_initialize()
{
    if (!IMU.begin())
    {
        while (1)
            ;
    }
}

void LSM9DS1_gyroscope_read(float &gyroscope_x, float &gyroscope_y, float &gyroscope_z)
{
    if (IMU.gyroscopeAvailable())
    {
        IMU.readGyroscope(gyroscope_x, gyroscope_y, gyroscope_z);
    }
}

void LSM9DS1_gyroscope_serial_print()
{
    float gyroscope_x;
    float gyroscope_y;
    float gyroscope_z;
    LSM9DS1_read_gyroscope(gyroscope_x, gyroscope_y, gyroscope_z);
    Serial.print("Gyroscope: x: ");
    Serial.print(gyroscope_x);
    Serial.print(", y: ");
    Serial.print(gyroscope_y);
    Serial.print(", z: ");
    Serial.println(gyroscope_z);
}

void LSM9DS1_gyroscope_serial_printe_sample_rate()
{
    // 119 Hz
    Serial.print("Gyroscope sample rate = ");
    Serial.print(IMU.gyroscopeSampleRate());
    Serial.println(" Hz");
}

void LSM9DS1_gyroscope_update_characteristic_buffer()
{
    memcpy(&LSM9DS1_gyroscope_characteristic_buffer[0], &gyroscope_x, 4);
    memcpy(&LSM9DS1_gyroscope_characteristic_buffer[4], &gyroscope_y, 4);
    memcpy(&LSM9DS1_gyroscope_characteristic_buffer[8], &gyroscope_z, 4);
}

void LSM9DS1_gyroscope_write_characteristic()
{
    LSM9DS1_gyroscope_characteristic.writeValue(LSM9DS1_gyroscope_characteristic_buffer, 12)
}