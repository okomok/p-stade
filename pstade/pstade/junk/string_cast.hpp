#ifndef PSTADE_STRING_CAST_HPP
#define PSTADE_STRING_CAST_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/lexical_cast.hpp>
#include <boost/optional.hpp>


namespace pstade {


// boost::optional<int> x = string_to<int>(str);

// throw ver.
// pstade::require(x);
// std::cout << *x;

// condition ver.
// if (!x)
//     std::cout << *x;


namespace string_cast_detail {


    template< class InputStreamable, class OutputStreamable >
    boost::optional<InputStreamable> aux(const OutputStreamable& src)
    {
        using namespace boost;

        typedef typename detail::array_to_pointer_decay<OutputStreamable>::type src_t;

        detail::lexical_stream<InputStreamable, src_t> interpreter;
        InputStreamable result;

        if (!(interpreter << arg && interpreter >> result))
            return boost::optional<InputStreamable>();

        return boost::optional<InputStreamable>(result);
    }


} // namespace string_cast_detail


template< class InputStreamable, class OutputStreamable > inline
boost::optional<InputStreamable> string_to(const OutputStreamable& src)
{
    return string_cast_detail::aux<InputStreamable>(src);
}


template< class InputStreamable, class OutputStreamable > inline
boost::optional<InputStreamable> to_string(const OutputStreamable& src)
{
    return string_cast_detail::aux<InputStreamable>(src);
}

} // namespace pstade


#endif
