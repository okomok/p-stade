#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_DETAIL_LITTLE_FUSE_RESULT_HPP
#define BOOST_EGG_DETAIL_LITTLE_FUSE_RESULT_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_MAX_LINEAR_ARITY
#include <boost/egg/fusion/length.hpp>
#include <boost/egg/get.hpp>
#include <boost/egg/preprocessor/enum_params_with.hpp>
#include <boost/egg/preprocessor/int_n.hpp>
#include <boost/egg/result_of.hpp>
#include <boost/egg/detail/ignore_unused.hpp>


namespace boost { namespace egg { namespace details {


    template<class Base>
    struct little_fuse_result
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
            apply_aux<Tuple, typename fusion_length<Tuple>::type>
        { };

        template<class Re, class Tuple>
        Re call(Tuple &t) const
        {
            return call_aux<Re>(t, typename fusion_length<Tuple>::type());
        }

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_EGG_MAX_LINEAR_ARITY, <boost/egg/detail/little_fuse_result.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } } // namespace boost::egg::details


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Tuple>
    struct apply_aux< Tuple, mpl::int_<n> > :
        result_of_<
            Base const( BOOST_EGG_PP_ENUM_PARAMS_WITH(n, typename result_of_<X_get_c<BOOST_EGG_PP_INT_, >(Tuple &)>::type) )
        >
    { };

    template<class Re, class Tuple>
    Re call_aux(Tuple &t, mpl::int_<n>) const
    {
        BOOST_EGG_IGNORE_UNUSED(t); // when n == 0.
        return m_base( BOOST_EGG_PP_ENUM_PARAMS_WITH(n, X_get_c<BOOST_EGG_PP_INT_, >()(t)) );
    }


#undef  n
#endif
