#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/trotter_decode_range.hpp>
#include <pstade/oven.hpp>
#include <boost/range.hpp>


#include "trotter/conversion/utf16/utf16.hpp"
#include "trotter/conversion/utf8/utf8.hpp"
#include "trotter/conversion/converter.hpp"
#include "trotter/conversion/input_iterator.hpp"
#include "trotter/conversion/output_iterator.hpp"


using namespace pstade::oven;
namespace cvt = trotter::conversion;


std::string utf16_utf8(std::wstring const& utf16string)
{
    std::string result;

    pstade::oven::copy(
        utf16string|trotter_decoded(cvt::utf16() >> cvt::utf8(), wchar_t()),
        std::back_inserter(result)
    );

    return result;
}

template< class Iterator >
void foo(Iterator x)
{
    Iterator y;
    y = x;
}


void test()
{
    std::string rng("axax");


}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
