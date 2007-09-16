#ifndef PSTADE_EGG_DETAIL_KEYWORD_HPP
#define PSTADE_EGG_DETAIL_KEYWORD_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/indexed_arg.hpp"


namespace pstade { namespace egg {


    template<class Keyword, class Base>
    struct keyword_to_index_tag
    {
        typedef void type;
    };

    template<class Keyword, class Base, class EnableIf>
    struct keyword_to_index_base
    {
        typedef typename Keyword::index_type type;
    };

    template<class Keyword, class Base, class Tag = typename keyword_to_index_tag<Keyword, Base>::type>
    struct keyword_to_index :
        keyword_to_index<Keyword, Base, enabler>
    { };


    struct error_named_parameter_requires_argument;




    namespace detail {


        struct unnamed_tag;



        template<class Tuple>
        struct left_indices;


        template<class NamedArg, class ArgTuple>
        struct get_arg
        {
            typedef typename
                result_of<typename NamedArg::make_default_type(ArgTuple&>::type
            result_type;

            result_type operator()(NamedArg& a, ArgTuple& args) cosnt
            {
                return a.m_make(args);
            }


    } // namespace detail


    template<int N, class Tag = void>
    struct keyword
    {
        typedef boost::mpl::int_<N> index_type;
        typedef Tag tag_type;

        template<class A>
        detail::named_arg<keyword, A&> const
        operator=(A& a, typename disable_if_copy_assign<keyword, A>::type = 0) const
        {
            detail::named_arg<keyword, boost::mpl::int_<N>, A&> r = {a};
            return r;
        }

        template<class A>
        detail::named_arg<keyword, PSTADE_DEDUCED_CONST(A)&> const
        operator=(A const& a) const
        {
            detail::named_arg<keyword, PSTADE_DEDUCED_CONST(A)&> r = {a};
            return r;
        }
    };


} } // namespace pstade::egg


#endif
