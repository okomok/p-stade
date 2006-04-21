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
#include <boost/mpl/identity.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/oven/range_adaptor.hpp>


namespace pstade { namespace tomato {


template< class TargetT, class SourceT >
struct boolean_cast_converter;


#define PSTADE_TOMATO_BOOLEAN_CAST_converter(TargetT, SourceT, Expr) \
    template< > \
    struct boolean_cast_converter<TargetT, SourceT> \
    { \
        static TargetT convert(SourceT b) \
        { \
            return Expr; \
        } \
    }; \
/**/


#define PSTADE_TOMATO_BOOLEAN_CAST_converter_set(TargeT, True, False) \
    PSTADE_TOMATO_BOOLEAN_CAST_converter(TargeT, bool, b ? True : False) \
    PSTADE_TOMATO_BOOLEAN_CAST_converter(TargeT, BOOL, b ? True : False) \
    PSTADE_TOMATO_BOOLEAN_CAST_converter(TargeT, VARIANT_BOOL, b ? True : False) \
    PSTADE_TOMATO_BOOLEAN_CAST_converter(TargeT, BOOLEAN, b ? True : False) \
    PSTADE_TOMATO_BOOLEAN_CAST_converter(TargeT, LRESULT, b ? True : False) \
/**/


PSTADE_TOMATO_BOOLEAN_CAST_converter_set(bool, true, false)
PSTADE_TOMATO_BOOLEAN_CAST_converter_set(BOOL, TRUE, FALSE)
PSTADE_TOMATO_BOOLEAN_CAST_converter_set(VARIANT_BOOL, VARIANT_TRUE, VARIANT_FALSE)
PSTADE_TOMATO_BOOLEAN_CAST_converter_set(BOOLEAN, (BOOLEAN)TRUE, (BOOLEAN)FALSE)
PSTADE_TOMATO_BOOLEAN_CAST_converter_set(LRESULT, 1, 0)


template< class TargetT, class SourceT > inline const
TargetT boolean_cast(SourceT arg)
{
    typedef boolean_cast_converter<TargetT, SourceT> converter_t;
    return converter_t::convert(arg);
}


namespace boolean_cast_detail {


    template< class SourceT >
    struct temporary
    {
        explicit temporary(SourceT b) :
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
boolean_cast_detail::temporary<SourceT> boolean(SourceT b)
{
    return boolean_cast_detail::temporary<SourceT>(b);
}

} } // namespace pstade::tomato


#endif
