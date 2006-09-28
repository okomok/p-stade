#ifndef PSTADE_LIME_SAVE_FILE_HPP
#define PSTADE_LIME_SAVE_FILE_HPP


// PStade.Lime
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <fstream> // ofstream
#include <string>
#include <boost/throw_exception.hpp>
#include <pstade/oven/to_stream.hpp>
#include <pstade/oven/to_utf8_encoder.hpp>
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
        std::ofstream fout(fileName.c_str(), std::ios::binary);
        if (!fout) {
            save_error err(fileName);
            boost::throw_exception(err);
            return;
        }

        lime::copy_XMLDecl(oven::to_stream(fout));
        lime::save(root, oven::to_utf8_encoder(oven::to_stream(fout)));
    }


    template< class Node >
    void save_file_default(Node& root, std::string const& fileName)
    {
        std::ofstream fout(fileName.c_str(), std::ios::binary);
        if (!fout) {
            save_error err(fileName);
            boost::throw_exception(err);
            return;
        }

        lime::copy_XMLDecl(oven::to_stream(fout));
        lime::save_default(root, oven::to_utf8_encoder(oven::to_stream(fout)));
    }


} } // namespace pstade::lime


#endif
