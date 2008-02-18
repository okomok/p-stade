

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PP_IS_ITERATING


    #ifndef BOOST_EGG_PLACEHOLDERS_HPP
    #define BOOST_EGG_PLACEHOLDERS_HPP
    #include <boost/egg/detail/prefix.hpp>


    #include <boost/preprocessor/cat.hpp>
    #include <boost/preprocessor/iteration/iterate.hpp>
    #include <boost/egg/arg.hpp>
    #include <boost/egg/config.hpp> // BOOST_EGG_MAX_LINEAR_ARITY
    #include <boost/egg/const.hpp>


    namespace boost { namespace egg {


        #define BOOST_EGG_PLACEHOLDER BOOST_EGG_ARG_INIT


        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_EGG_MAX_LINEAR_ARITY, <boost/egg/placeholders.hpp>))
        #include BOOST_PP_ITERATE()


    } } // namespace boost::egg


    #include <boost/egg/detail/suffix.hpp>
    #endif // BOOST_EGG_PLACEHOLDERS_HPP


#else


    #define n BOOST_PP_ITERATION()


        namespace placeholders {
            typedef X_arg< n >::base_class BOOST_PP_CAT(TT_, n);
            BOOST_EGG_CONST((BOOST_PP_CAT(TT_, n)), BOOST_PP_CAT(_, n)) = BOOST_EGG_PLACEHOLDER;
        }


    #undef  n


#endif
