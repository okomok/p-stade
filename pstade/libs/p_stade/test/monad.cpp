#include <pstade/vodka/drink.hpp>


#include <boost/function.hpp>
#include <iostream>
#include <string>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/type.hpp>
#include <boost/utility/result_of.hpp>


namespace bll = boost::lambda;


template<typename X>
struct Monad;

// m a -> (a -> m b) -> m b
template<typename Ma, typename a_Mb>
typename boost::result_of<a_Mb(typename Monad<Ma>::a_type)>::type
operator>>=(Ma m, a_Mb f)
{
    return Monad<Ma>().bind(m, f);
}

// m a -> m b -> m b
template<typename Ma, typename Mb>
Mb operator>>(Ma m, Mb k)
{
    return Monad<Ma>().abandon(m, k);
}

// a -> Ma
template<typename Ma, typename a>
Ma return_(a u)
{
    return Monad<Ma>().return_(u);
};


template<typename a>
struct IO
{
    boost::function<a()> operate;
};

template<typename IOa>
struct call_operate;

template<typename a>
struct call_operate<IO<a> >
{
    typedef a result_type;

    a operator()(IO<a> m) const
    {
        return m.operate();
    }
};

template<typename a_>
struct Monad<IO<a_> >
{
    typedef a_ a_type;

    template<typename a, typename a_IOb>
    typename boost::result_of<a_IOb(a)>::type bind(IO<a> m, a_IOb f)
    {
        typedef typename boost::result_of<a_IOb(a)>::type IOb;

        // function composition: call_operate . f . m.operate
        IOb r = { bll::bind(call_operate<IOb>(), bll::bind(f, bll::bind(m.operate))) };
        return r;
    }

    template<typename a, typename IOb>
    IOb abandon(IO<a> m, IOb k)
    {
        IOb r = { bll::bind(call_operate<IOb>(), ( bll::bind(m.operate) , bll::constant(k)) ) };
        return r;
    }

    template<typename a>
    IO<a> return_(a u)
    {
        IO<a> r = { bll::constant(u) };
        return r;
    }
};


inline
IO<void> putStr(std::string str)
{
    IO<void> r = { std::cout << bll::constant(str) };
    return r;
}

inline
std::string getLine_impl()
{
    std::string r;
    std::getline(std::cin, r);
    return r;
}

IO<std::string> const getLine = { &getLine_impl };

inline
IO<void> putStrLn(std::string str)
{
    return putStr(str + "\n");
}


template<class IOa>
void eval(IOa m)
{
    m.operate();
}

int main()
{
    ::eval( getLine >>= putStrLn );
    ::eval( putStrLn("hello,") >> putStrLn("monad") >> putStrLn("in C++!") );

//    ::eval( ( getLine >>= return_<IO<std::string>>() ) >>= my::putStrLn );
}
