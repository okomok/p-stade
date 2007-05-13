

namespace poost_extension {

    struct hello { };

}

namespace poost {

    namespace detail {

        template< class T >
        int poost_hello(T const& x)
        {
            return poost_(poost_extension::hello(), x);
        }

    }

    template< class T >
    int hello(T const& x)
    {
        using namespace detail;
        return poost_hello(x);
    }

}


// user code
//

struct bar_base
{
    int m_i;
};


namespace my {

    struct foo
    {
    private:
        int i;

        friend int poost_hello(foo const& self)
        {
            return self.i;
        }
    };

    struct foo_
    {
        int i;
    };

        inline
        int poost_hello(foo_ const& f_)
        {
            return f_.i;
        }

    struct bar : bar_base
    { };
}


namespace your {

    template< class Int >
    struct foo
    {
    private:
        Int i;

        friend int poost_hello(foo<Int> const& self)
        {
            Int i; // (1)
            return self.i;
        }
    };

    struct bar : bar_base
    { };
}


namespace poost_extension {

    int poost_(hello, bar_base const& b)
    {
        return b.m_i;
    }

}


int main()
{
    poost::hello(my::foo());
    poost::hello(my::foo_());
    poost::hello(your::foo<int>());
    poost::hello(my::bar());
    poost::hello(your::bar());
}
