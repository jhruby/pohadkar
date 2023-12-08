#pragma once

#include "button.h"

template <uint8_t pin>
class virtual_switch
{
 public:
   void setup()
   {
      button_.setup();
   }

   void check()
   {
      button_.check();
      if (button_.is_on_pressed())
      {
         is_on_ = !is_on_;
      }
   }

   auto is_on() const -> bool
   {
      return is_on_;
   }

 private:
   button<pin> button_;
   bool is_on_ = false;
};