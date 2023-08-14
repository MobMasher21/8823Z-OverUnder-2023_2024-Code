/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       chez                                                      */
/*    Created:      7/20/2023, 2:40:59 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include <stdio.h>

#include <string>

#include "json.h"
#include "serial.h"
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain Brain;
motor Motor1 = motor(PORT20, false);
motor Motor2 = motor(PORT21, true);
// define your global instances of motors and other devices here

int main() {
    // takes any file pointer
    Serial serial(stdin, stdout);

    serial.write("Hello, I am the test data\n");
    // Brain.Screen.print("1");
    json::Json_encoder test_message;
    // Brain.Screen.print("2");

    test_message.add_key(json::string, "str");
    test_message.add_key(json::integer, "int");
    test_message.add_key(json::decimal, "dec");
    test_message.add_key(json::boolean, "bool");
    // Brain.Screen.print("3");

    test_message.finalize_keys();
    // Brain.Screen.print("4");

    std::string message1 = test_message.encode("hello", 12345, 3.1415, json::from_bool(true));
    std::string message2 = test_message.encode("hi", 54321, 1.2345, json::from_bool(false));
    // Brain.Screen.print("5");

    serial.write(message2);
    // Brain.Screen.print("6");

    while (1) {
        // Brain.Screen.print("7");

        std::string data = serial.read_string();
        Brain.Screen.print(data.c_str());

        // Allow other tasks to run
        this_thread::sleep_for(10);
    }
}
