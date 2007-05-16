#ifndef PSTADE_OVEN_SHARED_HPP
#define PSTADE_OVEN_SHARED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// References:
//
// [1] Ronald Garcia, shared_container_iterator, Boost.Utility, 2002.
//     http://www.boost.org/libs/utility/shared_container_iterator.html
// [2] Eric Niebler, BOOST_FOREACH, Boost.Foreach, 2004.
//     http://www.boost.org/regression-logs/cs-win32_metacomm/doc/html/foreach.html


#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/pointee.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable_by_value.hpp>
#include <pstade/constant.hpp>
#include <pstade/nonassignable.hpp>
#include <pstade/to_shared_ptr.hpp>
#include "./concepts.hpp"
#include "./do_iter_swap.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace shared_detail {


    // The Range version of 'boost::shared_container_iterator'


    template< class Ptr >
    struct shared_range_iterator;


    template< class Ptr >
    struct shared_range_iterator_super
    {
        typedef typename
            boost::pointee<Ptr>::type
        rng_t;

        typedef
            boost::iterator_adaptor<
                shared_range_iterator<Ptr>,
                typename range_iterator<rng_t>::type
            >
        type;
    };


    template< class Ptr >
    struct shared_range_iterator :
        shared_range_iterator_super<Ptr>::type
    {
    private:
        typedef typename shared_range_iterator_super<Ptr>::type super_t;
        typedef typename super_t::base_type iter_t;

    public:
        shared_range_iterator()
        { }

        shared_range_iterator(iter_t it, Ptr prng) :
            super_t(it), m_prng(prng)
        { }

    template< class > friend struct shared_range_iterator;
        template< class P >
        shared_range_iterator(shared_range_iterator<P> const& other,
            typename boost::enable_if_convertible<typename shared_range_iterator<P>::iter_t, iter_t>::type * = 0,
            typename boost::enable_if_convertible<
                // Use raw pointer type; 'boost::shared_ptr' convertibility is over-optimistic.
                typename boost::pointee<P>::type *, typename boost::pointee<Ptr>::type *
            >::type * = 0
        ) :
            super_t(other.base()), m_prng(other.m_prng)
        { }

        typename boost::pointee<Ptr>::type& base_range() const
        {
            return *m_prng;
        }

    private:
        Ptr m_prng;
    };


    template< class P > inline
    void iter_swap(shared_range_iterator<P> const& left, shared_range_iterator<P> const& right)
    {
        do_iter_swap(left.base(), right.base());
    }


} // namespace shared_detail


struct op_make_shared :
    callable_by_value<op_make_shared>
{
    template< class Myself, class Ptr >
    struct apply
    {
        typedef typename
            boost::result_of<op_to_shared_ptr(Ptr&)>::type
        sprng_t;

        typedef
            shared_detail::shared_range_iterator<sprng_t>
        iter_t;

        typedef
            iter_range<iter_t> const
        type;
    };

    template< class Result, class Ptr >
    Result call(Ptr prng) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<typename boost::pointee<Ptr>::type>));

        typedef typename Result::iterator iter_t;
        typename boost::result_of<op_to_shared_ptr(Ptr&)>::type sprng = to_shared_ptr(prng);
        return Result(
            iter_t(boost::begin(*sprng), sprng),
            iter_t(boost::end(*sprng),   sprng)
        );
    }
};


PSTADE_CONSTANT(make_shared, (op_make_shared))


// A pipe must have its own namespace.
// The overload resolution may fall into compile error,
// while getting the result type; even if never called.
// See also "./jointed.hpp".


namespace shared_detail_ {


    struct pipe :
        private pstade::nonassignable
    { };


    template< class Ptr > inline
    typename boost::result_of<op_make_shared(Ptr&)>::type
    operator|(Ptr prng, pipe)
    {
        return make_shared(prng);
    }


} // namespace shared_detail_


PSTADE_CONSTANT(shared, (shared_detail_::pipe))


} } // namespace pstade::oven


#endif
