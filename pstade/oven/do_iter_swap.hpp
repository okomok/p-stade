#ifndef PSTADE_OVEN_DO_ITER_SWAP_HPP
#define PSTADE_OVEN_DO_ITER_SWAP_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_traits.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/egg/do_swap.hpp>
#include <pstade/pod_constant.hpp>
#include "./detail/is_reference_iterator.hpp"
#include "./read.hpp"
#include "./write.hpp"


namespace pstade { namespace oven {


namespace do_iter_swap_detail {


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
    void aux(Iterator1 it1, Iterator2 it2, boost::mpl::true_)
    {
        egg::do_swap(*it1, *it2);
    }

    template< class Iterator1, class Iterator2 >
    void aux(Iterator1 it1, Iterator2 it2, boost::mpl::false_)
    {
        typename boost::iterator_value<Iterator1>::type tmp = read(it1);
        write(it1, read(it2));
        write(it2, tmp);
    }


    // If these aren't in the same namespace,
    // msvc-7.1 ADL randomly fails.

    template< class Iterator1, class Iterator2 > inline
    void iter_swap(Iterator1 it1, Iterator2 it2, int)
    {
        here::aux(it1, it2, typename have_swappable_reference<Iterator1, Iterator2>::type());
    }

    struct op
    {
        typedef void result_type;

        template< class Iterator1, class Iterator2 >
        void operator()(Iterator1 it1, Iterator2 it2) const
        {
            // As 'std::iter_swap' implementation is wrong, we have to replace it.
            // But, if assocated namespaces of iterator contains 'std',
            // 'iter_swap' above and 'std::iter_swap' would be ambiguous without a dummy int.
            iter_swap(it1, it2, 0);
        }
    };


} // namespace do_iter_swap_detail


typedef do_iter_swap_detail::op op_do_iter_swap;
PSTADE_POD_CONSTANT((op_do_iter_swap), do_iter_swap) = {};


} } // namespace pstade::oven


#endif
