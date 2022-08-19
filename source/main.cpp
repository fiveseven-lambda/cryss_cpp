/**
 * @file main.cpp
 */
#include "type.hpp"

#include <functional>
#include <iostream>

int main() {
    type::TypeContext type_context;
    auto get_boolean = [&]{ return std::cref(type_context.primitive_type(type::PrimitiveTypeKind::Boolean)); };
    auto get_integer = [&]{ return std::cref(type_context.primitive_type(type::PrimitiveTypeKind::Integer)); };
    type_context.tuple({
        type_context.tuple({get_boolean(), get_integer()}),
        type_context.tuple({get_integer(), get_boolean()}),
        type_context.tuple({get_boolean(), get_integer()}),
        type_context.tuple({})
    });
    type_context.debug_print(0);
}
