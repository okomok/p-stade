#ifndef PSTADE_EGG_DETAIL_GET_ARG_HPP
#define PSTADE_EGG_DETAIL_GET_ARG_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/fusion/include/deref.hpp>
#include <boost/fusion/include/end.hpp>
#include <boost/fusion/include/find_if.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/int.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <pstade/unused.hpp>
#include "../function_facade.hpp"
#include "./default_value.hpp"
#include "./named_arg.hpp"
#include "./named_extension.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class Function, int Index>
    struct get_arg :
        function_facade< get_arg<Function, Index> >
    {
        struct is_this_index
        {
            template<class NamedArg>
            struct apply :
                boost::mpl::equal_to<
                    boost::mpl::int_<Index>,
                    typename keyword_to_index<Function, typename keyword_of<NamedArg>::type>::type
                >
            { };
        };

        template<bool NotFound, class Iter>
        struct get_ :
            make_default_value< Function, boost::mpl::int_<Index> >
        { };

        template<class Arg, class Iter>
        struct get_aux
        {
            typedef Arg& result_type;

            template<class PrecedingArgs>
            result_type operator()(Iter it, PrecedingArgs& pargs) const
            {
                unused(pargs);
                return boost::fusion::deref(it).m_arg;
            }
        };

        template<class Iter>
        struct get_aux<T_default_value const, Iter> :
            get_<true, Iter>
        { };

        template<class Iter>
        struct get_<false, Iter>
        {
            typedef typename boost::fusion::result_of::deref<Iter>::type ref_t;
            typedef typename boost::remove_reference<ref_t>::type named_arg_t;
            typedef typename named_arg_t::arg_type arg_t;
            typedef get_aux<arg_t, Iter> get_aux_t;
            typedef typename get_aux_t::result_type result_type;

            template<class PrecedingArgs>
            result_type operator()(Iter it, PrecedingArgs& pargs) const
            {
                return get_aux_t()(it, pargs);
            }
        };

        template<class Me, class NamedArgs, class PrecedingArgs>
        struct apply
        {
            typedef typename
                boost::fusion::result_of::find_if<NamedArgs, is_this_index>::type
            iter_t;

            typedef typename
                boost::fusion::result_of::end<NamedArgs>::type
            last_t;

            typedef
                get_<boost::is_same<iter_t, last_t>::value, iter_t>
            get_t;

            typedef typename
                get_t::result_type
            type;
        };

        template<class Re, class NamedArgs, class PrecedingArgs>
        Re call(NamedArgs& nargs, PrecedingArgs& pargs) const
        {
            typedef apply<void, NamedArgs, PrecedingArgs> apply_;

            typename apply_::iter_t it = boost::fusion::find_if<is_this_index>(nargs);
            return typename apply_::get_t()(it, pargs);
        }
    };


} } } // namespace pstade::egg::detail


#endif
