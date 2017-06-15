#include "bf.hpp"

using namespace bf::literals;

constexpr auto hello_world =
    "++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>."_bf;

static_assert(hello_world == "Hello World!\n");
// static_assert("get fucked"_bf == "??");                       // error: throw std::logic_error { "Invalid character" };
// static_assert("<+"_bf == "OOB write");                        // error: array subscript value '-1' is outside the bounds of array (gcc only)
// static_assert("+[]"_bf == "infinite loop");                   // error: constexpr evaluation hit maximum step limit; possible infinite loop? (clang only)
// static_assert("++]"_bf == "missing start loop");              // error: cannot refer to element -1 of array of 3 elements in a constant expression
// static_assert(bf::eval<256, 2>("+...") == "output too long"); // error: assignment to dereferenced one-past-the-end pointer is not allowed in a constant expression
// static_assert(bf::eval<2, 128>(">>+") == "OOB");              // error: increment of dereferenced one-past-the-end pointer is not allowed in a constant expression
