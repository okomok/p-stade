#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_FUSE_RESULT_HPP
#define PSTADE_EGG_DETAIL_FUSE_RESULT_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/int.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/deferred.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/tuple.hpp>
#include <pstade/unused.hpp>


#if !defined(PSTADE_EGG_FUSE_MAX_ARITY)
    #define PSTADE_EGG_FUSE_MAX_ARITY 10 // follows 'boost::tuple'.
#endif


namespace pstade { namespace egg { namespace detail {


    template<class Tuple>
    struct tuple_meta_size :
        boost::mpl::int_<tuple_size<Tuple>::value>
    { };


    template<class Function, class Tuple, class Arity>
    struct fuse_result_apply;


    // 0ary

    template<class Function, class Tuple>
    struct fuse_result_apply< Function, Tuple, boost::mpl::int_<0> > :
        boost::result_of<
            PSTADE_DEFERRED(Function const)()
        >
    { };

    template<class Result, class Function, class Tuple> inline
    Result fuse_result_call(Function& fun, Tuple& tup, boost::mpl::int_<0>)
    {
        unused(tup);
        return fun();
    }


    // 1ary-

    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_FUSE_MAX_ARITY, <pstade/egg/detail/fuse_result.hpp>))
    #include BOOST_PP_ITERATE()


    template<class Function>
    struct fuse_result
    {
        Function m_function;

        template<class Myself, class Tuple>
        struct apply :
            fuse_result_apply<
                Function, Tuple, typename fused_detail::tuple_meta_size<Tuple>::type
            >
        { };

        template<class Result, class Tuple>
        Result call(Tuple& tup) const
        {
            return detail::fuse_result_call<Result>(
                m_function, tup, typename fused_detail::tuple_meta_size<Tuple>::type()
            );
        }
    };


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Function, class Tuple>
    struct fuse_result_apply< Function, Tuple, boost::mpl::int_<n> > :
        boost::result_of<
            PSTADE_DEFERRED(Function const)(
                PSTADE_PP_ENUM_PARAMS_WITH(n, typename boost::result_of<op_tuple_get_c<PSTADE_PP_INT_, >(Tuple&)>::type)
            )
        >
    { };

    template<class Result, class Function, class Tuple> inline
    Result fuse_result_call(Function& fun, Tuple& tup, boost::mpl::int_<n>)
    {
        return fun(
            PSTADE_PP_ENUM_PARAMS_WITH(n, op_tuple_get_c<PSTADE_PP_INT_, >()(tup))
        );
    }


#undef n
#endif
