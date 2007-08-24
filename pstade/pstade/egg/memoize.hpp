#ifndef PSTADE_EGG_MEMOIZE_HPP
#define PSTADE_EGG_MEMOIZE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://www.kmonos.net/wlog/52.php
// http://d.hatena.ne.jp/Cryolite/20050902#p1
//
// Todo:
//
// thread-safe.


#include <map>
#include <boost/any.hpp>
#include <boost/shared_ptr.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./fix.hpp"
#include "./function_facade.hpp"


namespace pstade { namespace egg {


    namespace memoize_detail {


        struct op_uncurried_wrap :
            function_facade<op_uncurried_wrap>
        {
            template<class Myself, class Fun, class Fixed, class Arg>
            struct apply :
                result_of<
                    typename result_of<Fun(Fixed&)>::type(Arg&)
                >
            { };

            template<class Result, class Fun, class Fixed, class Arg>
            Result call(Fun& fun, Fixed& fixed, Arg const& arg) const
            {
                typedef std::map<Arg, Result> map_t;

                if (m_pany->empty()) {
                    *m_pany = map_t();
                }

                map_t *pmap = boost::any_cast<map_t>(m_pany.get());

                typename map_t::iterator it = pmap->find(arg);
                if (it != pmap->end())
                    return it->second;
                else
                    return (*pmap)[arg] = fun(fixed)(arg);
            }

            op_uncurried_wrap() :
                m_pany(new boost::any())
            { }

        private:
            boost::shared_ptr<boost::any> m_pany;
        };


        struct baby
        {
            template<class Myself, class Base>
            struct apply :
                result_of<
                    op_fix(
                        typename result_of<
                            typename result_of<op_curry3(op_uncurried_wrap)>::type(typename result_of<op_curry2(Base&)>::type)
                        >::type
                    )
                >
            { };

            template<class Result, class Base>
            Result call(Base& base) const
            {
                return fix(
                    curry3(op_uncurried_wrap())(curry2(base))
                );
            }
        };


    } // namespace memoize_detail


    typedef function<memoize_detail::baby> op_memoize;
    PSTADE_POD_CONSTANT((op_memoize), memoize) = {{}};


} } // namespace pstade::egg


#endif
