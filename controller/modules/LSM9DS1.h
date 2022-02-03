#include <Arduino_LSM9DS1.h>
#include "sensor_xyz.h"
/*
    This sensor has an accelerometer, a gyroscope and a magnetometer.

    All three "sub-sensors" will inherit from the SensorXYZ class, as they handle a 3-dimensional vector of floats.
*/

// Bluetooth Characteristics UUID
const char *LSM9DS1_gyroscope_characteristic_uuid = "19b10001-e8f2-537e-4f6c-d104768a1214";
const char *LSM9DS1_accelerometer_characteristic_uuid = "19b10002-e8f2-537e-4f6c-d104768a1214";
const char *LSM9DS1_magnetometer_characteristic_uuid = "19b10003-e8f2-537e-4f6c-d104768a1214";

class LSM9DS1_Gyroscope : public SensorXYZ
{
private:
    void read_sensor(float &x, float &y, float &z);

public:
    LSM9DS1_Gyroscope(BLECharacteristic &characteristic, const char *sensor_name) : SensorXYZ(characteristic, sensor_name){};
    void serial_print_sample_rate();
    bool initialize();
};

void LSM9DS1_Gyroscope::serial_print_sample_rate()
{
    // 119 Hz
    Serial.print("Gyroscope sample rate = ");
    Serial.print(IMU.gyroscopeSampleRate());
    Serial.println(" Hz");
}

bool LSM9DS1_Gyroscope::initialize()
{
    return IMU.begin();
}

void LSM9DS1_Gyroscope::read_sensor(float &x, float &y, float &z)
{
    // Serial.print("read ");
    if (IMU.gyroscopeAvailable())
    {
        IMU.readGyroscope(x, y, z);
        // Serial.println(x);
    }
}
