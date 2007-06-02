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
#include "./read.hpp"
#include "./write.hpp"


namespace pstade { namespace oven {


#if !BOOST_WORKAROUND(BOOST_MSVC, == 1310) // not msvc-7.1
namespace do_iter_swap_detail {
#endif

    // Sigh... msvc STL calls 'std::swap'.
    template< class ReadableIter >
    void iter_swap(ReadableIter left, ReadableIter right)
    {
        typename boost::iterator_value<ReadableIter>::type tmp = read(left);
        write(left, read(right)); // 'write(left, *right)' would call the copy-assignment of proxy.
        write(right, tmp);
    }

#if !BOOST_WORKAROUND(BOOST_MSVC, == 1310) // not msvc-7.1
} // namespace do_iter_swap_detail
#endif


struct op_do_iter_swap
{
    typedef void result_type;

    template< class Iterator >
    void operator()(Iterator left, Iterator right) const
    {
#if !BOOST_WORKAROUND(BOOST_MSVC, == 1310) // not msvc-7.1
        using do_iter_swap_detail::iter_swap;
#endif
        iter_swap(left, right);
    }
};


PSTADE_CONSTANT(do_iter_swap, (op_do_iter_swap))


} } // namespace pstade::oven


#endif
