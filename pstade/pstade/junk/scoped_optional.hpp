#ifndef PSTADE_OVEN_DETAIL_UNINIT_OPTIONAL_HPP
#define PSTADE_OVEN_DETAIL_UNINIT_OPTIONAL_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/optional/optional_fwd.hpp>


namespace pstade { namespace oven { namespace detail {


template< class Iterator >
struct scoped
{
    explicit scoped(Iterator& it) :
        m_ref(it), m_saved(it)
    { };

    ~scoped()
    {
        if (!m_dismissed)
            m_it = m_saved;
    }

    void dismiss()
    {
        m_dismissed = true;
    }

private:
    Iterator& m_ref;
    Iterator m_saved;
    bool m_dismissed;
};


template< class T >
struct uninit_optional<T>
{
    explicit scoped(boost::optional<T>& opt) :
        m_opt(opt), m_dismissed(false)
    { };

    ~scoped()
    {
        if (!m_dismissed)
            m_opt = boost::optional<T>();
    }

    void dismiss()
    {
        m_dismissed = true;
    }

    bool m_dismissed;
};


} } } // namespace pstade::oven::detail


#endif
