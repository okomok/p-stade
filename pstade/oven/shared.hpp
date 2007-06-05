#ifndef PSTADE_OVEN_SHARED_HPP
#define PSTADE_OVEN_SHARED_HPP
#include "./prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable_by_value.hpp>
#include <pstade/constant.hpp>
#include <pstade/to_shared_ptr.hpp>
#include "./concepts.hpp"
#include "./detail/shared_range_iterator.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


struct op_shared :
    callable_by_value<op_shared>
{
    template< class Myself, class Ptr >
    struct apply
    {
        typedef typename
            boost::result_of<op_to_shared_ptr(Ptr&)>::type
        sprng_t;

        typedef
            detail::shared_range_iterator<sprng_t>
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


PSTADE_CONSTANT(shared, (op_shared))


} } // namespace pstade::oven


#endif
