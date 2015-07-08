#pragma once

#include <stdexcept>
#include <string>

namespace jank
{
  namespace parse
  {
    namespace expect
    {
      namespace error
      {
        namespace syntax
        {
          namespace detail
          {
            struct generic
            { static char const constexpr *description{ "expression" }; };
          }

          template <typename T = detail::generic>
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