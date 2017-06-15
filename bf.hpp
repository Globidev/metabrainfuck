#include <array>
#include <string_view>

namespace bf {

    using          default_memory_cell_t = char;
    constexpr auto default_memory_size   = 4096ul;
    constexpr auto default_output_size   = 4096ul;

    // Stores an interpreted brainfuck result and can be compared with a string
    template <class Output, class Size = typename Output::size_type>
    struct result_t {
        Output output;
        Size size;

        constexpr operator std::string_view() const {
            return { output.data(), size };
        }

        constexpr auto operator==(std::string_view expected) const {
            return expected == *this;
        }
    };
    // Deduction guide
    template <class... Cs> result_t(Cs...) -> result_t<Cs...>;

    // Evaluation entrypoint
    template <
        auto  memory_size   = default_memory_size,
        auto  output_size   = default_output_size,
        class memory_cell_t = default_memory_cell_t,
        auto  input_size
    >
    constexpr auto eval(const char (&bf_code)[input_size]) {
        using memory_t = std::array<memory_cell_t, memory_size>;
        using output_t = std::array<char, output_size>;

        auto memory     = memory_t { 0 };
        auto pointer    = typename memory_t::size_type { 0 };
        auto output     = output_t { 0 };
        auto output_idx = typename output_t::size_type { 0 };

        for (auto i = 0; i < input_size; ++i) {

            switch (bf_code[i]) {
                case '>':   ++pointer;
                            break;
                case '<':   --pointer;
                            break;
                case '+':   ++memory[pointer];
                            break;
                case '-':   --memory[pointer];
                            break;
                case '.':   output[output_idx++] = memory[pointer];
                            break;
                case '[':   // could check for unclosed brackets
                            break;
                case ']':   if (memory[pointer] == 0) break;

                            for (auto opening_braces_left = 1; opening_braces_left > 0;) {
                                auto c = bf_code[--i];

                                if      (c == '[') --opening_braces_left;
                                else if (c == ']') ++opening_braces_left;
                            }
                            break;
                case '\0':
                            break;
                default:    throw std::logic_error { "Invalid character" };
            }

        }

        return result_t { output, output_idx };
    };

    namespace literals {

        template <class CharT, CharT... cs>
        constexpr auto operator""_bf() {
            return eval({ cs... });
        }

    }

}
