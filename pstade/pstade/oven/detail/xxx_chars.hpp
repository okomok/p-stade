#ifndef PSTADE_OVEN_DETAIL_XXX_CHARS_HPP
#define PSTADE_OVEN_DETAIL_XXX_CHARS_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <locale>
#include <pstade/egg/make_function.hpp>
#include <pstade/result_of.hpp>
#include "../concepts.hpp"
#include "../range_value.hpp"
#include "../transformed.hpp"


namespace pstade { namespace oven { namespace detail {


template< class BinaryFun, class CharT >
struct to_xxx_char
{
    typedef typename
        result_of<
            BinaryFun const(CharT&, std::locale const&)
        >::type
    result_type;

    result_type operator()(CharT ch) const
    {
        return BinaryFun()(ch, m_loc);
    }

    explicit to_xxx_char()
    { }

    explicit to_xxx_char(std::locale const& loc) :
        m_loc(loc)
    { }

private:
    std::locale m_loc;
};


template< class BinaryFun >
struct xxx_chars
{
    struct baby
    {
        template< class Myself, class Range, class Locale = std::locale const >
        struct apply :
            result_of<
                op_make_transformed(
                    Range&,
                    to_xxx_char<BinaryFun, typename range_value<Range>::type>
                )
            >
        { };

        template< class Result, class Range >
        Result call(Range& rng, std::locale const& loc) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

            return make_transformed(
                rng,
                to_xxx_char<BinaryFun, typename range_value<Range>::type>(loc)
            );
        }

        template< class Result, class Range >
        Result call(Range& rng) const
        {
            return egg::make_function(*this)(rng, std::locale());
        }
    };
};


} } } // namespace pstade::oven::detail


#endif
