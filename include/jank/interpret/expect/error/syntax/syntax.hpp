#pragma once

#include <stdexcept>
#include <string>

namespace jank
{
  namespace interpret
  {
    namespace expect
    {
      namespace error
      {
        namespace syntax
        {
          struct generic
          { static char const constexpr *description{ "expression" }; };

          template <typename T = generic>
          struct exception : std::runtime_error
          {
            exception()
              : std::runtime_error
                { std::string{ "syntax error (" } + T::description + ")" }
            { }
            exception(std::string const &s)
              : std::runtime_error
                { std::string{ "syntax error (" } + T::description + "): " + s }
            { }
          };
        }
      }
    }
  }
}
