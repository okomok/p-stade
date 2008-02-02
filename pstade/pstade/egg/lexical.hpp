#ifndef PSTADE_EGG_LEXICALIZE_HPP
#define PSTADE_EGG_LEXICALIZE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/lexical_cast.hpp>
#include <pstade/pod_constant.hpp>
#include "./ambi.hpp"
#include "./by_cref.hpp"
#include "./implicit.hpp"


namespace pstade { namespace egg {


    template<class To>
    struct X_lexical_cast
    {
        typedef To result_type;

        template<class From>
        To operator()(From const& from) const
        {
            return boost::lexical_cast<To>(from);
        }
    };

    typedef result_of_ambi0<implicit<X_lexical_cast<mpl_1>, by_cref>::type, by_cref>::type T_lexical;
    PSTADE_POD_CONSTANT((T_lexical), lexical) = PSTADE_EGG_AMBI_L PSTADE_EGG_IMPLICIT() PSTADE_EGG_AMBI_R;


} } // namespace pstade::egg


#endif
