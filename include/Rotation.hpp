#ifndef ROTATION_HPP_
# define ROTATION_HPP_

#include <iostream>

class rotation
{
public:
	rotation();
	~rotation();
	void rotation_left(int &, int &, int &);
	void rotation_right(int &, int &, int &);
	void rotate(const int &, int &, int &);
	
protected:
	int my_rotation;
};

#endif /* !ROTATION_HPP_ */