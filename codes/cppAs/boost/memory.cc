/*
g++ -I/usr/local/boost_1_51_0 memory.cc
*/

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/weak_ptr.hpp>
#include <boost/smart_ptr/intrusive_ptr.hpp>

int main()
{

boost::shared_ptr<int> p(new int(5));
boost::weak_ptr<int> q(p);

if(boost::shared_ptr<int> r = q.lock())
{
   
}

return 0;
}

