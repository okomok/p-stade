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


#include <map>
#include <boost/any.hpp>
#include <boost/shared_ptr.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./fix.hpp"
#include "./function_by_cref.hpp"
#include "./function_by_value.hpp"
#include "./function_facade.hpp"


namespace pstade { namespace egg {


    namespace memoize_detail {


        struct op_wrap_ :
            function_facade< op_wrap_, boost::use_default, function_by_cref<boost::mpl::_> >
        {
            template<class Myself, class Base, class Fixed, class Arg>
            struct apply :
                result_of<
                    typename result_of<Base(Fixed const&)>::type(Arg const&)
                >
            { };

            template<class Result, class Base, class Fixed, class Arg>
            Result call(Base const& base, Fixed const& fixed, Arg const& arg) const
            {
                typedef std::map<Arg, Result> map_t;

                if (m_pany->empty()) {
                    *m_pany = map_t();
                }

                map_t& m = boost::any_cast<map_t&>(*m_pany);

                typename map_t::iterator it = m.find(arg);
                if (it != m.end())
                    return it->second;
                else
                    return m[arg] = base(fixed)(arg);
            }

            op_wrap_() :
                m_pany(new boost::any())
            { }

        private:
            boost::shared_ptr<boost::any> m_pany;
        };


        struct baby
        {
            template<class Myself, class Base_>
            struct apply :
                result_of<
                    op_fix(
                        typename result_of<
                            typename result_of<op_curry3(op_wrap_)>::type(typename result_of<op_curry2(Base_&)>::type)
                        >::type
                    )
                >
            { };

            template<class Result, class Base_>
            Result call(Base_ base) const
            {
                return fix(
                    curry3(op_wrap_())(curry2(base))
                );
            }
        };


    } // namespace memoize_detail


    typedef function_by_value<memoize_detail::baby> op_memoize;
    PSTADE_POD_CONSTANT((op_memoize), memoize) = {{}};


} } // namespace pstade::egg


#endif
