#include <core/str8.hpp>

namespace gr
{
    const byte&
    Str8::operator[](isize index) const
    {
        gr_exec_expect(0 < index && index <= items,
            "The index must be in range");

        return data[index - 1];
    }
} // namespace gr
