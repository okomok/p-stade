#ifndef PSTADE_EGG_DETAIL_LEFT_INDICES_HPP
#define PSTADE_EGG_DETAIL_LEFT_INDICES_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/filter_view.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/protect.hpp>
#include <boost/mpl/range_c.hpp>
#include "../config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY


namespace pstade { namespace egg { namespace detail {


#if 0
    // manual protect
    template<class PartiallyIndexedArg>
    struct indexed_arg_has_index
    {
        struct type
        {
            template<class N>
            struct apply :
                boost::mpl::equal_to<N, typename PartiallyIndexedArg::index_type>
            { };
        };
    };
#endif


    template<class IndexedArg, class N>
    struct indexed_arg_has_index :
        boost::mpl::equal_to<N, typename IndexedArg::index_type>
    { };


    template<class PartiallyIndexedArgs>
    struct left_indices :
        boost::mpl::fold<
            PartiallyIndexedArgs,
            boost::mpl::range_c<int, 0, PSTADE_EGG_MAX_LINEAR_ARITY>,
            boost::mpl::filter_view<
                boost::mpl::_1,
                indexed_arg_has_index<boost::mpl::_2, boost::mpl::protect<boost::mpl::_1> >
            >
        >
    { };


    template<class X, class Y>
    struct lazy_pair
    {
        struct type {
            typedef typename X::type first_type;
            typedef typename Y::type second_type;
        }
    };


    template<class IndexArgs_LeftIndices, class MaybeIndexedArg>
    struct totally_indexed_state
    {
        typedef typename IndexArgs_LeftIndices::result_args_type result_args_t;
        typedef typename IndexArgs_LeftIndices::left_indices_type left_indices_t;

        typedef typename
            boost::mpl::eval_if< is_indexed<MaybeIndexedArg>,
                lazy_pair<
                    boost::mpl::push_back<result_args_t, MaybeIndexedArg>,
                    boost::mpl::indentity<left_indices_t>
                >,
                lazy_pair<
                    boost::mpl::push_back<result_args_t, typename index_noindex_arg<typename boost::mpl::front<left_indices_t>::type>::type>,
                    boost::mpl::pop_front<left_indices_t>
                >
            >::type
        type;
    };


    template<class PartiallyIndexedArgs>
    struct totally_indexed_args
    {
        struct initial_state_t
        {
            typedef boost::mpl::vector0<> result_args_type;
            typedef typename left_indices<PartiallyIndexedArgs>::type left_indices_type;
        };

        typedef typename
            boost::mpl::fold<
                PartiallyIndexedArgs,
                initial_state_t,
                op_t
            >::type::result_args_type
        type;
    };            


} } } // namespace pstade::egg::detail


#endif
