#include <jank/parse/expect/type.hpp>
#include <jank/translate/plugin/arithmetic/add.hpp>
#include <jank/translate/environment/builtin/type/primitive.hpp>
#include <jank/translate/environment/builtin/value/primitive.hpp>
#include <jank/interpret/environment/resolve_value.hpp>

namespace jank
{
  namespace translate
  {
    namespace plugin
    {
      namespace arithmetic
      {
        static void make_binary_operator
        (
          std::shared_ptr<environment::scope> const &scope,
          std::string const &op,
          cell::detail::type_reference const &type
        )
        {
          auto const nested_scope(std::make_shared<environment::scope>());
          nested_scope->parent = scope;

          cell::native_function_definition def
          {
            {
              op,
              { { "data1", type }, { "data2", type } },
              type,
              [](auto const &scope, auto const &args) -> cell::cell
              {
                if(args.size() != 2)
                { throw expect::error::type::exception<>{ "invalid binary operator args" }; }

                parse::cell::integer::type ret{};
                for(auto const &arg : args)
                {
                  ret += parse::expect::type<parse::cell::type::integer>
                  (interpret::resolve_value(scope, arg.cell)).data;
                }
                return environment::builtin::value::integer(ret);
              },
              nested_scope
            }
          };

          scope->native_function_definitions[def.data.name].emplace_back
          (std::move(def));
        }

        void add(std::shared_ptr<environment::scope> const &scope)
        {
          /* TODO: Add op+ and * and / and - for all primitives. */
          make_binary_operator
          (scope, "+", environment::builtin::type::integer(*scope));
        }
      }
    }
  }
}
