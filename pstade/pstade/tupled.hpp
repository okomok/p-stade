#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_TUPLED_HPP
#define PSTADE_TUPLED_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/int.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/affect.hpp>
#include <pstade/callable.hpp>
#include <pstade/object_generator.hpp>


namespace pstade {


    namespace tupled_detail {


        template< class Tuple, int N >
        struct result_of_get :
            affect_cvr<
                Tuple&,
                typename boost::tuples::element<N, Tuple>::type
            >
        { };


        template< class Function, class Tuple, class Arity >
        struct apply_impl;


        // 0ary

        template< class Function, class Tuple >
        struct apply_impl< Function, Tuple, boost::mpl::int_<0> > :
            boost::result_of<
                Function(
                )
            >
        { };

        template< class Result, class Function, class Tuple >
        Result call_impl(Function fun, Tuple& tup, boost::mpl::int_<0>)
        {
            return
                fun(
                );
        }


        // 1ary

        template< class Function, class Tuple >
        struct apply_impl< Function, Tuple, boost::mpl::int_<1> > :
            boost::result_of<
                Function(
                    typename result_of_get<Tuple, 0>::type
                )
            >
        { };

        template< class Result, class Function, class Tuple >
        Result call_impl(Function fun, Tuple& tup, boost::mpl::int_<1>)
        {
            return
                fun(
                    boost::tuples::get<0>(tup)
                );
        }


        // 2ary-

    #define PSTADE_max_arity 10
    #define PSTADE_result_of_get(Z, N, _) typename result_of_get< Tuple, N >::type
    #define PSTADE_get(Z, N, _) boost::tuples::get< N >(tup)
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_max_arity, <pstade/tupled.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_get
    #undef  PSTADE_result_of_get
    #undef  PSTADE_max_arity


        template< class Function >
        struct op_result :
            callable< op_result<Function> >
        {
            template< class Myself, class Tuple >
            struct apply
            {
                typedef typename boost::remove_cv<Tuple>::type tup_t; // 'tuples::length' doesn't know 'const'!
                typedef boost::mpl::int_<boost::tuples::length<tup_t>::value> n_t;
                typedef typename apply_impl<Function, Tuple, n_t>::type type;
            };

            template< class Result, class Tuple >
            Result call(Tuple& tup) const
            {
                typedef typename boost::remove_cv<Tuple>::type tup_t;
                typedef boost::mpl::int_<boost::tuples::length<tup_t>::value> n_t;
                return tupled_detail::call_impl<Result>(m_fun, tup, n_t());
            }

            explicit op_result() // DefaultConstructible iff 'Function' is.
            { }

            explicit op_result(Function const& fun) :
                m_fun(fun)
            { }

            typedef Function base_type;

            Function const& base()
            {
                return m_fun;
            }

        private:
            Function m_fun;
        };


    } // namespace tupled_detail


    PSTADE_OBJECT_GENERATOR(tupled, tupled_detail::op_result)


} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


template< class Function, class Tuple >
struct apply_impl< Function, Tuple, boost::mpl::int_< n > > :
    boost::result_of<
        Function(
            BOOST_PP_ENUM(n, PSTADE_result_of_get, ~)
        )
    >
{ };

template< class Result, class Function, class Tuple >
Result call_impl(Function fun, Tuple& tup, boost::mpl::int_< n >)
{
    return
        fun(
            BOOST_PP_ENUM(n, PSTADE_get, ~)
        );
}


#undef n
#endif
