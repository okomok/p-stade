#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_FUSE_HPP
#define PSTADE_FUSE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/int.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/deferred.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/tuple.hpp>
#include <pstade/unused.hpp>


#if !defined(PSTADE_FUSE_MAX_ARITY)
    #define PSTADE_FUSE_MAX_ARITY 10 // follows 'boost::tuple' for now.
#endif


namespace pstade {


    namespace fuse_detail {


        using boost::mpl::int_;


        template<class Tuple>
        struct meta_size :
            int_<tuple_size<Tuple>::value>
        { };


        template<class Function, class Tuple, class Arity>
        struct apply_impl
        { }; // complete for SFINAE.


        // 0ary

        template<class Function, class Tuple>
        struct apply_impl< Function, Tuple, int_<0> > :
            boost::result_of<
                PSTADE_DEFERRED(Function const)()
            >
        { };

        template<class Result, class Function, class Tuple> inline
        Result call_impl(Function& fun, Tuple& seq, int_<0>)
        {
            unused(seq);
            return fun();
        }


        // 1ary-

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_FUSE_MAX_ARITY, <pstade/fuse.hpp>))
        #include BOOST_PP_ITERATE()


        template<class Function>
        struct return_op :
            callable< return_op<Function> >
        {
            template<class Myself, class Tuple>
            struct apply :
                apply_impl<Function, Tuple, typename meta_size<Tuple>::type>
            { };

            template<class Result, class Tuple>
            Result call(Tuple& seq) const
            {
                return fuse_detail::call_impl<Result>(m_fun, seq, typename meta_size<Tuple>::type());
            }

            explicit return_op()
            { }

            explicit return_op(Function fun) :
                m_fun(fun)
            { }

            typedef Function base_type;

            Function base() const
            {
                return m_fun;
            }

        private:
            Function m_fun;
        };


    } // namespace fuse_detail


    PSTADE_OBJECT_GENERATOR(fuse, (fuse_detail::return_op< deduce<_1, as_value> >))


} // namespace pstade


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
Result call_impl(Function& fun, Tuple& seq, int_<n>)
{
    return fun(
        PSTADE_PP_ENUM_PARAMS_WITH(n, op_tuple_get_c<PSTADE_PP_INT_, >()(seq))
    );
}


#undef n
#endif
