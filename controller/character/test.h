// TEST CHARACTER
// Model functions for populating a controller with a character
const char *controller_name = "Test Character Controller";
float humidity = 0;

bool initialize_sensors()
{
    HTS221_initialize();
    return true;
}

void update()
{
    // behaviour:
    // humidity decreasing -> face_left
    // humidity increasing -> face_right
    float humidity_reading = HTS221_read_humidity();

    if (humidity > humidity_reading)
    {
        make_move = direction.right;
    }
    else
    {
        make_move = direction.left;
    }
    humidity = humidity_reading;
}