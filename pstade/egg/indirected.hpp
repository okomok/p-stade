#ifndef PSTADE_EGG_INDIRECTED_HPP
#define PSTADE_EGG_INDIRECTED_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// 'boost::indirect_iterator<>' is famous.
// This is intended as "indirect_function<>".
// See also 'boost::indirect_fun'.


#include <pstade/pod_constant.hpp>
#include "./detail/baby_indirected_result.hpp"
#include "./function.hpp"
#include "./generator.hpp"
#include "./use_brace_level1.hpp"


namespace pstade { namespace egg {


    template<class Dereferenceable>
    struct result_of_indirected
    {
        typedef function< detail::baby_indirected_result<Dereferenceable> > type;
    };


    #define PSTADE_EGG_INDIRECTED(B) \
        { { B() } } BOOST_PP_EMPTY \
    /**/


    typedef
        generator<
            result_of_indirected< deduce<boost::mpl::_1, as_value> >::type,
            use_brace_level1
        >::type
    op_indirected;


    PSTADE_POD_CONSTANT((op_indirected), indirected) = {{}};


} } // namespace pstade::egg


#endif
