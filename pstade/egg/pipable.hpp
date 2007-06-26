#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_PIPABLE_HPP
#define PSTADE_EGG_PIPABLE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Port of: adaptor_base at Boost.RangeEx
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// You may say preprocessors could be removed by using
// the way shown at "./compose.hpp".
// But such implementation is not as small as the following.
// Also, we must know the exact type passed to 'operator|'.


#include <boost/mpl/bool.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/unparenthesize.hpp>
#include "./apply_params.hpp"
#include "./callable.hpp"
#include "./fuse.hpp"
#include "./nullary_result_of.hpp"
#include "./object.hpp"
#include "./object_generator.hpp"


namespace pstade { namespace egg {


    namespace pipable_detail {


        template< class Function, class ArgTuple = boost::tuples::tuple<> >
        struct pipe :
            callable<pipe<Function, ArgTuple>, pipe<Function, ArgTuple> const&>
        {
            template<class Myself, PSTADE_EGG_APPLY_PARAMS(A)>
            struct apply
            { };

            // 0ary
            template<class Result>
            Result call() const
            {
                return *this;
            }

            // 1ary-
            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_ARITY, <pstade/egg/pipable.hpp>))
            #include BOOST_PP_ITERATE()

            explicit pipe()
            { }

            explicit pipe(Function fun, ArgTuple const& args = ArgTuple()) :
                m_fun(fun), m_args(args)
            { }

            typedef Function base_type;
            typedef ArgTuple arguments_type;

            Function base() const
            {
                return m_fun;
            }

            ArgTuple const& arg_tuple() const
            {
                return m_args;
            }

        private:
            Function m_fun;
            ArgTuple m_args;

            pipe& operator=(pipe const&);
        };


        template<class ArgTuple, class A> inline
        boost::tuples::cons<A&, ArgTuple>
        push_front(ArgTuple const& args, A& a)
        {
            return boost::tuples::cons<A&, ArgTuple>(a, args);
        }


        template<class A, class Function, class ArgTuple>
        struct result_of_output :
            boost::result_of<
                typename boost::result_of<op_fuse(Function const&)>::type(boost::tuples::cons<A&, ArgTuple>)
            >
        { };


        template<class A, class Function, class ArgTuple> inline
        typename result_of_output<A, Function, ArgTuple>::type
        operator|(A& a, pipe<Function, ArgTuple> const& pi)
        {
            return fuse(pi.base())(pipable_detail::push_front(pi.arg_tuple(), a));
        }

        template<class A, class Function, class ArgTuple> inline
        typename result_of_output<PSTADE_DEDUCED_CONST(A), Function, ArgTuple>::type
        operator|(A const& a, pipe<Function, ArgTuple> const& pi)
        {
            return fuse(pi.base())(pipable_detail::push_front(pi.arg_tuple(), a));
        }


    } // namespace pipable_detail


    PSTADE_EGG_OBJECT_GENERATOR(pipable, (pipable_detail::pipe< deduce<_1, as_value> >))


    #define PSTADE_EGG_PIPABLE(O, F) \
        namespace BOOST_PP_CAT(pstade_egg_pipable_workarea_of_, O) { \
            using namespace boost::mpl::placeholders; \
            typedef boost::result_of<pstade::egg::op_pipable(PSTADE_UNPARENTHESIZE(F))>::type pipe; \
        } \
        PSTADE_EGG_OBJECT(O, (BOOST_PP_CAT(pstade_egg_pipable_workarea_of_, O)::pipe)) \
    /**/


} } // namespace pstade::egg


PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE(pstade::egg::pipable_detail::pipe, 2)


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)>
    {
        typedef
            pipe< Function, boost::tuples::tuple<PSTADE_PP_ENUM_PARAMS_WITH(n, A, &)> >
        type;
    };

    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return Result(m_fun, typename Result::arguments_type(BOOST_PP_ENUM_PARAMS(n, a)));
    }


#undef n
#endif
