#ifndef PSTADE_BISCUIT_PARSER_PRIMITIVE_ICHAR_HPP
#define PSTADE_BISCUIT_PARSER_PRIMITIVE_ICHAR_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/and.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/less_equal.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/eval_if.hpp>
#include "../orn.hpp"
#include "./char.hpp"


namespace pstade { namespace biscuit {


namespace ichar_detail {


    template< char ch >
    struct is_lower :
        boost::mpl::and_<
            boost::mpl::less_equal<
                boost::mpl::integral_c<char, 'a'>,
                boost::mpl::integral_c<char, ch>
            >,
            boost::mpl::less_equal<
                boost::mpl::integral_c<char, ch>,
                boost::mpl::integral_c<char, 'z'>
            >
        >
    { };


    template< char ch >
    struct is_upper :
        boost::mpl::and_<
            boost::mpl::less_equal<
                boost::mpl::integral_c<char, 'A'>,
                boost::mpl::integral_c<char, ch>
            >,
            boost::mpl::less_equal<
                boost::mpl::integral_c<char, ch>,
                boost::mpl::integral_c<char, 'Z'>
            >
        >
    { };


    template< char ch >
    struct to_lower :
        boost::mpl::eval_if< is_upper<ch>,
            boost::mpl::plus<
                boost::mpl::minus<
                    boost::mpl::integral_c<char, ch>,
                    boost::mpl::integral_c<char, 'A'>
                >,
                boost::mpl::integral_c<char, 'a'>
            >,
            boost::mpl::integral_c<char, ch>
        >::type
    { };


    template< char ch >
    struct to_upper :
        boost::mpl::eval_if< is_lower<ch>,
            boost::mpl::plus<
                boost::mpl::minus<
                    boost::mpl::integral_c<char, ch>,
                    boost::mpl::integral_c<char, 'a'>
                >,
                boost::mpl::integral_c<char, 'A'>
            >,
            boost::mpl::integral_c<char, ch>
        >::type
    { };


} // namespace ichar_detail


template< char ch >
struct ichar :
    or_2<
        char_< ichar_detail::to_lower<ch>::value >,
        char_< ichar_detail::to_upper<ch>::value >
    >
{ };


} } // namespace pstade::biscuit


#endif
