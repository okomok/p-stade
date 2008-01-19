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
#include "./automatic.hpp"
#include "./by_cref.hpp"


namespace pstade { namespace egg {


    template<class To>
    struct X_lexical_cast
    {
        typedef X_lexical_cast function_type;
        typedef by_cref strategy_type;

        typedef To result_type;

        template<class From>
        To operator()(From const& from) const
        {
            return boost::lexical_cast<To>(from);
        }
    };

#if 0
PSTADE_ADL_BARRIER(lexical_cast) { // for boost

    template<class To, class From> inline
    To lexical_cast(From const& from)
    {
        return X_lexical_cast<To>()(from);
    }

}
#endif


    typedef result_of_ambi0<automatic< X_lexical_cast<mpl_1> >::type, by_cref>::type T_lexical;
    PSTADE_POD_CONSTANT((T_lexical), lexical) = PSTADE_EGG_AMBI_L PSTADE_EGG_AUTOMATIC() PSTADE_EGG_AMBI_R;


} } // namespace pstade::egg


#endif
