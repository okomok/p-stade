

#if defined(_MSC_VER)
    #pragma warning(push)
    #pragma warning(disable: 4127) // conditional expression is constant
    #pragma warning(disable: 4244) // conversion from 'const NewSource' to 'unsigned int', possible loss of data
    #pragma warning(disable: 4267) // conversion from 'size_t' to 'unsigned int', possible loss of data
    #pragma warning(disable: 4511) // copy constructor could not be generated
    #pragma warning(disable: 4512) // assignment operator could not be generated
    #pragma warning(disable: 4701) // local variable 'result' may be used without having been initialized
    #include <boost/lexical_cast.hpp>
    #pragma warning(pop)
#endif
