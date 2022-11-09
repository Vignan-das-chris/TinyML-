#define NUM_HOURS 3

constexpr int num_reads = 3;
constexpr float t_mean = 2.05179f;
constexpr float h_mean = 82.30551f;
constexpr float t_std = 7.33084f;
constexpr float h_std = 14.55707f;

int8_t t_vals[NUM_HOURS] = {0};
int8_t h_vals[NUM_HOURS] = {0};
int cur_idx = 0;
float tflu_i_scale = 0.0f;
int32_t tflu_i_zero_point = 0;

inline int8_t quantize(float x, float scale, float zero_point)
{
    return (x / scale) + zero_point;
}

#if defined(ARDUINO_ARDUINO_NANO33BLE)
#include <Arduino_HTS221.h>

#define READ_TEMPERATURE() HTS.readTemperature()
#define READ_HUMIDITY() HTS.readHumidity()

void setup()
{
    Serial.begin(9600);

    while (!Serial)
        ;

    if (!HTS.begin())
    {

        Serial.println("Failed initialization of HTS221!");
        while (1)
            ;
    }
}
#endif // defined(ARDUINO_ARDUINO_NANO33BLE)

#if defined(ARDUINO_RASPBERRY_PI_PICO)
#include <DHT.h>

const int gpio_pin_dht_pin = 10;

DHT dht(gpio_pin_dht_pin, DHT11);

#define READ_TEMPERATURE() dht.readTemperature()
#define READ_HUMIDITY() dht.readHumidity()

void setup()
{
    Serial.begin(9600);
    while (!Serial)
        ;

    dht.begin();

    delay(2000);
}
#endif

void loop()
{
    float t = 0.0f;
    float h = 0.0f;

    for (int i = 0; i < num_reads; ++i)
    {
        t += READ_TEMPERATURE();
        h += READ_HUMIDITY();

        delay(3000);
    }

    t /= (float)num_reads;
    h /= (float)num_reads;

    Serial.print("Temperature = ");
    Serial.print(t, 2);
    Serial.println(" °C");
    Serial.print("Humidity = ");
    Serial.print(h, 2);
    Serial.println(" %");

    t = (t - t_mean) / t_std;
    h = (h - h_mean) / h_std;

    t_vals[cur_idx] = quantize(t, tflu_i_scale, tflu_i_zero_point);
    h_vals[cur_idx] = quantize(h, tflu_i_scale, tflu_i_zero_point);

    cur_idx = (cur_idx + 1) % NUM_HOURS;

    delay(2000);
}
