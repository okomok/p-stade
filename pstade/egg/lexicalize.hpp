#ifndef PSTADE_EGG_LEXICALIZE_HPP
#define PSTADE_EGG_LEXICALIZE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/placeholders.hpp>
#include "./automatic.hpp"
#include "./auxiliary.hpp"
#include "./lexical_cast.hpp"
#include "./object.hpp"


namespace pstade { namespace egg {


    namespace lexicalize_detail {

        typedef automatic< xp_lexical_cast<boost::mpl::_1> >::type op;

    }


    typedef result_of_auxiliary0<lexicalize_detail::op>::type op_lexicalize;
    PSTADE_EGG_OBJECT((op_lexicalize), lexicalize) = PSTADE_EGG_AUXILIARY_RESULT_INITIALIZER(PSTADE_EGG_AUTOMATIC_INITIALIZER);


} } // namespace pstade::egg


#endif
