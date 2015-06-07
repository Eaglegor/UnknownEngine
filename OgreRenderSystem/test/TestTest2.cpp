#include <boost/test/minimal.hpp>

int add(int i, int j) {
	return i + j;
}

int test_main(int, char*[])
{
	BOOST_CHECK(add(2,2) == 4);
	
	return add(2,2) == 4 ? 0 : 1;
}