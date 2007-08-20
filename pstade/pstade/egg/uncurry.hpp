#ifndef PSTADE_EGG_UNCURRY_HPP
#define PSTADE_EGG_UNCURRY_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/facilities/empty.hpp>
#include <pstade/pod_constant.hpp>
#include "./detail/baby_uncurry_result.hpp"
#include "./function.hpp"
#include "./generator.hpp"
#include "./use_brace_level1.hpp"


namespace pstade { namespace egg {


    template<class Base>
    struct result_of_uncurry
    {
        typedef function< detail::baby_uncurry_result<Base> > type;
    };


    #define PSTADE_EGG_UNCURRY(B) \
        { { B() } } BOOST_PP_EMPTY \
    /**/


    typedef
        generator<
            result_of_uncurry< deduce<boost::mpl::_1, as_value> >::type,
            use_brace_level1
        >::type
    op_uncurry;


    PSTADE_POD_CONSTANT((op_uncurry), uncurry) = {{}};


} } // namespace pstade::egg


#endif
