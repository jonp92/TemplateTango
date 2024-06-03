# TemplateTango
![TemplateTango Logo](https://github.com/jonp92/TemplateTango/blob/6bbdf242115dbba2eca92f017660a15902b9c88f/tt_no_text.png?raw=true)

TemplateTango is a versatile template engine designed for Arduino and ESP32 microcontrollers. It allows for the dynamic generation of any text-based content, such as HTML, XML, JSON, or plain text, by substituting placeholders with real-time data from sensors or other sources.

## Features

- **Dynamic Content Generation**: Generate any text-based content dynamically by replacing placeholders with real-time values.
- **Ease of Use**: Simple and intuitive API for defining templates and passing variables.
- **Expression Evaluation**: Supports basic arithmetic expressions and string concatenation within templates.
- **Modularity**: Easily integrates with existing Arduino and ESP32 projects, including web servers like `ESPAsyncWebServer`.

## Installation

To use TemplateTango, simply include the `TemplateTango.h` file in your project.

## Usage

### Basic Example

```cpp
#include <Arduino.h>
#include "TemplateTango.h"

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
    std::map<string, string> variables = {
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
```

## API

**setVariable(const string& varName, const string& value)**
Sets the value of a variable.

**varName:** The name of the variable.
value: The value of the variable.
render(const string& templateStr, const map<string, string>& variables)
Renders the template string with the provided variables.

**templateStr:** The template string containing placeholders for variables.
variables: A map of variable names and their corresponding values.
Returns: A string with variables replaced by their corresponding values.
