#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/directory_range.hpp>


#include <iostream>
#include <boost/foreach.hpp>


void test()
{
    namespace fs = boost::filesystem;
    namespace oven = pstade::oven;
    using namespace oven;

    {
        BOOST_FOREACH (const fs::path& pt, directory_range(fs::current_path<fs::path>())) {
            std::cout << pt.leaf() << std::endl;
        }
    }

#if !defined(BOOST_FILESYSTEM_NARROW_ONLY)
    {
        BOOST_FOREACH (const fs::wpath& pt, wdirectory_range(fs::current_path<fs::wpath>())) {
            std::wcout << pt.leaf() << std::endl;
        }
    }
#endif

    std::cout << "recursive...\n";

    {
        BOOST_FOREACH (const fs::path& pt, recursive_directory_range(fs::current_path<fs::path>())) {
            std::cout << pt.leaf() << std::endl;
        }
    }

#if !defined(BOOST_FILESYSTEM_NARROW_ONLY)
    {
        BOOST_FOREACH (const fs::wpath& pt, wrecursive_directory_range(fs::current_path<fs::wpath>())) {
            std::wcout << pt.leaf() << std::endl;
        }
    }
#endif
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
