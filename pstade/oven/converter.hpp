#ifndef PSTADE_OVEN_CONVERTER_HPP
#define PSTADE_OVEN_CONVERTER_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/by_value.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/egg/specified.hpp>
#include <pstade/result_of.hpp>
#include "./concepts.hpp"
#include "./transformer.hpp"


namespace pstade { namespace oven {


namespace converter_detail {


    template< class To >
    struct func
    {
        typedef To result_type;

        To operator()(To v) const
        {
            return v;
        }
    };


    template< class To >
    struct baby
    {
        template< class Myself, class Iterator >
        struct apply :
            result_of<
                T_make_transformer(Iterator&, func<To>)
            >
        { };

        template< class Result, class Iterator >
        Result call(Iterator it) const
        {
            PSTADE_CONCEPT_ASSERT((Output<Iterator>));
            return make_transformer(it, func<To>());
        }
    };


    template< class To >
    struct pod_
    {
        typedef egg::function<baby<To>, egg::by_value> type;
    };


} // namespace converter_detail


template< class To >
struct X_make_converter :
    converter_detail::pod_<To>::type
{
    typedef typename converter_detail::pod_<To>::type pod_type;
};


PSTADE_EGG_SPECIFIED1(make_converter, X_make_converter, (class))


template< class To >
struct converter :
    egg::result_of_pipable< X_make_converter<To> >::type,
    egg::lookup_pipable_operator
{ };


} } // namespace pstade::oven


#endif
