#ifndef PSTADE_GRAVY_RGB_HPP
#define PSTADE_GRAVY_RGB_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Converts something like '#11AAFF' to 'COLORREF'.
// A 'wchar_t' is casted to 'char'. Take care.


#include <iomanip> // hex
#include <locale>
#include <sstream> // istringstream
#include <string>
#include <boost/cstdint.hpp> // uint32_t
#include <boost/optional/optional.hpp>
#include <pstade/constant.hpp>
#include <pstade/oven/copy_range.hpp>
#include <pstade/oven/dropped.hpp>
#include "./sdk/windows.hpp"


namespace pstade { namespace gravy {


    struct op_rgb
    {
        typedef
            boost::optional<COLORREF> const
        result_type;

        template<class CharRange>
        result_type operator()(CharRange const& rng) const
        {
            if (boost::empty(rng))
                return result_type();

            // See:
            // http://groups.google.com/group/comp.lang.c++.moderated/msg/3a2bbe7be45a9d80
            // http://d.hatena.ne.jp/y-hamigaki/20061017

            std::string tmp = rng|oven::dropped(1)|oven::copied;
            std::istringstream is(tmp);
            is.imbue(std::locale::classic());

            boost::uint32_t n;
            if (!(is >> std::hex >> n))
                return result_type();

            boost::uint32_t r = (n & 0xFF0000) >> 16;
            boost::uint32_t g = (n & 0xFF00) >> 8;
            boost::uint32_t b = (n & 0xFF);
            return result_type(RGB(r, g, b));
        }
    };


    PSTADE_CONSTANT(rgb, (op_rgb))


} } // namespace pstade::gravy


#endif
