#include <Arduino_HTS221.h>

void initialize_HTS221()
{
    if (!HTS.begin())
    {
        while (1)
            ;
    }
}

float HTS221_read_temperature(float &temperature)
{
    temperature = HTS.readHumidity();
}

void HTS221_serial_print_temperature()
{
    Serial.print("Temperature: ");
    Serial.println(HTS.readTemperature());
}

void HTS221_serial_print_humidity()
{
    Serial.print("Humidity: ");
    Serial.println(HTS.readHumidity());
}

void HTS221_read_humidity(float &humidity)
{
    humidity = HTS.readHumidity();
}