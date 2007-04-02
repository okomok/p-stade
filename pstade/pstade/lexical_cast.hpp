#ifndef PSTADE_LEXICAL_CAST_HPP
#define PSTADE_LEXICAL_CAST_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <string>
#include <boost/lexical_cast.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/automatic.hpp>
#include <pstade/auxiliary.hpp>
#include <pstade/specified.hpp>


namespace pstade {


    template<class To>
    struct op_lexical_cast
    {
        typedef To result_type;

        template<class From>
        To operator()(From const& from) const
        {
            return boost::lexical_cast<To>(from);
        }
    };


PSTADE_ADL_BARRIER(lexical_cast) { // for 'boost'
    PSTADE_SPECIFIED1(lexical_cast, op_lexical_cast, 1)
}
    PSTADE_AUXILIARY(0, lexicalized, (automatic< op_lexical_cast<_> >))


    PSTADE_AUXILIARY(0, to_string, (op_lexical_cast<std::string>))
    PSTADE_AUXILIARY(0, to_wstring, (op_lexical_cast<std::wstring>))


} // namespace pstade


#endif
