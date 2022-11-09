void setup()
{
    Serial.begin(9600);
    while (!Serial)
        ;
    Serial.print("Initialized\n");
}

void loop()
{
    delay(2000);
    Serial.print("Executed\n");
}