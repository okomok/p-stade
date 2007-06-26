#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_FUSE_HPP
#define PSTADE_EGG_FUSE_HPP
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
#include <pstade/pod_constant.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/tuple.hpp>
#include <pstade/unused.hpp>
#include "./aggregate1.hpp"
#include "./callable.hpp"
#include "./object_generator.hpp"


#if !defined(PSTADE_EGG_FUSE_MAX_ARITY)
    #define PSTADE_EGG_FUSE_MAX_ARITY 10 // follows 'boost::tuple'.
#endif


namespace pstade { namespace egg {


    namespace fuse_detail {


        namespace here = fuse_detail;


        using boost::mpl::int_;


        template<class Tuple>
        struct meta_size :
            int_<tuple_size<Tuple>::value>
        { };


        template<class Function, class Tuple, class Arity>
        struct apply_impl;


        // 0ary

        template<class Function, class Tuple>
        struct apply_impl< Function, Tuple, int_<0> > :
            boost::result_of<
                PSTADE_DEFERRED(Function const)()
            >
        { };

        template<class Result, class Function, class Tuple> inline
        Result call_impl(Function& fun, Tuple& tup, int_<0>)
        {
            unused(tup);
            return fun();
        }


        // 1ary-

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_FUSE_MAX_ARITY, <pstade/egg/fuse.hpp>))
        #include BOOST_PP_ITERATE()


        template<class Function>
        struct baby_return_op
        {
            Function m_fun;

            template<class Myself, class Tuple>
            struct apply :
                apply_impl<Function, Tuple, typename meta_size<Tuple>::type>
            { };

            template<class Result, class Tuple>
            Result call(Tuple& tup) const
            {
                return here::call_impl<Result>(m_fun, tup, typename meta_size<Tuple>::type());
            }

            typedef Function base_type;

            Function base() const
            {
                return m_fun;
            }
        };


        using namespace object_generator_helpers;

        typedef
            object_generator<
                callable< baby_return_op< deduce<_1, as_value> > >,
                aggregate1
            >::type
        op;


    } // namespace fuse_detail


    typedef fuse_detail::op op_fuse;
    PSTADE_POD_CONSTANT(fuse, (op_fuse))


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Function, class Tuple>
    struct apply_impl< Function, Tuple, int_<n> > :
        boost::result_of<
            PSTADE_DEFERRED(Function const)(
                PSTADE_PP_ENUM_PARAMS_WITH(n, typename boost::result_of<op_tuple_get_c<PSTADE_PP_INT_, >(Tuple&)>::type)
            )
        >
    { };

    template<class Result, class Function, class Tuple> inline
    Result call_impl(Function& fun, Tuple& tup, int_<n>)
    {
        return fun(
            PSTADE_PP_ENUM_PARAMS_WITH(n, op_tuple_get_c<PSTADE_PP_INT_, >()(tup))
        );
    }


#undef n
#endif
