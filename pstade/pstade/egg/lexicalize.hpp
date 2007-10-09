#ifndef PSTADE_EGG_LEXICALIZE_HPP
#define PSTADE_EGG_LEXICALIZE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./automatic.hpp"
#include "./auxiliary.hpp"
#include "./lexical_cast.hpp"


namespace pstade { namespace egg {


    namespace lexicalize_detail {

        typedef automatic< X_lexical_cast<boost::mpl::_1> >::type op;

    }


    typedef result_of_auxiliary0<lexicalize_detail::op>::type T_lexicalize;
    PSTADE_POD_CONSTANT((T_lexicalize), lexicalize) = PSTADE_EGG_AUXILIARY_L PSTADE_EGG_AUTOMATIC PSTADE_EGG_AUXILIARY_R;


} } // namespace pstade::egg


#endif
