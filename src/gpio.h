#pragma once
#include <Arduino.h>
#include "call.h"

template <uint8_t pin>
class digital_input_pin
{
public:
   void setup()
   {
      pinMode(pin, INPUT);
   }

   auto read() -> bool
   {
      return digitalRead(pin) != LOW;
   }
};


template <uint8_t pin>
class digital_output_pin
{
public:
   void setup()
   {
      pinMode(pin, OUTPUT);
   }

   auto write(bool b) -> void
   {
      return digitalWrite(pin, b?HIGH:LOW);
   }
};

template <class...T>
void setup_all(T&... dev)
{
   for_every([](auto& v){ v.setup();}, dev...);
}

template <class...T>
void check_all(T&... dev)
{
   for_every([](auto& v){ v.check();}, dev...);
}


