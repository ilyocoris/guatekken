// TEST CHARACTER
// Model functions for populating a controller with a character
const char *controller_name = "TestController";

// GYROSCOPE
// Characteristic
BLECharacteristic LSM9DS1_gyroscope_characteristic(LSM9DS1_gyroscope_characteristic_uuid, BLERead | BLENotify, 12, /*fixedLength*/ true);
// Object
LSM9DS1_Gyroscope gyroscope(LSM9DS1_gyroscope_characteristic, "Gyroscope");

bool initialize_sensors()
{
    // HTS221_initialize();

    gyroscope.initialize();
    return true;
}

void update_readings()
{
    gyroscope.update_readings();
    // gyroscope.serial_print();
    // gyroscope.serial_print_sample_rate();
}

void push_characteristics()
{
    gyroscope.push_characteristic();
}

void add_characteristics_to_service(BLEService &service)
{
    service.addCharacteristic(gyroscope.characteristic);
}
