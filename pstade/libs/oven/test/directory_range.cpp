#include "./prelude.hpp"
#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/directory_range.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/test.hpp"


#include <iostream>
#include <boost/foreach.hpp>


void pstade_minimal_test()
{
    namespace fs = boost::filesystem;
    namespace oven = pstade::oven;
    using namespace oven;

    {
        directory_range dr(fs::current_path<fs::path>());
        BOOST_FOREACH (const fs::path& pt, dr) {
            std::cout << pt.leaf() << std::endl;
        }

        test::lightweight_copyable(dr);
    }

#if !defined(BOOST_FILESYSTEM_NARROW_ONLY)
    {
        wdirectory_range dr(fs::current_path<fs::wpath>());
        BOOST_FOREACH (const fs::wpath& pt, dr) {
            std::wcout << pt.leaf() << std::endl;
        }

        test::lightweight_copyable(dr);
    }
#endif

    std::cout << "recursive...\n";

    {
        recursive_directory_range dr(fs::current_path<fs::path>());
        BOOST_FOREACH (const fs::path& pt, dr) {
            std::cout << pt.leaf() << std::endl;
        }

        test::lightweight_copyable(dr);
    }

#if !defined(BOOST_FILESYSTEM_NARROW_ONLY)
    {
        wrecursive_directory_range dr(fs::current_path<fs::wpath>());
        BOOST_FOREACH (const fs::wpath& pt, dr) {
            std::wcout << pt.leaf() << std::endl;
        }

        test::lightweight_copyable(dr);
    }
#endif
}
