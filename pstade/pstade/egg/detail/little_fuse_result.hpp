#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_LITTLE_FUSE_RESULT_HPP
#define PSTADE_EGG_DETAIL_LITTLE_FUSE_RESULT_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/int.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/tuple/tuple.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>
#include "../tuple/config.hpp"
#include "../tuple/get.hpp"
#include "../tuple/size.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class Tuple>
    struct int_tuple_size :
        boost::mpl::int_<tuple_size<Tuple>::value>
    { };


    template<class Base>
    struct little_fuse_result
    {
        typedef Base base_type;

        Base m_base;

        Base base() const
        {
            return m_base;
        }

        template<class Tuple, class Arity>
        struct apply_aux;

        template<class Myself, class Tuple>
        struct apply :
            apply_aux<Tuple, typename int_tuple_size<Tuple>::type>
        { };

        template<class Result, class Tuple>
        Result call(Tuple& tup) const
        {
            return call_aux<Result>(tup, typename int_tuple_size<Tuple>::type());
        }

    // 0ary
        template<class Tuple>
        struct apply_aux< Tuple, boost::mpl::int_<0> > :
            result_of<Base const()>
        { };

        template<class Result, class Tuple>
        Result call_aux(Tuple&, boost::mpl::int_<0>) const
        {
            return m_base();
        }

    // 1ary-
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_TUPLE_MAX_SIZE, <pstade/egg/detail/little_fuse_result.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Tuple>
    struct apply_aux< Tuple, boost::mpl::int_<n> > :
        result_of<
            Base const( PSTADE_PP_ENUM_PARAMS_WITH(n, typename result_of<X_tuple_get_c<PSTADE_PP_INT_, >(Tuple&)>::type) )
        >
    { };

    template<class Result, class Tuple>
    Result call_aux(Tuple& tup, boost::mpl::int_<n>) const
    {
        return m_base( PSTADE_PP_ENUM_PARAMS_WITH(n, X_tuple_get_c<PSTADE_PP_INT_, >()(tup)) );
    }


#undef n
#endif
