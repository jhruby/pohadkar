//
// Created by jan on 26.11.23.
//
#include "Arduino.h"
#include "virtual_switch.h"
#include <SPI.h>

#include "../lib/SdFat/SdFat.h"
#include "../lib/SdFat/SdFatUtil.h"

#include "../lib/SFEMP3Shield/SFEMP3Shield.h"

template <uint8_t pin>
using led = digital_output_pin<pin>;

SdFat sd;
SFEMP3Shield player;

struct pohadkar
{
   virtual_switch<A5> button_b = {};
   virtual_switch<A4> button_g = {};
   virtual_switch<A3> button_r = {};
   button<A2> button_play = {};

   led<5> led_b = {};
   led<4> led_g = {};
   led<3> led_r = {};
   led<10> led_play = {};

#define POHADKAR_INPUT button_b, button_g, button_r, button_play
#define POHADKAR_OUTPUT led_b, led_g, led_r, led_play

   void setup()
   {
      Serial.begin(115000); // open the serial port at 9600 bps:
      setup_all(POHADKAR_INPUT, POHADKAR_OUTPUT);
   }

   void check()
   {
      check_all(POHADKAR_INPUT);
      if (button_play.is_on_pressed())
      {
         player.playMP3("TEST.OGG");
      }

      led_b.write(button_b.is_on());
      led_g.write(button_g.is_on());
      led_r.write(button_r.is_on());

      led_play.write(player.isPlaying());
   }
};

static auto pohadkar_state = pohadkar{};

void setup()
{
   pohadkar_state.setup();
   Serial.begin(9600);

   Serial.print(F("F_CPU = "));
   Serial.println(F_CPU);
   Serial.print(F("Free RAM = ")); // available in Version 1.0 F() bases the string to into Flash, to use less SRAM.
   Serial.print(FreeRam(), DEC);   // FreeRam() is provided by SdFatUtil.h
   Serial.println(F(" Should be a base line of 1028, on ATmega328 when using INTx"));

   // Initialize the SdCard.
   if (!sd.begin(9)) sd.initErrorHalt();

   sd.chdir("/");
   sd.ls();

   player.begin();
}

void loop()
{
   pohadkar_state.check();
}