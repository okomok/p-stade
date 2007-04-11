#ifndef PSTADE_OVEN_IDENTITIES_HPP
#define PSTADE_OVEN_IDENTITIES_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/mpl/assert.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/dont_care.hpp>
#include <pstade/is_convertible.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include <pstade/use_default.hpp>
#include <pstade/value_cast.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_difference.hpp"
#include "./range_iterator.hpp"
#include "./range_traversal.hpp"
#include "./traversal_tags.hpp" // inclusion guaranteed


namespace pstade { namespace oven {


namespace identities_detail {


    template< class Iterator, class Traversal, class Difference >
    struct identity_iterator;


    template< class Iterator, class Traversal, class Difference >
    struct identity_iterator_super
    {
        typedef
            boost::iterator_adaptor<
                identity_iterator<Iterator, Traversal, Difference>,
                Iterator,
                boost::use_default,
                Traversal,
                boost::use_default,
                Difference
            >
        type;
    };


    template< class Iterator, class Traversal, class Difference >
    struct identity_iterator :
        identity_iterator_super<Iterator, Traversal, Difference>::type
    {
    private:
        typedef typename identity_iterator_super<Iterator, Traversal, Difference>::type super_t;
        typedef typename super_t::difference_type diff_t;

    public:
        explicit identity_iterator()
        { }

        explicit identity_iterator(Iterator const& it, dont_care = 0, dont_care = 0) :
            super_t(it)
        { }

        template< class I, class T, class D >
        identity_iterator(identity_iterator<I, T, D> const& other,
            typename boost::enable_if_convertible<I, Iterator>::type * = 0
        ) :
            super_t(other.base())
        { }

    friend class boost::iterator_core_access;
        template< class I, class T, class D >
        diff_t distance_to(identity_iterator<I, T, D> const& other) const
        {
            return pstade::value_cast<diff_t>(other.base() - this->base());
        }
    };


} // namespace identities_detail


template< class Difference = boost::use_default >
struct op_make_identities :
    callable< op_make_identities<Difference> >
{
    template< class Myself, class Range, class Traversal = boost::use_default >
    struct apply
    {
        typedef typename
            use_default_eval_to<
                typename pass_by_value<Traversal>::type,
                range_pure_traversal<Range>
            >::type
        trv_t;

        typedef typename
            use_default_eval_to<
                Difference,
                range_difference<Range>
            >::type
        diff_t;

        typedef
            identities_detail::identity_iterator<
                typename range_iterator<Range>::type,
                trv_t,
                diff_t
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        type;
    };

    template< class Result, class Range >
    Result call(Range& rng, dont_care = 0) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
        BOOST_MPL_ASSERT((is_convertible<
            typename range_traversal<Range>::type,
            typename range_pure_traversal<Result>::type>
        ));

        return Result(rng);
    }
};


PSTADE_CONSTANT(make_identities, (op_make_identities<>))
PSTADE_PIPABLE(identities, (op_make_identities<>))


} } // namespace pstade::oven


#endif
