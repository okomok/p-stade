#ifndef PSTADE_OVEN_RANGE_HOLDER_HPP
#define PSTADE_OVEN_RANGE_HOLDER_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/any.hpp>
#include <boost/noncopyable.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/oven/distance.hpp>


namespace pstade { namespace oven {


struct range_placeholder
{
    virtual ~range_placeholder() { }

    boost::any begin() { return override_begin(); }
    boost::any end() { return override_end(); }
    boost::any size() { return override_size(); }
    bool empty() { return override_empty(); }

    boost::any ptr_begin() { return override_ptr_begin(); }
    boost::any ptr_end() { return override_ptr_end(); }

protected:
    virtual boost::any override_begin() = 0;
    virtual boost::any override_end() = 0;
    virtual boost::any override_size() = 0;
    virtual bool override_empty() = 0;

    virtual boost::any override_ptr_begin() = 0;
    virtual boost::any override_ptr_end() = 0;
};


template< class Range >
struct range_holder :
    range_placeholder,
    private boost::noncopyable
{
    explicit range_holder(Range& rng) :
        m_held(rng)
    { }

    Range& held() { return m_held; }

protected:
    boost::any override_begin() { return boost::begin(m_held); }
    boost::any override_end() { return boost::end(m_held); }
    boost::any override_size() { return oven::distance(m_held); }
    bool override_empty() { return boost::empty(m_held); }

    boost::any override_ptr_begin() { return boost::addressof( *boost::begin(m_held) ); }
    boost::any override_ptr_end() { return boost::addressof( *boost::end(m_held) ); }

private:
    Range& m_held;
};


} } // namespace pstade::oven


#endif
