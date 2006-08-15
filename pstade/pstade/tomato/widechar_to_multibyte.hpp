#ifndef PSTADE_TOMATO_WIDECHAR_TO_MULTIBYTE_HPP
#define PSTADE_TOMATO_WIDECHAR_TO_MULTIBYTE_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <string>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/apple/atl/config.hpp> // ATL_VER
#include <pstade/apple/atl/conv.hpp>
#include <pstade/egg/pipeline.hpp>
#include <pstade/nonassignable.hpp>
#include <pstade/oven/copy_range.hpp>
#include <pstade/oven/null_terminate_range.hpp>


namespace pstade { namespace tomato {


template< class MultiByteSeq, class WideCharRange >
MultiByteSeq widechar_to(WideCharRange const& from)
{
    std::wstring tmp = from|oven::copied;

#if !(PSTADE_APPLE_ATL_VER < 0x0700)

    return ATL::CW2A(tmp.c_str()).operator LPSTR()
        | oven::null_terminated
        | oven::copied;

#else

    USES_CONVERSION_EX;
    return W2A_EX(tmp.c_str(), 128)
        | oven::null_terminated
        | oven::copied;

#endif
}


namespace to_multibyte_detail {


    template< class WideCharRange >
    struct temp :
        private nonassignable
    {
        explicit temp(WideCharRange const& from) :
            m_from(from)
        { }

        template< class MultiByteSeq >
        operator MultiByteSeq() const
        {
            return tomato::widechar_to<MultiByteSeq>(m_from);
        }

    private:
        WideCharRange const& m_from;
    };


    struct baby
    {
        template< class Unused, class WideCharRange >
        struct result
        {
            typedef typename boost::remove_cv<WideCharRange>::type rng_t;
            typedef temp<rng_t> const type;
        };

        template< class Result, class WideCharRange >
        Result call(WideCharRange const& rng)
        {
            return Result(rng);
        }
    };


} // namespace to_multibyte_detail


PSTADE_EGG_PIPELINE(to_multibyte, to_multibyte_detail::baby)


} } // namespace pstade::tomato


#endif
