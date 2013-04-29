class no_copies
{
public:
no_copies(){}
//the delete is similar to declare a func as private.
no_copies(no_copies const&) = delete;
no_copies& operator=(no_copies const&) = delete;
};

