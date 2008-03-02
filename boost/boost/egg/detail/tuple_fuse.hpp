#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_DETAIL_TUPLE_FUSE_HPP
#define BOOST_EGG_DETAIL_TUPLE_FUSE_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/egg/by_cref.hpp>
#include <boost/egg/by_value.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_MAX_LINEAR_ARITY
#include <boost/egg/const.hpp>
#include <boost/egg/construct_braced2.hpp>
#include <boost/egg/generator.hpp>
#include <boost/egg/preprocessor/enum_params_with.hpp>
#include <boost/egg/preprocessor/int_n.hpp>
#include <boost/egg/result_of.hpp>
#include <boost/egg/detail/ignore_unused.hpp>
#include <boost/egg/detail/result_of_tuple_get.hpp>
#include <boost/egg/detail/tuple_length.hpp>


namespace boost { namespace egg { namespace details {


    template<class Base>
    struct little_tuple_fuse_result
    {
        Base m_base;

        Base const &base() const
        {
            return m_base;
        }

        template<class Tuple, class Arity>
        struct apply_aux;

        template<class Me, class Tuple>
        struct apply :
            apply_aux<Tuple, typename tuple_length<Tuple>::type>
        { };

        template<class Re, class Tuple>
        Re call(Tuple &t) const
        {
            return call_aux<Re>(t, typename tuple_length<Tuple>::type());
        }

    #define BOOST_EGG_result_of_get(Z, N, _) typename result_of_tuple_get<N, Tuple>::type
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_EGG_MAX_LINEAR_ARITY, <boost/egg/detail/tuple_fuse.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  BOOST_EGG_result_of_get
    };

    typedef
        generator<
            function<little_tuple_fuse_result< deduce<mpl::_1, as_value> >, by_cref>,
            by_value,
            X_construct_braced2<>
        >::type
    T_tuple_fuse;

    BOOST_EGG_CONST((T_tuple_fuse), tuple_fuse) = BOOST_EGG_GENERATOR();


} } } // namespace boost::egg::details


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Tuple>
    struct apply_aux< Tuple, mpl::int_<n> > :
        result_of_<
            Base const( BOOST_PP_ENUM(n, BOOST_EGG_result_of_get, ~) )
        >
    { };

    template<class Re, class Tuple>
    Re call_aux(Tuple &t, mpl::int_<n>) const
    {
        BOOST_EGG_IGNORE_UNUSED(t); // when n == 0.
        return m_base( BOOST_EGG_PP_ENUM_PARAMS_WITH(n, tuples::get<BOOST_EGG_PP_INT_, >(t)) );
    }


#undef  n
#endif
