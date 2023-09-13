#ifndef VECTOR_H
#define VECTOR_H

/**
 * @class Vector
 * @brief A class that represents a 3D vector
 * @details This class represents a 3D vector with integer coordinates.
 * It supports basic operations such as addition, subtraction, multiplication and division by a scalar,
 * as well as addition and subtraction by vectors and the dot product and the cross product.
*/
class Vector{
public:
	int x;
	int y;
	int z;
	Vector(int x=0, int y=0, int z=0): x(x), y(y), z(z) {};
	Vector(Vector const& v): x(v.x), y(v.y), z(v.z) {};
	Vector operator+(Vector v);
	Vector operator+(int b);
	Vector operator-(Vector v);
	Vector operator-(int b);
	Vector operator*(int a);
	Vector operator/(int a);
	Vector& operator+=(int b);
	Vector& operator-=(int b);
	Vector& operator*=(int a);
	Vector& operator/=(int a);
};

Vector operator+(int b, Vector v);
Vector operator*(int a, Vector v);
#endif