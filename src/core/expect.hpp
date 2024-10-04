#ifndef GR_CORE_ASSERT_HPP
#define GR_CORE_ASSERT_HPP

#include <assert.h>

#define gr_expect(test, mesg) \
    assert((test) && mesg)

#define gr_expectc(test, mesg) \
    static_assert(test, mesg)

#endif // GR_CORE_ASSERT_HPP
