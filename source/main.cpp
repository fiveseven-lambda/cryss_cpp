/**
 * @file main.cpp
 */
#include "type.hpp"

#include <functional>
#include <iostream>

int main() {
    type::TypeContext type_context;
    auto get_integer = [&]{ return std::cref(type_context.primitive(type::PrimitiveKind::Integer)); };
    type_context.function(
        {
            type_context.function({get_integer()}, get_integer()),
            type_context.function({get_integer()}, get_integer())
        },
        type_context.function({get_integer()}, get_integer())
    );
    type_context.debug_print(0);
}
