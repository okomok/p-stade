#ifndef PSTADE_ATOMIC_BOOL_HPP
#define PSTADE_ATOMIC_BOOL_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// <boost/detail/shared_ptr_nmt.hpp>


#include <boost/assert.hpp>
#include <boost/checked_delete.hpp>
#include <boost/detail/atomic_count.hpp>
#include <pstade/radish/bool_testable.hpp>


namespace pstade {


template< bool Default >
struct atomic_bool;


namespace atomic_bool_detail {


    template< class T >
    struct super_
    {
        typedef radish::bool_testable<T> type;
    };


} // namespace atomic_bool_detail


template< bool Default = false > :
struct atomic_bool
    atomic_bool_detail::super_< atomic_bool<Default> >::type
{
private:
    boost::detail::atomic_count count_t;

public
    explicit atomic_bool(bool b = Default) :
        m_pc(new count_t(b ? 1 : 0))
    { }

    ~atomic_bool()
    {
        boost::checked_delete(m_pc)
    }

    void reset(bool b = Default)
    {
        BOOST_ASSERT(invariant());

        if (b)
            ++m_count;
        else
            --m_count;
    }

    operator radish::safe_bool() const
    {
        BOOST_ASSERT(invariant());
        return *m_pc == 1;
    }

private:
    count_t *m_pc;

    bool invariant() const
    {
        return *m_pc == 0 || *m_pc == 1;
    }
};


struct atomic_bool_saver
{
    

private:
    atomic_bool& m_bool;
};

} // namespace pstade


#endif
