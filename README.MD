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
Before using the `render` method of TemplateTango to replace variables with values, you must specify a mapping of variables and their values. Values must be strings or functions returning Strings. Additionally, the template that will have its variables replaced with values must be stored as a String.

Basic arithmetic is supported with operator precedence and parentheses. A simple example might be to convert ºC to ºF.

```cpp
{{(temperature * 9 / 5) + 32}}
```

A basic example of this setup is provided in the `BasicExample` sketch included with this library. The sketch demonstrates how to define a template string, collect variable values, and render the template with these values.

To render a template, simply call the `render` method as follows:

```cpp
TemplateTango::render(template, variables)
```
## API

**std::string render(const std::string& templateStr, const std::map<std::string, std::string>& variables)**
Renders the template string with the provided variables.

**templateStr:** The template string containing placeholders for variables.
**variables:** A map of variable names and their corresponding values.
**Returns:** A string with variables replaced by their corresponding values.

## Notes

- **String Usage**: To make this library simple to use, Arduino style Strings are employed. Due to dynamic memory allocation, these can lead to memory fragmentation issues. Additionally, large mappings may cause memory overflow issues if there is not sufficient RAM. Avoid large mappings on memory-limited devices. To reduce memory usage, keep arithmetic expressions simple and String lengths as short as possible.
