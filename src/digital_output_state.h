#pragma once
#include <gpio.h>

template <uint8_t pin>
class digital_output_state: public digital_output_pin<pin>
{
public:
   inline auto toogle() -> bool
   {
      const auto prev = value_;
      this->set_value(!prev);
      return prev;
   }

   inline
   void set_value(bool is_on)
   {
      value_ = is_on;
      write_state(is_on);
   }

   inline
   auto get_value() const -> bool
   {
      return value_;
   }
private:
   void write_state(bool is_on)
   {
      this->write(is_on);
   }

   bool value_ = false;
};
