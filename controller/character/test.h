// TEST CHARACTER
// Model functions for populating a controller with a character
const char *controller_name = "Test Character Controller";
float humidity = 0;

bool initialize_character()
{
    HTS221_initialize();
    return true;
}

void update_character()
{
    // behaviour:
    // humidity decreasing -> face_left
    // humidity increasing -> face_right
    float humidity_reading = HTS221_read_humidity();

    if (humidity > humidity_reading)
    {
        make_move = RIGHT;
    }
    else
    {
        make_move = LEFT;
    }
    humidity = humidity_reading;
}