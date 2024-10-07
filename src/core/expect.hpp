#ifndef GR_CORE_EXPECT_HPP
#define GR_CORE_EXPECT_HPP

#include <assert.h>

#define gr_cmpl_expect(test, message) \
    static_assert(test, message)

#define gr_exec_expect(test, message) \
    assert((test) && message)

#endif // GR_CORE_EXPECT_HPP
