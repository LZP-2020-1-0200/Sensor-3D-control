#include "vector.h"

Vector operator+(int b, Vector v){
	return Vector(v.x+b, v.y+b, v.z+b);
}
Vector operator*(int a, Vector v){
	return Vector(v.x*a, v.y*a, v.z*a);
}
Vector Vector::operator+(Vector v){
	return Vector(x+v.x, y+v.y, z+v.z);
}
Vector Vector::operator+(int b){
	return Vector(x+b, y+b, z+b);
}
Vector Vector::operator-(Vector v){
	return Vector(x-v.x, y-v.y, z-v.z);
}
Vector Vector::operator-(int b){
	return Vector(x-b, y-b, z-b);
}
Vector Vector::operator*(int a){
	return Vector(x*a, y*a, z*a);
}
Vector Vector::operator/(int a){
	return Vector(x/a, y/a, z/a);
}
Vector& Vector::operator+=(int b){
	x+=b;
	y+=b;
	z+=b;
	return *this;
}
Vector& Vector::operator-=(int b){
	x-=b;
	y-=b;
	z-=b;
	return *this;
}
Vector& Vector::operator*=(int a){
	x*=a;
	y*=a;
	z*=a;
	return *this;
}
Vector& Vector::operator/=(int a){
	x/=a;
	y/=a;
	z/=a;
	return *this;
}