#ifndef PSTADE_GRAVY_HANDLE_CAST_HPP
#define PSTADE_GRAVY_HANDLE_CAST_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade { namespace gravy {


    template<class To, class From> inline
    To handle_cast(From from)
    {
        return (To)from;
    }


} } // namespace pstade::gravy


#endif
