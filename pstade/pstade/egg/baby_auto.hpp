#ifndef PSTADE_EGG_BABY_AUTO_HPP
#define PSTADE_EGG_BABY_AUTO_HPP


// PStade.Egg
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Question:
//
// 'mpl::identity<To>' is better?


#include <pstade/nonassignable.hpp>


namespace pstade { namespace egg {


template< class CastFunClass >
struct baby_auto
{
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
            return CastFunClass::template call<To>(m_from);
        }

    private:
        From& m_from;
    };

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


} } // namespace pstade::egg


#endif
