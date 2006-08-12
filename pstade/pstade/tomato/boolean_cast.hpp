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


#include <pstade/apple/sdk/windows.hpp>
#include <pstade/apple/sdk/wtypes.hpp> // VARIANT_BOOL
#include <pstade/nonassignable.hpp>


namespace pstade { namespace tomato {


namespace boolean_cast_detail {


    template< class To, class From >
    struct cvter;


    #define PSTADE_TOMATO_BOOLEAN_CAST_cvter(To, From, Expr) \
        template< > \
        struct cvter<To, From> \
        { \
            static To cvt(From b) \
            { \
                return Expr; \
            } \
        }; \
    /**/


    #define PSTADE_TOMATO_BOOLEAN_CAST_cvter_set(To, True, False) \
        PSTADE_TOMATO_BOOLEAN_CAST_cvter(To, bool, b ? True : False) \
        PSTADE_TOMATO_BOOLEAN_CAST_cvter(To, BOOL, b ? True : False) \
        PSTADE_TOMATO_BOOLEAN_CAST_cvter(To, VARIANT_BOOL, b ? True : False) \
        PSTADE_TOMATO_BOOLEAN_CAST_cvter(To, BOOLEAN, b ? True : False) \
        PSTADE_TOMATO_BOOLEAN_CAST_cvter(To, LRESULT, b ? True : False) \
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
To boolean_cast(From arg)
{
    typedef boolean_cast_detail::cvter<To, From> cvter_t;
    return cvter_t::cvt(arg);
}


namespace boolean_cast_detail {


    template< class From >
    struct temp :
        private nonassignable
    {
        explicit temp(From b) :
            m_b(b)
        { }

        template< class To >
        operator To() const
        {
            return tomato::boolean_cast<To>(m_b);
        }

    private:
        From m_b;
    };


} // namespace boolean_cast_detail


template< class From > inline
boolean_cast_detail::temp<From> const
boolean(From b)
{
    return boolean_cast_detail::temp<From>(b);
}

} } // namespace pstade::tomato


#endif
