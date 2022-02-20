/*
 Handles bluetooth characteristic writting and averaging computation for sensors in three-dimensional space (floats).

 The structure of the bluetooth characteristic is the following:
| 0 1 2 3 | 4 5 6 7 | 8 9 10 11 |
|    x    |    y    |    z      |
*/

struct Axis
{
    float current_avg;
    float past_avg;
    float readings[3]; // 0 most recent -> n less recent
};

class SensorXYZ
{
private:
    Axis x = {0, 0, {0, 0, 0}};
    Axis y = {0, 0, {0, 0, 0}};
    Axis z = {0, 0, {0, 0, 0}};
    uint8_t characteristic_buffer[12];
    void update_characteristic_buffer();
    void write_characteristic();
    virtual void read_sensor(float &x, float &y, float &z){};
    void push_new_reading(Axis &axis, float new_reading);
    void update_average(Axis &axis);
    // bool update_characteristic = false;

public:
    // const char characteristic_uuid;
    const char *sensor_name;
    BLECharacteristic characteristic;
    SensorXYZ(BLECharacteristic &characteristic, const char *sensor_name);
    void push_characteristic();
    void serial_print();
    virtual bool initialize() { return 0; };
    void update_readings();
};

SensorXYZ::SensorXYZ(BLECharacteristic &characteristic, const char *sensor_name)
{
    // this->characteristic_uuid = characteristic_uuid;
    this->sensor_name = sensor_name;
    this->characteristic = characteristic;
}

void SensorXYZ::push_characteristic()
{
    // if (update_characteristic)
    // {
    update_characteristic_buffer();
    write_characteristic();
    // update_characteristic = false;
    // }
    // for (int i = 0; i < 12; ++i)
    // {
    //     Serial.print(characteristic_buffer[i]);
    //     Serial.print(" ");
    // }
}

void SensorXYZ::update_characteristic_buffer()
{
    memcpy(&characteristic_buffer[0], &x.current_avg, 4);
    memcpy(&characteristic_buffer[4], &y.current_avg, 4);
    memcpy(&characteristic_buffer[8], &z.current_avg, 4);
}

void SensorXYZ::write_characteristic()
{
    bool written = characteristic.writeValue(characteristic_buffer, 12, true);
    // Serial.println(written);
}

void SensorXYZ::serial_print()
{
    Serial.print(sensor_name);
    Serial.print(" x: ");
    Serial.print(x.current_avg);
    Serial.print(", y: ");
    Serial.print(y.current_avg);
    Serial.print(", z: ");
    Serial.println(z.current_avg);
}

void SensorXYZ::push_new_reading(Axis &axis, float new_reading)
{
    for (uint8_t i = 1; i < 3; ++i)
    {
        axis.readings[i] = axis.readings[i - 1];
    }
    axis.readings[0] = new_reading;
}

void SensorXYZ::update_average(Axis &axis)
{
    float sum = 0;
    float length = 3;
    for (uint8_t i = 0; i < length; ++i)
    {
        sum = sum + axis.readings[i];
    }
    float average = sum / length;
    axis.past_avg = axis.current_avg;
    // only update characteristic if significant change on one of the axis
    // if (abs(average - axis.current_avg) > 1)
    // {
    //     update_characteristic = true;
    // }
    axis.current_avg = average;
}

void SensorXYZ::update_readings()
{
    float new_reading_x, new_reading_y, new_reading_z;
    read_sensor(new_reading_x, new_reading_y, new_reading_z);
    push_new_reading(x, new_reading_x);
    push_new_reading(y, new_reading_y);
    push_new_reading(z, new_reading_z);
    // update_average(x);
    // update_average(y);
    // update_average(z);
}
