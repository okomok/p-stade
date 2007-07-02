


template<typename T> struct static_const
{
 static T const value;
};

template<typename T>
T const static_const<T>::value = T();

struct placeholder
{
    placeholder() {}
};

// This is *supposed* to be statically initialized but many
// compilers do dynamic initialization for it. :-(
placeholder const &_1 = static_const<placeholder>::value;

int main()
{
    (placeholder volatile* volatile)(&_1);
}
