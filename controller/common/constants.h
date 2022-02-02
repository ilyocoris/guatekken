
// BASE KIT CHARACTERISTIC
// 0-idle | 1-left | 2-right
enum direction
{
    IDLE,
    LEFT,
    RIGHT
};
const uint8_t MOVE = 0;
const uint8_t JUMP = 1;
const uint8_t DODGE = 2;
const uint8_t BASIC_ATTACK = 3;

const uint8_t BUFFER_BASE_ABILITIES_LENGTH = 4;

// BLUETOOTH UUIDS
const char *controller_service_uuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char *base_characteristic_uuid = "19b10001-e8f2-537e-4f6c-d104768a1214";

//
uint8_t base_characteristic_buffer[BUFFER_BASE_ABILITIES_LENGTH];
//
uint8_t make_move = 0;
uint8_t make_jump = 0;
uint8_t make_dodge = 0;
uint8_t make_basic_attack = 0;
//

// SENSORS VARIABLES
// HTS221
float humidity;
float temperature;
// LSM9DS1
// float gyroscope_x;
// float gyroscope_y;
// float gyroscope_z;