#ifndef GR_CORE_ASSERT_HPP
#define GR_CORE_ASSERT_HPP

#include <assert.h>

#define gr_run_assert(test, mesg) \
    assert((test) && mesg)

#define gr_cpl_assert(test, mesg) \
    static_assert(test, mesg)

#endif // GR_CORE_ASSERT_HPP
