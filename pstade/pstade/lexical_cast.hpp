#ifndef PSTADE_LEXICAL_CAST_HPP
#define PSTADE_LEXICAL_CAST_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://d.hatena.ne.jp/Cryolite/20061101


#include <boost/lexical_cast.hpp>
#include <pstade/auto_castable.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pipable.hpp>
#include <pstade/to_type.hpp>


namespace pstade {


    namespace lexical_cast_detail {

        struct baby
        {
            template< class Myself, class From, class To >
            struct apply :
                to_type<To>
            { };

            template< class Result, class From, class To >
            Result call(From const& from, To) const
            {
                return boost::lexical_cast<Result>(from);
            }
        };

    } // namespace lexical_cast_detail


    PSTADE_EGG_FUNCTION(lexical_cast, lexical_cast_detail::baby)


    PSTADE_AUTO_CASTABLE(lexical, lexical_cast_fun)
    PSTADE_PIPABLE(lexicalized, lexical_fun)


} // namespace pstade


#endif
