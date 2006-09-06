#ifndef PSTADE_LIME_SAVE_FILE_HPP
#define PSTADE_LIME_SAVE_FILE_HPP


// PStade.Lime
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <fstream>
#include <iterator> // ostream_iterator
#include <string>
#include <boost/cstdint.hpp> // uint8_t
#include <boost/throw_exception.hpp>
#include <pstade/oven/function_output_iterator.hpp>
#include <pstade/oven/null_terminate_range.hpp>
#include <pstade/oven/output_functions.hpp>
#include <pstade/oven/to_utf8.hpp>
#include <pstade/what.hpp>
#include "./copy_XMLDecl.hpp"
#include "./error.hpp"
#include "./save.hpp"


namespace pstade { namespace lime {


struct save_error :
    error
{
    explicit save_error(std::string const& fileName) :
        error(pstade::what("lime-save-error", fileName))
    { }
};


template< class Node >
void save_file(Node& root, std::string const& fileName)
{
    std::ofstream to_file(fileName.c_str(), std::ios::binary);
    if (!to_file) {
        save_error err(fileName);
        boost::throw_exception(err);
    }

    lime::copy_XMLDecl(oven::to_function(oven::stream_output(to_file)));
    lime::save(root, oven::to_utf8(oven::to_function(oven::stream_output(to_file))));
}


template< class Node >
void save_file_default(Node& root, std::string const& fileName)
{
    std::ofstream to_file(fileName.c_str(), std::ios::binary);
    if (!to_file) {
        save_error err(fileName);
        boost::throw_exception(err);
    }

    lime::copy_XMLDecl(oven::to_function(oven::stream_output(to_file)));
    lime::save_default(root, oven::to_utf8(oven::to_function(oven::stream_output(to_file))));
}


} } // namespace pstade::lime


#endif
