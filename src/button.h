#pragma once

#include "gpio.h"

struct no_op_listener
{
   void operator()(bool) const {}
};
template <uint8_t pin>
class button : public digital_input_pin<pin>
{
 public:
   void check()
   {
      const auto now = millis();
      const auto delta_time = now - last_change_at_;
      state_ = state_ & ~button_on_pressed;

      const auto val = this->read();
      if (val == HIGH && state_ == button_up && delta_time > 100)
      {
         state_ = button_pressed | button_on_pressed;
         last_change_at_ = now;
      }
      else if (val == LOW && delta_time > 100)
      {
         state_ = button_up;
         last_change_at_ = now;
      }
   }

   auto is_pressed() const -> bool
   {
      return (state_ & button_pressed) != 0;
   }

   auto is_on_pressed() const -> bool
   {
      return (state_ & button_on_pressed) != 0;
   }

 private:
   unsigned long last_change_at_ = 0;
   enum button_state
   {
      button_up,
      button_pressed,
      button_on_pressed
   };

   button_state state_ = button_up;
};
