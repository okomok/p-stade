#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_AUXILIARY0_HPP
#define PSTADE_EGG_AUXILIARY0_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2004/n1742.pdf


#include <boost/mpl/placeholders.hpp>
#include "./aggregate1.hpp"
#include "./deduce.hpp"
#include "./detail/baby_auxiliary0_result.hpp"
#include "./detail/config.hpp" // PSTADE_EGG_MAX_ARITY
#include "./function.hpp"
#include "./generator.hpp"
#include "./object.hpp"


namespace pstade { namespace egg {


    template<class Base>
    struct auxiliary0_result
    {
        typedef
            function< baby_auxiliary_result0<Base> >
        type;
    };


    #define PSTADE_AUXILIARY0_RESULT_INITIALIZER(B) \
        { { B } } \
    /**/


    typedef
        generator<
            auxiliary0_result< deduce<boost::mpl::_1, as_value> >::type
            aggregate1
        >::type
    op_auxiliary0;


    PSTADE_EGG_OBJECT((op_auxiliary0), auxiliary0) = PSTADE_EGG_GENERATOR_INITIALIZER();


} } // namespace pstade::egg


#endif
