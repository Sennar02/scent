#ifndef CORE_ASSERT_HPP
#define CORE_ASSERT_HPP

#include <assert.h>

#define RUNTIME_ASSERT(test, mesg) \
    assert((test) && mesg)

#define COMPILE_ASSERT(test, mesg) \
    static_assert(test, mesg)

#endif // CORE_ASSERT_HPP
