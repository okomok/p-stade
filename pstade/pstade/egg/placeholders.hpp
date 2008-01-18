

// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PP_IS_ITERATING


    #ifndef PSTADE_EGG_PLACEHOLDERS_HPP
    #define PSTADE_EGG_PLACEHOLDERS_HPP
    #include "./detail/prefix.hpp"


    #include <boost/preprocessor/cat.hpp>
    #include <boost/preprocessor/iteration/iterate.hpp>
    #include <pstade/pod_constant.hpp>
    #include "./arg.hpp"
    #include "./config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY


    namespace pstade { namespace egg {


        #define PSTADE_EGG_PLACEHOLDER PSTADE_EGG_ARG_INIT


        // 1ary-
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/placeholders.hpp>))
        #include BOOST_PP_ITERATE()


    } } // namespace pstade::egg


    #endif // PSTADE_EGG_PLACEHOLDERS_HPP


#else


    #define n BOOST_PP_ITERATION()


        namespace placeholders {
            typedef X_arg< n >::function_type BOOST_PP_CAT(TT_, n);
            PSTADE_POD_CONSTANT((BOOST_PP_CAT(TT_, n)), BOOST_PP_CAT(_, n)) = PSTADE_EGG_PLACEHOLDER;
        }


    #undef  n


#endif
