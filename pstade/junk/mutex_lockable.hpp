#ifndef PSTADE_MUTEX_LOCKABLE_HPP
#define PSTADE_MUTEX_LOCKABLE_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp> // BOOST_HAS_THREADS

#if defined(BOOST_HAS_THREADS)
    #include <boost/detail/lightweight_mutex.hpp>
#endif


namespace pstade {


#if defined(BOOST_HAS_THREADS)

    struct mutex_lockable
    {
        typedef boost::detail::lightweight_mutex mutex_type;
        typedef boost::detail::lightweight_mutex::scoped_lock scoped_lock_type;

        mutex_type &mutex() const
        {
            return m_mutex;
        }

    private:
        mutable mutex_type m_mutex;

        mutex_lockable(mutex_lockable const &);
        mutex_locakble &operator=(mutex_lockable const &);
    };

#else

    struct mutex_lockable
    {
        struct mutex_type {};
        struct scoped_lock_type { explicit scoped_lock_type(mutex_type) {} };

        mutex_type mutex() const
        {
            return mutex_type();
        }

    private:
        mutex_lockable(mutex_lockable const &);
        mutex_locakble &operator=(mutex_lockable const &);
    };

#endif // defined(BOOST_HAS_THREADS)


} // namespace pstade


#endif
