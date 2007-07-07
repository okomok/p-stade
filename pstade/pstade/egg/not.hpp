#ifndef PSTADE_EGG_NOT_HPP
#define PSTADE_EGG_NOT_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/placeholders.hpp>
#include <pstade/pod_constant.hpp>
#include "./deduce.hpp"
#include "./detail/baby_not_result.hpp"
#include "./function.hpp"
#include "./generator.hpp"
#include "./use_brace_level1.hpp"


namespace pstade { namespace egg {


    template<class Base>
    struct result_of_not_
    {
        typedef
            function< detail::baby_not_result<Base> >
        type; // = { { Base } };
    };


    #define PSTADE_EGG_NOT_RESULT_INITIALIZER(B) \
        { { B() } } \
    /**/


    typedef
        generator<
            result_of_not_< deduce<boost::mpl::_1, as_value> >::type,
            use_brace_level1
        >::type
    op_not_;


    PSTADE_POD_CONSTANT((op_not_), not_) = PSTADE_EGG_GENERATOR_INITIALIZER();


} } // namespace pstade::egg


#endif
