#include <string>
#include <vector>
#include <utility>
#include <functional>

#include <boost/iterator/transform_iterator.hpp>
#include <boost/range/iterator_range.hpp> 
#include <boost/utility.hpp> 
#include <boost/bind.hpp>

typedef boost::iterator_range<std::string::const_iterator>
iter_range;
typedef std::pair<iter_range,iter_range>
result_type;

struct string_splitter : std::unary_function<std::string const&,
result_type> 
{
	result_type operator()(std::string const& s)const throw()
	{
		iter_range r1(s.begin(), s.begin() + s.find(":"));
		iter_range r2(r1.end()+1, s.end());
		return result_type(r1,r2);
	}
};

typedef std::vector<std::string>
str_vector;
typedef str_vector::const_iterator
vector_citer;
typedef boost::transform_iterator<string_splitter, vector_citer>
msg_opcode_citer;

int main()
{
	//create vector of strings and put 2 strings inside
	str_vector v;
	v.push_back(std::string("test1:opcode1"));
	v.push_back(std::string("test2:opcode2"));

	//!!!increment operator or dereference operator cause an assertion failure!!!
	// stating: "vector iterators incompatible"
    for(msg_opcode_citer curr = msg_opcode_citer(boost::const_begin(v), string_splitter()),
        end = msg_opcode_citer(boost::const_end(v), string_splitter()); 
			curr != end; ++curr)
	{
		result_type t = *curr;
	}

	return 0;
}
