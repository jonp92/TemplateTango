#include <Arduino.h>
#include <TemplateTango.h>

// Functions to simulate sensor readings
string readTemperature() { return "25.5"; }
string readSensor1() { return "100.1"; }
string readSensor2() { return "200.2"; }

void setup() {
    Serial.begin(9600);

    // Define the template
    string templateStr = R"(
        <!DOCTYPE html>
        <html>
        <head>
            <title>Sensor Data</title>
        </head>
        <body>
            <h1>Sensor Readings</h1>
            <p>Current Temperature: {{temperature}} °C</p>
            <p>Temperature in Fahrenheit: {{(temperature * 9 / 5) + 32}} °F</p>
            <p>Sensor 1 Reading: {{sensor1_reading}}</p>
            <p>Sensor 2 Reading: {{sensor2_reading}}</p>
        </body>
        </html>
    )";

    // Collect variable values
    map<string, string> variables = {
        {"temperature", readTemperature()},
        {"sensor1_reading", readSensor1()},
        {"sensor2_reading", readSensor2()}
    };

    // Render the template
    string renderedHtml = TemplateTango::render(templateStr, variables);
    Serial.println(renderedHtml.c_str());
}

void loop() {
    // Main loop
}
