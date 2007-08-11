#include <pstade/vodka/drink.hpp>


#include <string>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/type.hpp>
#include <boost/function.hpp>
#include <boost/utility/result_of.hpp>
#include <iostream>


namespace my {


    namespace bll = boost::lambda;


    template<typename a>
    struct IO
    {
        boost::function<a()> side_effect;
    };


    template<typename IOa>
    struct call_side_effect;

    template<typename a>
    struct call_side_effect<IO<a> >
    {
        typedef a result_type;

        a operator()(IO<a> m) const
        {
            return m.side_effect();
        }
    };


    template<typename a, typename a_IOb>
    typename boost::result_of<a_IOb(a)>::type operator>>=(IO<a> m, a_IOb f)
    {
        typedef typename boost::result_of<a_IOb(a)>::type IOb;

        // function composition: call_effect . f . m.side_effect
        IOb r = { bll::bind(call_side_effect<IOb>(), bll::bind(f, bll::bind(m.side_effect))) };
        return r;
    }

    template<typename a, typename IOb>
    IOb operator>>(IO<a> m, IOb k)
    {
        IOb r = { bll::bind(call_side_effect<IOb>(), ( bll::bind(m.side_effect) , bll::constant(k)) ) };
        return r;
    }

#if 0
    template<typename a>
    IO<a> return_(boost::type<IO<a> >, a u)
    {
        IO<a> r = { bll::constant(u) };
        return r;
    }
#endif

    template<typename a>
    struct return_
    {
        typedef IO<a> result_type;

        IO<a> operator()(a u) const
        {
            IO<a> r = { bll::constant(u) };
            return r;
        }
    };

#if 0
    inline
    void do_nothing() { }

    template<>
    struct return_<void>
    {
        typedef IO<void> result_type;

        IO<void> operator()() const
        {
            IO<void> r = { &do_nothing };
            return r;
        }
    };
#endif


    inline IO<void> putStr(std::string str)
    {
        IO<void> r = { std::cout << bll::constant(str) };
        return r;
    }


    inline std::string getLine_impl()
    {
        std::string r;
        std::getline(std::cin, r);
        return r;
    }

    IO<std::string> const getLine = { &getLine_impl };


    inline IO<void> putStrLn(std::string str)
    {
        return putStr(str + "\n");
    }


    //IO<std::string> const getHello = my::return_(boost::type<IO<std::string> >(), std::string("Hello"));


} // namespace my


template<class IOa>
void eval(IOa m)
{
    m.side_effect();
}


int main()
{
    ::eval( my::getLine >>= my::putStrLn );
    ::eval( my::putStrLn("hello,") >> my::putStrLn("monad") >> my::putStrLn("in C++!") );

    ::eval( ( my::getLine >>= my::return_<std::string>() ) >>= my::putStrLn );
}
