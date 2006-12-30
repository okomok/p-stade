#ifndef PSTADE_TOMATO_BOOLEAN_CAST_HPP
#define PSTADE_TOMATO_BOOLEAN_CAST_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// 'boost::numeric_cast'


// Note:
//
// 'boolean/booleanized' is slightly slower.


#include <pstade/apple/sdk/windows.hpp>
#include <pstade/apple/sdk/wtypes.hpp> // VARIANT_BOOL
#include <pstade/auto_castable.hpp>
#include <pstade/pipable.hpp>


namespace pstade { namespace tomato {


namespace boolean_cast_detail {


    template<class To, class From>
    struct cvter;


    #define PSTADE_TOMATO_cvter(To, From, Expr) \
        template< > \
        struct cvter<To, From> \
        { \
            static To cvt(From from) \
            { \
                return Expr; \
            } \
        }; \
    /**/


    #define PSTADE_TOMATO_cvter_set(To, True, False) \
        PSTADE_TOMATO_cvter(To, bool, from ? True : False) \
        PSTADE_TOMATO_cvter(To, BOOL, from ? True : False) \
        PSTADE_TOMATO_cvter(To, VARIANT_BOOL, from ? True : False) \
        PSTADE_TOMATO_cvter(To, BOOLEAN, from ? True : False) \
        PSTADE_TOMATO_cvter(To, LRESULT, from ? True : False) \
    /**/


    PSTADE_TOMATO_cvter_set(bool, true, false)
    PSTADE_TOMATO_cvter_set(BOOL, TRUE, FALSE)
    PSTADE_TOMATO_cvter_set(VARIANT_BOOL, VARIANT_TRUE, VARIANT_FALSE)
    PSTADE_TOMATO_cvter_set(BOOLEAN, (BOOLEAN)TRUE, (BOOLEAN)FALSE)
    PSTADE_TOMATO_cvter_set(LRESULT, 1, 0)


    #undef PSTADE_TOMATO_cvter_set
    #undef PSTADE_TOMATO_cvter


} // namespace boolean_cast_detail


template<class To, class From> inline
To boolean_cast(From from)
{
    typedef boolean_cast_detail::cvter<To, From> cvter_t;
    return cvter_t::cvt(from);
}


template< class To >
struct op_boolean_cast
{
    typedef To result_type;

    template<class From>
    To operator()(From const& from) const
    {
        return tomato::boolean_cast<To>(from);
    }
};

PSTADE_PIPABLE(booleanized, (auto_castable<op_boolean_cast<boost::mpl::_1> >))


} } // namespace pstade::tomato


#endif
