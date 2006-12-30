#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_FUSE_HPP
#define PSTADE_FUSE_HPP


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
#include <boost/utility/result_of.hpp>
#include <pstade/affect.hpp>
#include <pstade/at.hpp>
#include <pstade/callable1.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/remove_cvr.hpp>
#include <pstade/unused.hpp>


namespace pstade {


    namespace fuse_detail {


        using boost::mpl::int_;


        template< class Tuple >
        struct result_of_size :
            int_<
                boost::tuples::length<
                    typename remove_cvr<Tuple>::type // Boost.Tuple needs this.
                >::value
            >
        { };


        template< class Function, class FusionSeq, class Arity >
        struct apply_impl;


        // 0ary

        template< class Function, class FusionSeq >
        struct apply_impl< Function, FusionSeq, int_<0> > :
            boost::result_of< Function(
            ) >
        { };

        template< class Result, class Function, class FusionSeq >
        Result call_impl(Function fun, FusionSeq& seq, int_<0>)
        {
            pstade::unused(seq);
            return fun(
            );
        }


        // 1ary

        template< class Function, class FusionSeq >
        struct apply_impl< Function, FusionSeq, int_<1> > :
            boost::result_of< Function(
                typename boost::result_of<op_at< int_<0> >(FusionSeq&)>::type
            ) >
        { };

        template< class Result, class Function, class FusionSeq >
        Result call_impl(Function fun, FusionSeq& seq, int_<1>)
        {
            return fun(
                pstade::at< int_<0> >(seq)
            );
        }


        // 2ary-

    #define PSTADE_max_arity 10
    #define PSTADE_result_of_at_c(Z, N, _) typename boost::result_of< op_at< int_<N> >(FusionSeq&)>::type
    #define PSTADE_at_c(Z, N, _)           pstade::at< int_<N> >(seq)
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_max_arity, <pstade/fuse.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_at_c
    #undef  PSTADE_result_of_at_c
    #undef  PSTADE_max_arity


        template< class Function >
        struct op_result :
            callable1< op_result<Function> >
        {
            template< class Myself, class FusionSeq >
            struct apply
            {
                typedef typename result_of_size<FusionSeq>::type n_t;
                typedef typename apply_impl<Function, FusionSeq, n_t>::type type;
            };

            template< class Result, class FusionSeq >
            Result call(FusionSeq& seq) const
            {
                typedef typename result_of_size<FusionSeq>::type n_t;
                return fuse_detail::call_impl<Result>(m_fun, seq, n_t());
            }

            explicit op_result() // for ForwardIterator
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


    } // namespace fuse_detail


    PSTADE_OBJECT_GENERATOR(fuse, (fuse_detail::op_result< deduce<_1, to_value> >))


} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


template< class Function, class FusionSeq >
struct apply_impl< Function, FusionSeq, int_< n > > :
    boost::result_of< Function(
        BOOST_PP_ENUM(n, PSTADE_result_of_at_c, ~)
    ) >
{ };

template< class Result, class Function, class FusionSeq >
Result call_impl(Function fun, FusionSeq& seq, int_< n >)
{
    return fun(
        BOOST_PP_ENUM(n, PSTADE_at_c, ~)
    );
}


#undef n
#endif
