#ifndef PSTADE_EGG_LEXICAL_CAST_HPP
#define PSTADE_EGG_LEXICAL_CAST_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/lexical_cast.hpp>
#include <pstade/adl_barrier.hpp>


namespace pstade { namespace egg {


    template<class To>
    struct X_lexical_cast
    {
        typedef X_lexical_cast function_type;
        typedef To result_type;

        template<class From>
        To operator()(From const& from) const
        {
            return boost::lexical_cast<To>(from);
        }
    };


PSTADE_ADL_BARRIER(lexical_cast) { // for boost

    template<class To, class From> inline
    To lexical_cast(From const& from)
    {
        return X_lexical_cast<To>()(from);
    }

}


} } // namespace pstade::egg


#endif
