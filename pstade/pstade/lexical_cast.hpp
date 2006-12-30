#ifndef PSTADE_LEXICAL_CAST_HPP
#define PSTADE_LEXICAL_CAST_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/lexical_cast.hpp>
#include <pstade/automatic.hpp>
#include <pstade/pipable.hpp>


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


    PSTADE_PIPABLE(lexicalized, (automatic<op_lexical_cast<boost::mpl::_1> >))


} // namespace pstade


#endif
