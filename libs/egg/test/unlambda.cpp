

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/unlambda.hpp>
#include <boost/egg/bind.hpp>
#include <boost/egg/placeholders.hpp>
#include "./egg_test.hpp"


namespace egg = boost::egg;
using namespace egg::placeholders;


int foo(int) { return 0; }
int bar(int, int) { return 0; }


template<class F>
int nested(const F& f) {
    int x;
    egg::bind(egg::unlambda(f), _1)(x);
    return x;
}


void egg_test()
{
    ::nested(egg::bind(&bar, 1, _1));
}










#if 0

#include <boost/bind.hpp>
#include "./egg_test.hpp"

using namespace boost;

int foo(int) { return 0; }
int bar(int, int) { return 0; }

template<class F>
int nested(const F& f) {
  int x;
  bind(f, _1)(x);
  return x;
}

void egg_test()
{
    nested(bind(&bar, 1, _1));
}

#endif




#if 0

#include <boost/lambda/bind.hpp>
#include <boost/lambda/core.hpp>
#include "./egg_test.hpp"

using namespace boost::lambda;

int foo(int) { return 0; }
int bar(int, int) { return 0; }

template<class F>
int nested(const F& f) {
  int x;
  bind(f, _1)(x);
  return x;
}

void egg_test()
{
    nested(bind(&bar, 1, _1));
}

#endif
