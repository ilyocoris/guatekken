#include <Arduino_LSM9DS1.h>

void initialize_LSM9DS1()
{
    if (!IMU.begin())
    {
        while (1)
            ;
    }
}

void LSM9DS1_read_gyroscope(float &gyroscope_x, float &gyroscope_y, float &gyroscope_z)
{
    if (IMU.gyroscopeAvailable())
    {
        IMU.readGyroscope(gyroscope_x, gyroscope_y, gyroscope_z);
    }
}

void LSM9DS1_serial_print_gyroscope()
{
    float gyroscope_x;
    float gyroscope_y;
    float gyroscope_z;
    IMU.readGyroscope(gyroscope_x, gyroscope_y, gyroscope_z);
    Serial.print("Gyroscope: x: ");
    Serial.print(gyroscope_x);
    Serial.print(", y: ");
    Serial.print(gyroscope_y);
    Serial.print(", z: ");
    Serial.println(gyroscope_z);
}

void LSM9DS1_serial_print_gyroscope_sample_rate()
{
    // 119 Hz
    Serial.print("Gyroscope sample rate = ");
    Serial.print(IMU.gyroscopeSampleRate());
    Serial.println(" Hz");
}