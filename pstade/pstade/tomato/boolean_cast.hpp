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


#include <boost/utility/result_of.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/apple/sdk/wtypes.hpp> // VARIANT_BOOL
#include <pstade/auto_castable.hpp>
#include <pstade/pipable.hpp>
#include <pstade/singleton.hpp>
#include <pstade/to_type.hpp>


namespace pstade { namespace tomato {


namespace boolean_cast_detail {


    template< class To, class From >
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


template< class To, class From > inline
To boolean_cast(From from)
{
    typedef boolean_cast_detail::cvter<To, From> cvter_t;
    return cvter_t::cvt(from);
}


struct boolean_cast_fun :
    to_type_cast_result
{
    template< class From, class Type_To >
    typename to_type<Type_To>::type operator()(From const& from, Type_To) const
    {
        return tomato::boolean_cast<typename to_type<Type_To>::type>(from);
    }
};

PSTADE_SINGLETON_CONST(boolean_cast_fun, boolean_cast_)
PSTADE_PIPABLE(booleanized, boost::result_of<auto_castable_fun(boolean_cast_fun)>::type)


} } // namespace pstade::tomato


#endif
