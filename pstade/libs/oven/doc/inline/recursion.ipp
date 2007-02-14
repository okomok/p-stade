typedef any_range<int const&, boost::forward_traversal_tag> range_t;
range_t fibs;
memo_table tb;
int const start[] = { 1, 1 };
fibs =
    start
        | transformed(pstade::as_value)
        | jointed(
            boost::make_tuple(recursion(fibs), recursion(fibs)|dropped(1))|
                zipped_with(regular(lambda::_1 + lambda::_2))
            )
        | memoized(tb)
;

std::cout << (fibs|taken(howMany));