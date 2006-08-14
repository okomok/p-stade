#ifndef PSTADE_TOMATO_BOOLEAN_CAST_HPP
#define PSTADE_TOMATO_BOOLEAN_CAST_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// boost::numeric_cast


#include <boost/type_traits/remove_cv.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/apple/sdk/wtypes.hpp> // VARIANT_BOOL
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipeline.hpp>
#include <pstade/nonassignable.hpp>


namespace pstade { namespace tomato {


namespace boolean_cast_detail {


    template< class To, class From >
    struct cvter;


    #define PSTADE_TOMATO_BOOLEAN_CAST_cvter(To, From, Expr) \
        template< > \
        struct cvter<To, From> \
        { \
            static To cvt(From from) \
            { \
                return Expr; \
            } \
        }; \
    /**/


    #define PSTADE_TOMATO_BOOLEAN_CAST_cvter_set(To, True, False) \
        PSTADE_TOMATO_BOOLEAN_CAST_cvter(To, bool, from ? True : False) \
        PSTADE_TOMATO_BOOLEAN_CAST_cvter(To, BOOL, from ? True : False) \
        PSTADE_TOMATO_BOOLEAN_CAST_cvter(To, VARIANT_BOOL, from ? True : False) \
        PSTADE_TOMATO_BOOLEAN_CAST_cvter(To, BOOLEAN, from ? True : False) \
        PSTADE_TOMATO_BOOLEAN_CAST_cvter(To, LRESULT, from ? True : False) \
    /**/


    PSTADE_TOMATO_BOOLEAN_CAST_cvter_set(bool, true, false)
    PSTADE_TOMATO_BOOLEAN_CAST_cvter_set(BOOL, TRUE, FALSE)
    PSTADE_TOMATO_BOOLEAN_CAST_cvter_set(VARIANT_BOOL, VARIANT_TRUE, VARIANT_FALSE)
    PSTADE_TOMATO_BOOLEAN_CAST_cvter_set(BOOLEAN, (BOOLEAN)TRUE, (BOOLEAN)FALSE)
    PSTADE_TOMATO_BOOLEAN_CAST_cvter_set(LRESULT, 1, 0)


    #undef PSTADE_TOMATO_BOOLEAN_CAST_cvter_set
    #undef PSTADE_TOMATO_BOOLEAN_CAST_cvter


} // namespace boolean_cast_detail


template< class To, class From > inline
To boolean_cast(From from)
{
    typedef boolean_cast_detail::cvter<To, From> cvter_t;
    return cvter_t::cvt(from);
}


namespace boolean_cast_detail {


    template< class From >
    struct temp :
        private nonassignable
    {
        explicit temp(From from) :
            m_from(from)
        { }

        template< class To >
        operator To() const
        {
            return tomato::boolean_cast<To>(m_from);
        }

    private:
        From m_from;
    };


    struct baby_boolean
    {
        template< class Unused, class From >
        struct result
        {
            typedef typename boost::remove_cv<From>::type from_t;
            typedef boolean_cast_detail::temp<from_t> const type;
        };

        template< class Result, class From >
        Result call(From from)
        {
            return Result(from);
        }
    };


} // namespace boolean_cast_detail


PSTADE_EGG_FUNCTION(boolean,     boolean_cast_detail::baby_boolean)
PSTADE_EGG_PIPELINE(booleanized, boolean_cast_detail::baby_boolean)


} } // namespace pstade::tomato


#endif
