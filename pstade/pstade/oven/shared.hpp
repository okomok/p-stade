#ifndef PSTADE_OVEN_SHARED_HPP
#define PSTADE_OVEN_SHARED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/noncopyable.hpp>
#include <boost/pointee.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/provide_sig.hpp>
#include <pstade/to_shared_ptr.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace shared_detail {


    // The Range version of 'boost::shared_container_iterator'


    template< class Ptr >
    struct share_iterator;


    template< class Ptr >
    struct share_iterator_super
    {
        typedef typename
            boost::pointee<Ptr>::type
        rng_t;

        typedef
            boost::iterator_adaptor<
                share_iterator<Ptr>,
                typename range_iterator<rng_t>::type
            >
        type;
    };


    template< class Ptr >
    struct share_iterator :
        share_iterator_super<Ptr>::type
    {
    private:
        typedef typename share_iterator_super<Ptr>::type super_t;
        typedef typename super_t::base_type iter_t;

    public:
        share_iterator()
        { }

        share_iterator(iter_t it, Ptr prng) :
            super_t(it), m_prng(prng)
        { }

    template< class > friend struct share_iterator;
        template< class P >
        share_iterator(share_iterator<P> const& other,
            typename boost::enable_if_convertible<typename share_iterator<P>::iter_t, iter_t>::type * = 0,
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


} // namespace shared_detail


// 'callable/function' is useless here,
// because a temporary 'auto_ptr' is const-qualified
// then the ownership cannot be moved. So make it from scratch.


struct op_make_shared :
    provide_sig
{
    template< class Ptr >
    struct result_aux
    {
        typedef typename
            boost::result_of<op_to_shared_ptr(Ptr&)>::type
        sprng_t;

        typedef
            shared_detail::share_iterator<sprng_t>
        iter_t;

        typedef
            iter_range<iter_t> const
        type;
    };

    template< class Ptr >
    typename result_aux<Ptr>::type
    operator()(Ptr prng) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<typename boost::pointee<Ptr>::type>));

        typedef result_aux<Ptr> aux_;
        typename aux_::sprng_t sprng = to_shared_ptr(prng);
        return typename aux_::type(
            typename aux_::iter_t(boost::begin(*sprng), sprng),
            typename aux_::iter_t(boost::end(*sprng),   sprng)
        );
    }

    template< class FunCall >
    struct result;

    template< class Fun, class Ptr >
    struct result<Fun(Ptr)> :
        result_aux<typename pass_by_value<Ptr>::type>
    { };
};


PSTADE_CONSTANT(make_shared, (op_make_shared))


// A pipe must have its own namespace.
// The overload resolution falls into compile error
// while getting the result type; even if never called.
// See also "./joint_iterator.hpp"


namespace shared_detail_ {


    struct pipe :
        private boost::noncopyable
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
