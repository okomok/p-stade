#ifndef PSTADE_TOMATO_MULTIBYTE_TO_WIDECHAR_HPP
#define PSTADE_TOMATO_MULTIBYTE_TO_WIDECHAR_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <string>
#include <boost/utility/result_of.hpp>
#include <pstade/apple/atl/config.hpp> // ATL_VER
#include <pstade/apple/atl/conv.hpp>
#include <pstade/auto_castable.hpp>
#include <pstade/constant.hpp>
#include <pstade/oven/c_str_range.hpp>
#include <pstade/oven/copy_range.hpp>
#include <pstade/pipable.hpp>
#include <pstade/to_type.hpp>


namespace pstade { namespace tomato {


template< class WideCharSeq, class MultiByteRange >
WideCharSeq const
multibyte_to(MultiByteRange const& from)
{
    std::string tmp = from|oven::copied;

#if !(PSTADE_APPLE_ATL_VER < 0x0700)

    return ATL::CA2W(tmp.c_str()).operator LPWSTR()
        | oven::as_c_str
        | oven::copied;

#else

    USES_CONVERSION_EX;
    return A2W_EX(tmp.c_str(), 128)
        | oven::as_c_str
        | oven::copied;

#endif
}


struct op_multibyte_to :
    to_type_cast_result
{
    template< class From, class Type_To >
    typename to_type<Type_To>::type operator()(From const& from, Type_To) const
    {
        return tomato::multibyte_to<typename to_type<Type_To>::type>(from);
    }
};

PSTADE_CONSTANT(multibyte_to_, (op_multibyte_to))
PSTADE_PIPABLE(to_widechar, (boost::result_of<op_auto_castable(op_multibyte_to)>::type))


} } // namespace pstade::tomato


#endif
