BOOST_FOREACH (
    filesystem::path const& pt,
    directory_range(filesystem::current_path()))
{
    std::cout << pt.leaf() << std::endl;
}