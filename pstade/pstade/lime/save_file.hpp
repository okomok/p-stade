#ifndef PSTADE_LIME_SAVE_FILE_HPP
#define PSTADE_LIME_SAVE_FILE_HPP


// PStade.Lime
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <fstream>
#include <iterator> // ostream_iterator
#include <string>
#include <boost/cstdint.hpp> // uint8_t
#include <boost/throw_exception.hpp>
#include <pstade/oven/null_terminate_range.hpp>
#include <pstade/oven/stream_output_iterator.hpp>
#include <pstade/oven/utf8_encoder.hpp>
#include <pstade/what.hpp>
#include "./copy_XMLDecl.hpp"
#include "./error.hpp"
#include "./save.hpp"


namespace pstade { namespace lime {


struct save_error :
    error
{
    explicit save_error(std::string fileName) :
        error(pstade::what("lime-save-error", fileName))
    { }
};


template< class Node >
void save_file(Node& root, std::string fileName)
{
    std::ofstream fout(fileName.c_str(), std::ios::binary);
    if (!fout) {
        save_error err(fileName);
        boost::throw_exception(err);
    }

    lime::copy_XMLDecl(oven::stream_outputter(fout));
    lime::save(root, oven::utf8_encoder(oven::stream_outputter(fout)));
}


template< class Node >
void save_file_default(Node& root, std::string fileName)
{
    std::ofstream fout(fileName.c_str(), std::ios::binary);
    if (!fout) {
        save_error err(fileName);
        boost::throw_exception(err);
    }

    lime::copy_XMLDecl(oven::stream_outputter(fout));
    lime::save_default(root, oven::utf8_encoder(oven::stream_outputter(fout)));
}


} } // namespace pstade::lime


#endif
