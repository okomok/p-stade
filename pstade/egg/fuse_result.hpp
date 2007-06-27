#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_FUSE_RESULT_HPP
#define PSTADE_EGG_FUSE_RESULT_HPP
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


namespace pstade { namespace egg {


    namespace fuse_result_detail {


        using boost::mpl::int_;


        template<class Tuple>
        struct meta_size :
            int_<tuple_size<Tuple>::value>
        { };


        template<class Function, class Tuple, class Arity>
        struct apply_;


        // 0ary

        template<class Function, class Tuple>
        struct apply_< Function, Tuple, int_<0> > :
            boost::result_of<
                PSTADE_DEFERRED(Function const)()
            >
        { };

        template<class Result, class Function, class Tuple> inline
        Result call_(Function& fun, Tuple& tup, int_<0>)
        {
            unused(tup);
            return fun();
        }


        // 1ary-

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_FUSE_MAX_ARITY, <pstade/egg/fuse_result.hpp>))
        #include BOOST_PP_ITERATE()


    } // namespace fuse_result_detail


    template<class Function>
    struct fuse_result
    {
        Function m_function;

        typedef Function base_type;

        Function base() const
        {
            return m_function;
        }

        template<class Myself, class Tuple>
        struct apply :
            fuse_result_detail::apply_<
                Function, Tuple, typename fuse_result_detail::meta_size<Tuple>::type
            >
        { };

        template<class Result, class Tuple>
        Result call(Tuple& tup) const
        {
            return fuse_result_detail::call_<Result>(
                m_function, tup, typename fuse_result_detail::meta_size<Tuple>::type()
            );
        }
    };


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Function, class Tuple>
    struct apply_< Function, Tuple, int_<n> > :
        boost::result_of<
            PSTADE_DEFERRED(Function const)(
                PSTADE_PP_ENUM_PARAMS_WITH(n, typename boost::result_of<op_tuple_get_c<PSTADE_PP_INT_, >(Tuple&)>::type)
            )
        >
    { };

    template<class Result, class Function, class Tuple> inline
    Result call_(Function& fun, Tuple& tup, int_<n>)
    {
        return fun(
            PSTADE_PP_ENUM_PARAMS_WITH(n, op_tuple_get_c<PSTADE_PP_INT_, >()(tup))
        );
    }


#undef n
#endif
