#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_TUPLE_FUSE_HPP
#define PSTADE_EGG_DETAIL_TUPLE_FUSE_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>
#include "../by_cref.hpp"
#include "../by_value.hpp"
#include "../config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY
#include "../construct_braced2.hpp"
#include "../generator.hpp"
#include "./result_of_tuple_get.hpp"
#include "./tuple_length.hpp"


namespace pstade { namespace egg { namespace detail {


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

    #define PSTADE_result_of_get(Z, N, _) typename result_of_tuple_get<N, Tuple>::type
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/detail/tuple_fuse.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_result_of_get
    };

    typedef
        generator<
            function<little_tuple_fuse_result< deduce<mpl_1, as_value> >, by_cref>,
            by_value,
            X_construct_braced2<>
        >::type
    T_tuple_fuse;

    PSTADE_POD_CONSTANT((T_tuple_fuse), tuple_fuse) = PSTADE_EGG_GENERATOR();


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Tuple>
    struct apply_aux< Tuple, boost::mpl::int_<n> > :
        result_of<
            Base const( BOOST_PP_ENUM(n, PSTADE_result_of_get, ~) )
        >
    { };

    template<class Re, class Tuple>
    Re call_aux(Tuple &t, boost::mpl::int_<n>) const
    {
        (void)t; // for n == 0.
        return m_base( PSTADE_PP_ENUM_PARAMS_WITH(n, boost::tuples::get<PSTADE_PP_INT_, >(t)) );
    }


#undef  n
#endif
