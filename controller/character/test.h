// TEST CHARACTER
// Model functions for populating a controller with a character
const char *controller_name = "Test Character Controller";

bool initialize_sensors()
{
    HTS221_initialize();
    LSM9DS1_initialize();
    return true;
}

void update_readings()
{
    // behaviour:
    // humidity decreasing -> face_left
    // humidity increasing -> face_right
    // LSM9DS1_read_gyroscope(gyroscope_x, gyroscope_y, gyroscope_z);
    LSM9DS1_serial_print_gyroscope();
    LSM9DS1_serial_print_gyroscope_sample_rate();
    // HTS221_serial_print_temperature();
    // HTS221_serial_print_humidity();
    // HTS221_read_humidity(humidity);
    //  float humidity_reading = HTS221_read_humidity();

    // if (humidity > humidity_reading)
    // {
    //     make_move = RIGHT;
    // }
    // else
    // {
    //     make_move = LEFT;
    // }
    // humidity = humidity_reading;
}

void write_characteristics()
{
}
