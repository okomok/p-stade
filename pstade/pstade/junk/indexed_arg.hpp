#ifndef PSTADE_EGG_DETAIL_INDEXED_ARG_HPP
#define PSTADE_EGG_DETAIL_INDEXED_ARG_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/type_traits/remove_cv.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/pod_constant.hpp>
#include "../function.hpp"
#include "./default_value.hpp"


namespace pstade_egg_extension {


    struct use_default_index
    {
        template<class X, class Keyword>
        struct index :
            Keyword::index_type
        { };
    };


    template<class Function>
    struct Parameter;
#if 0
    {
        template<class X, class Args, int Index>
        struct default_;

        template<class X, class Args>
        struct default_<X, Args, 0>
        {
            typedef int result_type;

            result_type operator()(Args args) cosnt
            {
                return 120;
            }
        };

        template<class X, class Keyword>
        struct index;

        template<class X>
        struct index<X, _width>
        {
            typedef boost::mpl::int_<3> type;
        };
    };
#endif


} // namespace pstade_egg_extension


namespace pstade { namespace egg { namespace detail {


    typedef boost::mpl::int_<-1> noindex_tag;


    template<class Base, class ArgTuple, class N>
    struct default_value
    {
        typedef typename pass_by_value<Base>::type base_t;
        typedef pstade_egg_extension::Parameter<base_t> ext_t;
        typedef ext_t::template default_<base_t, ArgTuple&, N::value> fun_type;
        typedef typename fun_type::result_type type;
    };


    template<class Base, class Keyword>
    struct keyword_to_index
    {
        typedef typename pass_by_value<Base>::type base_t;
        typedef pstade_egg_extension::Parameter<base_t> ext_t;
        typedef typename ext_t::template index<base_t, Keyword>::type type;
    };


    template<int I>
    struct xp_find_argument :
        function_facade< xp_find_argument<I> >
    {
        struct is_same_index
        {
            template<class IndexedArg>
            struct apply :
                boost::mpl::equal_to<
                    boost::mpl::int_<I>,
                    typename keyword_to_index<typename IndexedArg::keyword_type>::type
            { };
        };

        template<class Myself, class ArgTuple>
        struct apply :
            boost::fusion::result_of::find_if<ArgTuple, is_same_index>
        { };

        template<class Myself, class ArgTuple>
        Result call(ArgTuple& args) const
        {
            return boost::fusion::find_if<is_same_index>(args);
        }
    };


    template<class Keyword, class Arg>
    struct indexed_arg
    {
        typedef Keyword keyword_type;
        typedef Arg argument_type;

        Arg m_arg;

        typedef Arg result_type;

        template<class Base, class ArgTuple>
        result_type operator()(Base&, ArgTuple&) const
        {
            return m_arg;
        };
    };


    template<class N, class Arg>
    struct indexed_arg<N, use_default_arg_type const&> :
        function_facade< indexed_arg<N, use_default_arg_type const&> >
    {
        template<class Myself, class Base, class ArgTuple>
        struct apply :
            default_value<Base, ArgTuple, N>
        { };

        template<class Result, class Base, class ArgTuple>
        Result call(Base&, ArgTuple& args) const
        {
            return typename default_value<Base, ArgTuple, N>::fun_type()(args);
        }

    private:
        Arg m_arg;
    };


    template<class X>
    struct is_indexed_arg_aux :
        boost::mpl::false_
    { };

    template<class N, class A, class MakeValue>
    struct is_indexed_arg_aux< indexed_arg<N, A, MakeValue> > :
        boost::mpl::true_
    { };

    template<class X>
    struct is_indexed_arg :
        is_indexed_arg_aux<typename boost::remove_cv<X>::type>
    { };


    struct baby_to_indexed_arg
    {
        template<class Myself, class A>
        struct apply :
            boost::mpl::if_< is_indexed_arg<A>,
                A,
                indexed_arg< noindex_tag, A&, default_value<A&> >
            >
        { };

        template<class Result, class A>
        Result to_indexed_arg(A& a, typename disable_if<is_indexed_arg<A> >::type = 0) const
        {
            indexed_arg< noindex_tag, A&, default_value<A&> > r = {a, {}};
            return r;
        }

        template<class Result, class A>
        Result to_indexed_arg(A& a, typename enable_if< is_indexed_arg<A> >::type = 0) const
        {
            return a;
        }
    };

    typedef function<baby_to_indexed_arg> op_to_indexed_arg;
    PSTADE_POD_CONSTANT((op_to_indexed_arg), to_indexed_arg) = {{}};


    template<class Tuple, class LeftIndices>
    struct index


} } } // namespace pstade::egg::detail


#endif
