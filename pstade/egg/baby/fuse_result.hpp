#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_BABY_FUSE_RESULT_HPP
#define PSTADE_EGG_BABY_FUSE_RESULT_HPP
#include "../detail/prefix.hpp"


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
#include "../detail/config.hpp" // PSTADE_EGG_FUSE_MAX_ARITY


namespace pstade { namespace egg { namespace baby {


    namespace fuse_result_detail {


        template<class Tuple>
        struct int_tuple_size :
            boost::mpl::int_<tuple_size<Tuple>::value>
        { };


        template<class Base, class Tuple, class Arity>
        struct apply_;

    // 0ary
        template<class Base, class Tuple>
        struct apply_< Base, Tuple, boost::mpl::int_<0> > :
            boost::result_of<
                PSTADE_DEFERRED(Base const)()
            >
        { };

        template<class Result, class Base, class Tuple> inline
        Result call_(Base& base, Tuple& tup, boost::mpl::int_<0>)
        {
            unused(tup);
            return base();
        }

    // 1ary-
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_FUSE_MAX_ARITY, <pstade/egg/baby/fuse_result.hpp>))
        #include BOOST_PP_ITERATE()


    } // namespace fuse_result_detail


    template<class Base>
    struct fuse_result
    {
        typedef Base base_type;

        Base m_base;

        Base base() const
        {
            return m_base;
        }

        template<class Myself, class Tuple>
        struct apply :
            fuse_result_detail::apply_<
                Base, Tuple, typename fuse_result_detail::int_tuple_size<Tuple>::type
            >
        { };

        template<class Result, class Tuple>
        Result call(Tuple& tup) const
        {
            return fuse_result_detail::call_<Result>(
                m_base, tup, typename fuse_result_detail::int_tuple_size<Tuple>::type()
            );
        }
    };


} } } // namespace pstade::egg::baby


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Base, class Tuple>
    struct apply_< Base, Tuple, boost::mpl::int_<n> > :
        boost::result_of<
            PSTADE_DEFERRED(Base const)(
                PSTADE_PP_ENUM_PARAMS_WITH(n, typename boost::result_of<op_tuple_get_c<PSTADE_PP_INT_, >(Tuple&)>::type)
            )
        >
    { };

    template<class Result, class Base, class Tuple> inline
    Result call_(Base& base, Tuple& tup, boost::mpl::int_<n>)
    {
        return base(
            PSTADE_PP_ENUM_PARAMS_WITH(n, op_tuple_get_c<PSTADE_PP_INT_, >()(tup))
        );
    }


#undef n
#endif
