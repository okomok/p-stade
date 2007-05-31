#ifndef PSTADE_OVEN_DO_ITER_SWAP_HPP
#define PSTADE_OVEN_DO_ITER_SWAP_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/prelude.hpp"
#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <pstade/constant.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, == 1310) // msvc-7.1
    // For some reason, ADL randomly fails without this.
    namespace boost {
        struct pstade_oven_do_iter_swap_dummy_type;
        void iter_swap(pstade_oven_do_iter_swap_dummy_type, pstade_oven_do_iter_swap_dummy_type);
    }
#endif


namespace pstade { namespace oven {


namespace do_iter_swap_detail {


    // Sigh... msvc STL calls 'std::swap'.
    template< class Iterator >
    void iter_swap(Iterator left, Iterator right)
    {
        typename boost::iterator_value<Iterator>::type tmp = *left;
        *left = *right;
        *right = tmp;
    }


} // namespace do_iter_swap_detail


struct op_do_iter_swap
{
    typedef void result_type;

    template< class Iterator >
    void operator()(Iterator left, Iterator right) const
    {
#if BOOST_WORKAROUND(BOOST_MSVC, == 1310) // msvc-7.1
        using boost::iter_swap;
#endif
        using do_iter_swap_detail::iter_swap;
        iter_swap(left, right);
    }
};


PSTADE_CONSTANT(do_iter_swap, (op_do_iter_swap))


} } // namespace pstade::oven


#endif
