int pHSense = 32;
int samples = 10;
float adc_resolution = 4095.0; //ESP 32 ADC Resolution

void setup()
{
    Serial.begin(9600);
    delay(100);
    Serial.println("pH Sense");
}

float ph (float voltage) {
    return 7 + ((1.30 - voltage) / 0.18);
}

void loop()
{
    int measurings=0;

    for (int i = 0; i < samples; i++)
    {
        measurings += analogRead(pHSense);
        delay(10);

    }

    float voltage = 5 / adc_resolution * measurings/samples;
    Serial.print("pH= ");
    Serial.println(ph(voltage));
    delay(1000);
}
