#ifndef PSTADE_OVEN_DO_ITER_SWAP_HPP
#define PSTADE_OVEN_DO_ITER_SWAP_HPP
#include "./prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm> // swap
#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/constant.hpp>
#include "./detail/is_reference_iterator.hpp"
#include "./read.hpp"
#include "./write.hpp"


namespace pstade { namespace oven { namespace do_iter_swap_detail {


    namespace here = do_iter_swap_detail;


    template< class Iterator1, class Iterator2 >
    struct have_swappable_reference :
        boost::mpl::and_<
            detail::is_reference_iterator<Iterator1>,
            boost::is_same<
                typename boost::iterator_value<Iterator1>::type,
                typename boost::iterator_value<Iterator2>::type
            >
        >
    { };


    template< class Iterator1, class Iterator2 > inline
    void default_way_aux(Iterator1 it1, Iterator2 it2, boost::mpl::true_)
    {
#if BOOST_WORKAROUND(BOOST_MSVC, == 1310) // msvc-7.1
        using namespace std;
#else
        using std::swap;
#endif
        swap(*it1, *it2);
    }

    template< class Iterator1, class Iterator2 >
    void default_way_aux(Iterator1 it1, Iterator2 it2, boost::mpl::false_)
    {
        typename boost::iterator_value<Iterator1>::type tmp = read(it1);
        write(it1, read(it2));
        write(it2, tmp);
    }


    template< class Iterator1, class Iterator2 > inline
    void default_way(Iterator1 it1, Iterator2 it2)
    {
        here::default_way_aux(it1, it2, typename have_swappable_reference<Iterator1, Iterator2>::type());
    }


} } } // namespace pstade::oven::do_iter_swap_detail


namespace pstade_oven_extension {


    struct iter_swap { };
    struct iter_swap_base { };


    template< class Iterator1, class Iterator2 > inline
    void pstade_oven_(iter_swap_base, Iterator1 it1, Iterator2 it2)
    {
        pstade::oven::do_iter_swap_detail::default_way(it1, it2);
    }


    template< class Iterator1, class Iterator2 > inline
    void pstade_oven_(iter_swap, Iterator1 it1, Iterator2 it2)
    {
        pstade_oven_extension::pstade_oven_(iter_swap_base(), it1, it2);
    }


} // namespace pstade_oven_extension


namespace pstade { namespace oven {


    template< class Iterator1, class Iterator2 > inline
    void pstade_oven_iter_swap(Iterator1 it1, Iterator2 it2)
    {
        pstade_oven_(pstade_oven_extension::iter_swap(), it1, it2);
    }


    // Unless this is in the same namespace as above,
    // msvc-7.1 ADL randomly fails.

    struct op_do_iter_swap
    {
        typedef void result_type;

        template< class Iterator1, class Iterator2 >
        void operator()(Iterator1 it1, Iterator2 it2) const
        {
            pstade_oven_iter_swap(it1, it2);
        }
    };


    PSTADE_CONSTANT(do_iter_swap, (op_do_iter_swap))


} } // namespace pstade::oven


#endif
