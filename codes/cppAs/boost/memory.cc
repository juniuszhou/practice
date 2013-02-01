/*
g++ -I/usr/local/boost_1_51_0 memory.cc
*/

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/weak_ptr.hpp>

int main()
{

boost::shared_ptr<int> p(new int(5));
boost::weak_ptr<int> q(p);

boost::instrutive_ptr<int> x(new int(9));



if(boost::shared_ptr<int> r = q.lock())
{
   
}

return 0;
}

