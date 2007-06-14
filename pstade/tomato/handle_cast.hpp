#ifndef PSTADE_TOMATO_HANDLE_CAST_HPP
#define PSTADE_TOMATO_HANDLE_CAST_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade { namespace tomato {


    template<class To, class From> inline
    To handle_cast(From from)
    {
        return (To)from;
    }


} } // namespace pstade::tomato


#endif
