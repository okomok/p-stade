#ifndef PSTADE_OVEN_COPY_RANGE_HPP
#define PSTADE_OVEN_COPY_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp> // BOOST_MSVC, BOOST_NESTED_TEMPLATE
#include <boost/type_traits/remove_const.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/automatic.hpp>
#include <pstade/callable.hpp>
#include <pstade/copy_construct.hpp>
#include <pstade/pipable.hpp>
#include <pstade/remove_cvr.hpp>
#include <pstade/specified.hpp>
#include <pstade/unevaluated.hpp>
#include "./concepts.hpp"
#include "./extension.hpp"
#include "./identities.hpp"
#include "./range_reference.hpp"
#include "./range_value.hpp"
#include "./transformed.hpp"


namespace pstade { namespace oven {


namespace copy_range_detail {


    // Force copy-initialization to disambiguate overload-resolution;
    // Standard seems not to guarantee that range-constructor of
    // Sequence is copy-initialization. GCC actually triggers
    // direct-initialization, hence the overload-resolution may fail
    // if 'ValueFrom' has a template conversion operator.
    template< class ValueFrom, class ValueTo >
    struct to_strictly_convertibles
    {
        template< class From >
        static typename boost::result_of<
            op_make_transformed<>(From&, op_copy_construct<ValueTo>)
        >::type call(From& from)
        {
            return make_transformed(from, op_copy_construct<ValueTo>());
        }
    };


    template< class ValueTo >
    struct to_strictly_convertibles<ValueTo, ValueTo>
    {
        template< class From >
        static From& call(From& from)
        {
            return from;
        }
    };


} // namespace copy_range_detail


template< class To >
struct op_copy_range
{
    typedef To result_type;

    template< class From >
    To operator()(From const& from) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<To>));
        PSTADE_CONCEPT_ASSERT((SinglePass<From>));

        return pstade_oven_extension::Range<To>().BOOST_NESTED_TEMPLATE copy<To>(
            copy_range_detail::to_strictly_convertibles<
                typename remove_cvr<typename range_reference<From>::type>::type,
                typename range_value<To>::type
            >::call(from)
        );
    }

    // 'To' is sometimes the same as 'From', then easy to copy.
    // Ideally, 'is_convertible' should kick in, but many types
    // don't or cannot correctly implement the convertibility.
    To operator()(To const& from) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<To>));
        return from;
    }
};


PSTADE_ADL_BARRIER(copy_range) { // for 'boost'
    PSTADE_SPECIFIED1(copy_range, op_copy_range, 1)
}
PSTADE_PIPABLE(copied, (automatic< op_copy_range<_> >))


template< class Range >
struct Copyable :
    SinglePass<Range>
{
    typedef typename boost::remove_const<Range>::type rng_t;

    PSTADE_CONCEPT_USAGE(Copyable)
    {
        rng_t& from = unevaluated<rng_t&>();
        rng_t rng = op_copy_range<rng_t>()(make_identities(from)); 
    }
};


} } // namespace pstade::oven


// Let 'boost::array' CopyableRange.
//


#include <cstddef> // size_t
#include <boost/array.hpp>
#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/integral_cast.hpp>
#include "./distance.hpp"
#include "./range_iterator.hpp"
#include "./traversal_tags.hpp" // is_random_access


namespace pstade_oven_extension {


#if defined(BOOST_MSVC)
    #pragma warning(push)
    #pragma warning(disable: 4701) // potentially uninitialized local variable 'arr' used
#endif

    template< class T, std::size_t N, class From >
    boost::array<T, N> pstade_oven_(copy_range< boost::array<T, N> >, From& from)
    {
        using namespace pstade::oven;

        BOOST_ASSERT(is_random_access(from) ?
            pstade::integral_cast<std::size_t>(distance(from)) <= N : true);

        typename range_iterator<From>::type
            it(boost::begin(from)), last(boost::end(from));
        boost::array<T, N> arr;
        std::size_t i = 0;

        for (; it != last; ++it, ++i)
            arr[i] = *it;
        for (; i != N; ++i)
            arr[i] = T();

        return arr; 
    }

#if defined(BOOST_MSVC)
    #pragma warning(pop)
#endif


} // namespace pstade_oven_extension


#endif
