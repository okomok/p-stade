#ifndef PSTADE_OVEN_COPY_RANGE_HPP
#define PSTADE_OVEN_COPY_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp> // BOOST_MSVC, BOOST_NESTED_TEMPLATE
#include <boost/utility/result_of.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/automatic.hpp>
#include <pstade/callable.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/functional.hpp> // identity
#include <pstade/pipable.hpp>
#include <pstade/remove_cvr.hpp>
#include "./concepts.hpp"
#include "./extension.hpp"
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
            op_make_transformed<ValueTo>(From&, op_identity const&)
        >::type call(From& from)
        {
            return op_make_transformed<ValueTo>()(from, identity);
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
    PSTADE_CONCEPT_ASSERT((SinglePass<To>));

    typedef To result_type;

    template< class From >
    To operator()(From const& from) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<From>));

        return pstade_oven_extension::Range<To>().BOOST_NESTED_TEMPLATE copy<To>(
            copy_range_detail::to_strictly_convertibles<
                typename remove_cvr<typename range_reference<From>::type>::type,
                typename range_value<To>::type
            >::call(from)
        );
    }

    // 'To' is sometimes the same as 'From', then easy to copy.
    To operator()(To const& from) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<From>));
        return from;
    }
};


PSTADE_ADL_BARRIER(copy_range) { // for Boost

template< class To, class From > inline
typename boost::result_of<op_copy_range<To>(PSTADE_DEDUCED_CONST(From)&)>::type
copy_range(From const& from)
{
    return op_copy_range<To>()(from);
}

} // ADL barrier


PSTADE_PIPABLE(copied, (automatic< op_copy_range<boost::mpl::_1> >))


} } // namespace pstade::oven


// Let 'boost::array' CopyableRange.
//


#include <cstddef> // size_t
#include <boost/array.hpp>
#include <boost/assert.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include "./detail/is_random_access.hpp"
#include "./distance.hpp"
#include "./range_iterator.hpp"


namespace pstade_oven_extension {


#if defined(BOOST_MSVC)
    #pragma warning(push)
    #pragma warning(disable: 4701) // potentially uninitialized local variable 'arr' used
#endif

    template< class T, std::size_t N, class From >
    boost::array<T, N> pstade_oven_(copy_range< boost::array<T, N> >, From& from)
    {
        using namespace pstade::oven;

        BOOST_ASSERT(detail::is_random_access(from) ?
            boost::numeric_cast<std::size_t>(distance(from)) <= N : true);

        typename range_iterator<From>::type
            it(boost::begin(from)), last(boost::end(from));
        boost::array<T, N> arr;
        std::size_t i = 0;

        for(; it != last; ++it, ++i)
            arr[i] = *it;
        for(; i != N; ++i)
            arr[i] = T();

        return arr; 
    }

#if defined(BOOST_MSVC)
    #pragma warning(pop)
#endif


} // namespace pstade_oven_extension


#endif
