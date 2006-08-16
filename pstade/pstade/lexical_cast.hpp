#ifndef PSTADE_LEXICAL_CAST_HPP
#define PSTADE_LEXICAL_CAST_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/lexical_cast.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/nonassignable.hpp>


namespace pstade {


template< class To, class From > inline
To lexical_cast(From const& from)
{
    return boost::lexical_cast<To>(from);
}


namespace lexical_cast_detail {


    template< class From >
    struct temp :
        private nonassignable
    {
        explicit temp(From& from) :
            m_from(from)
        { }

        template< class To >
        operator To() const
        {
            return pstade::lexical_cast<To>(m_from);
        }

    private:
        From& m_from;
    };


    struct baby_auto
    {
        template< class Unused, class From >
        struct result
        {
            typedef temp<From> const type;
        };

        template< class Result, class From >
        Result call(From& from)
        {
            return Result(from);
        }
    };


} // namespace lexical_cast_detail


PSTADE_EGG_FUNCTION(lexical, lexical_cast_detail::baby_auto)
PSTADE_EGG_PIPABLE(to_lexicon, lexical_cast_detail::baby_auto)


} // namespace pstade


#endif
