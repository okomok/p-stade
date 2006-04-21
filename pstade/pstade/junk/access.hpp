#ifndef PSTADE_SAUSAGE_ACCESS_HPP
#define PSTADE_SAUSAGE_ACCESS_HPP


// PStade.Sausage
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// #include <boost/typeof/typeof.hpp>


namespace pstade { namespace sausage {


template< class T_ >
class access
{
public:
    typedef typename T_::pstade_sausage_enumerate_argument_type
    detail_enumerate_argument_type;

    template< class Argument, class T, class EnumFtor > static
    EnumFtor detail_enumerate(T& x, EnumFtor fun)
    {
        return x.template pstade_sausage_enumerate<Argument>(fun);
    }

private:
    template< class T >
    typename T::pstade_sausage_enumerate_argument_type get_argument_type();

public:
    template< class T >
    struct detail_enumerate_argument
    {
        // BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested, get_argument_type<T>)
        // typedef typename nested::type type;
        typedef typename T::pstade_sausage_enumerate_argument_type type;
    };
};


} } // namespace pstade::sausage


#endif
