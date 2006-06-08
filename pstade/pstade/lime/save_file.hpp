#ifndef PSTADE_LIME_SAVE_FILE_HPP
#define PSTADE_LIME_SAVE_FILE_HPP


// PStade.Lime
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <fstream>
#include <string>
#include <boost/throw_exception.hpp>
#include <pstade/garlic/back_inserter.hpp>
#include <pstade/oven/copy.hpp>
#include <pstade/oven/null_terminate_range.hpp>
#include <pstade/oven/utf8_encoder.hpp>
#include <pstade/what.hpp>
#include "./error.hpp"
#include "./save.hpp"


namespace pstade { namespace lime {


    namespace save_detail {


        template< class OStream > inline
        void copy_XMLDecl(OStream& os)
        {
            oven::copy(
                "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"|oven::null_terminated,
                oven::utf8_encoder(garlic::back_inserter(os))
            );
        }


    } // namespace save_detail


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

    save_detail::copy_XMLDecl(fout);
    lime::save(root, oven::utf8_encoder(garlic::back_inserter(fout)));
}


template< class Node >
void save_file_default(Node& root, std::string fileName)
{
    std::ofstream fout(fileName.c_str(), std::ios::binary);
    if (!fout) {
        save_error err(fileName);
        boost::throw_exception(err);
    }

    save_detail::copy_XMLDecl(fout);
    lime::save_default(root, oven::utf8_encoder(garlic::back_inserter(fout)));
}


} } // namespace pstade::lime


#endif
