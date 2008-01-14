

// msvc-7.1, msvc-8.0, gcc-4.2, comeau-test-drive are ok.
// gcc-3.4 doesn't compile, though.

template<class Derived>
struct message_processor
{
    template<class P0, class P1, class P2>
    struct begin_msg_map { };

    template<int ID, int (Derived::*func)(int, int, int, bool&)>
    struct message_handler { };

    typedef Derived _;
};


struct a_type :
    message_processor<a_type>
{
    int on_file_exit(int, int, int, bool&)
    {
        return 0;
    }

    begin_msg_map
    <
        message_handler<10, &_::on_file_exit>,
        message_handler<11, &_::on_file_exit>,
        message_handler<12, &_::on_file_exit>
    >
    end_msg_map;
};

template<class T>
struct a_template :
    message_processor<a_template<T> >
{
    int on_file_exit(int, int, int, bool&)
    {
        return 0;
    }

    typedef a_template _;                       typename _::template
    begin_msg_map
    <                                           typename _::template
        message_handler<10, &_::on_file_exit>,  typename _::template
        message_handler<11, &_::on_file_exit>,  typename _::template
        message_handler<12, &_::on_file_exit>
    >
    end_msg_map;
};

int main()
{
    a_type().end_msg_map;
    a_template<char>().end_msg_map;
}

