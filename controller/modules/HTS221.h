#include <Arduino_HTS221.h>

void HTS221_initialize()
{
    if (!HTS.begin())
    {
        while (1)
            ;
    }
}

float HTS221_read_temperature()
{
    return HTS.readTemperature();
}

float HTS221_read_humidity()
{
    return HTS.readHumidity();
}