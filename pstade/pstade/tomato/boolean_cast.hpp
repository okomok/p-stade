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


#include <boost/microsoft/sdk/windows.hpp>
#include <boost/microsoft/sdk/wtypes.hpp> // VARIANT_BOOL


namespace pstade { namespace tomato {


namespace boolean_cast_detail {


    template< class TargetT, class SourceT >
    struct cvter;


    #define PSTADE_TOMATO_BOOLEAN_CAST_cvter(TargetT, SourceT, Expr) \
        template< > \
        struct cvter<TargetT, SourceT> \
        { \
            static TargetT cvt(SourceT b) \
            { \
                return Expr; \
            } \
        }; \
    /**/


    #define PSTADE_TOMATO_BOOLEAN_CAST_cvter_set(TargeT, True, False) \
        PSTADE_TOMATO_BOOLEAN_CAST_cvter(TargeT, bool, b ? True : False) \
        PSTADE_TOMATO_BOOLEAN_CAST_cvter(TargeT, BOOL, b ? True : False) \
        PSTADE_TOMATO_BOOLEAN_CAST_cvter(TargeT, VARIANT_BOOL, b ? True : False) \
        PSTADE_TOMATO_BOOLEAN_CAST_cvter(TargeT, BOOLEAN, b ? True : False) \
        PSTADE_TOMATO_BOOLEAN_CAST_cvter(TargeT, LRESULT, b ? True : False) \
    /**/


    PSTADE_TOMATO_BOOLEAN_CAST_cvter_set(bool, true, false)
    PSTADE_TOMATO_BOOLEAN_CAST_cvter_set(BOOL, TRUE, FALSE)
    PSTADE_TOMATO_BOOLEAN_CAST_cvter_set(VARIANT_BOOL, VARIANT_TRUE, VARIANT_FALSE)
    PSTADE_TOMATO_BOOLEAN_CAST_cvter_set(BOOLEAN, (BOOLEAN)TRUE, (BOOLEAN)FALSE)
    PSTADE_TOMATO_BOOLEAN_CAST_cvter_set(LRESULT, 1, 0)


} // namespace boolean_cast_detail


template< class TargetT, class SourceT > inline const
TargetT boolean_cast(SourceT arg)
{
    typedef boolean_cast_detail::cvter<TargetT, SourceT> cvter_t;
    return cvter_t::cvt(arg);
}


namespace boolean_cast_detail {


    template< class SourceT >
    struct temp
    {
        explicit temp(SourceT b) :
            m_b(b)
        { }

        template< class TargetT >
        operator TargetT() const
        {
            return tomato::boolean_cast<TargetT>(m_b);
        }

    private:
        SourceT m_b;
    };


} // namespace boolean_cast_detail


template< class SourceT > inline const
boolean_cast_detail::temp<SourceT> boolean(SourceT b)
{
    return boolean_cast_detail::temp<SourceT>(b);
}

} } // namespace pstade::tomato


#endif
