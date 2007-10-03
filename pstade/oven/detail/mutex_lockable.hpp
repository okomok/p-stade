#ifndef PSTADE_OVEN_DETAIL_MUTEX_LOCKABLE_HPP
#define PSTADE_OVEN_DETAIL_MUTEX_LOCKABLE_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/noncopyable.hpp>
#include "./config.hpp" // PSTADE_OVEN_HAS_THREADS

#if defined(PSTADE_OVEN_HAS_THREADS)
    #include <boost/detail/lightweight_mutex.hpp>
#endif


namespace pstade { namespace oven { namespace detail {


#if defined(PSTADE_OVEN_HAS_THREADS)

    struct mutex_lockable :
        private boost::noncopyable
    {
        typedef boost::detail::lightweight_mutex mutex_type;
        typedef boost::detail::lightweight_mutex::scoped_lock scoped_lock_type;

        mutex_type& mutex() const
        {
            return m_mutex;
        }

    private:
        mutable mutex_type m_mutex;
    };

#else

    // expects EBO.
    struct mutex_lockable :
        private boost::noncopyable
    {
        typedef int mutex_type;
        struct scoped_lock_type { explicit scoped_lock_type(int) { } };

        mutex_type mutex() const
        {
            return 0;
        }
    };

#endif // defined(PSTADE_OVEN_HAS_THREADS)


} } } // namespace pstade::oven::detail


#endif
