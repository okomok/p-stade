// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_USAGE_DWA2006919_HPP
# define BOOST_CONCEPT_USAGE_DWA2006919_HPP

# include <boost/concept/assert.hpp>
# include <boost/detail/workaround.hpp>

namespace boost { namespace concept { 

# if BOOST_WORKAROUND(__GNUC__, == 2)

#  define BOOST_CONCEPT_USAGE(model) ~model()

# else 

template <class Model>
struct usage_requirements
{
    ~usage_requirements() { ((Model*)0)->~Model(); }
};

#  define BOOST_CONCEPT_USAGE(model)                                    \
    BOOST_CONCEPT_ASSERT((boost::concept::usage_requirements<model>));  \
    ~model()

# endif 

}} // namespace boost::concept

#endif // BOOST_CONCEPT_USAGE_DWA2006919_HPP
