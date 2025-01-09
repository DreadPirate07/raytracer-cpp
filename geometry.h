#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_
#include <cmath>
#include <cstddef>
#include <regex>
#include <vcruntime_typeinfo.h>
#include <vector>
#include <cassert>
#include <iostream>
#include <xstring>

// size_t -> unsigned long long
// DIM -> dimension
// template of custom vector struct

template <size_t DIM, typename T> struct vec {
    // default constructor
    // assigns a default constructed T object to the i-th element
    // of array (T())
    vec() {
        for (int i=DIM;i--;data_[i] = T());
    }
    // overload methods, allows handling elements differently according to
    // whether the object is modifiable or not
    // maintains safety and flexibility regarding object mutability.
    T& operator[](const size_t i) {
        assert(i<DIM);
        return data_[i];
    }
        
    const T& operator[](const size_t i) const {
        assert(i<DIM);
        return data_[i];
    }

    private:
        T data_[DIM];
};

typedef vec<2,float> Vec2f;
typedef vec<3,float> Vec3f;
typedef vec<3, int > Vec3i;
typedef vec<4,float> Vec4f;

template <typename T> struct vec<2,T> {
    T x,y;

    // default constructor
    vec(): x(T()), y(T()) {}
    
    // parameterized constructor 
    vec(T X, T Y): x(X), y(Y) {}

    // template constructor (for conversion between types)
    template <class U> vec<2,T>(const vec<2,U> &v);

    T& operator[](const size_t i) {
        assert(i<2);
        return i<=0? x:y;
    }

    const T& operator[](const size_t i) const {
        assert(i<2);
        return i<=0?x:y;
    }
};

template <typename T> struct vec<3,T> {
    T x,y,z;

    vec(): x(T()),y(T()),z(T()) {}
    vec(T X,T Y,T Z): x(X),y(Y),z(Z) {}

    T& operator[](const size_t i) {
        assert(i<3);
        return i <= 0 ? x : (i==1?y:z);
    }
    const T& operator[](const size_t i) const {
        assert(i<3);
        return i<=0 ? x:(i==1?y:z);
    }

    float norm() {
        return std::sqrt(x*x + y*y + z*z);
    }
    
    // adjusts the vector until the length becomes l (default=1)
    vec<3,T>& normalize(T l=1) {
        *this = (*this)*(l/norm());
        return *this;
    }
};

// overloaded operator for respective operations 

template<size_t DIM, typename T> T operator*(const vec<DIM,T>& lhs, const vec<DIM,T>& rhs) {
    T ret = T();
    for (size_t i=DIM;i--;ret += lhs[i]*rhs[i]);
    return ret;
}

template<size_t DIM, typename T> vec<DIM,T> operator+(vec<DIM,T> lhs,const vec<DIM,T>& rhs) {
    for (size_t i=DIM;i--; lhs[i] += rhs[i]);
    return lhs;
}

template<size_t DIM, typename T> vec<DIM,T> operator-(vec<DIM,T> lhs,const vec<DIM,T>& rhs) {
    for (size_t i=DIM;i--;lhs[i] -= rhs[i]);
    return lhs;
}

template<size_t DIM, typename T, typename U> vec<DIM,T> operator*(const vec<DIM,T>& lhs, const U& rhs) {
    vec<DIM,T> ret;
    for (size_t i = DIM;i--;ret[i] = lhs[i]*rhs);
    return ret;
}

template <size_t DIM,typename T> vec<DIM,T> operator-(const vec<DIM,T> &lhs) {
    return lhs*T(-1);
}

template <typename T> vec<3,T> cross(vec<3,T> v1, vec<3,T> v2) {
    return vec<3,T>(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
}

// '<<' operator overloaded
template <size_t DIM, typename T> std::ostream& operator<<(std::ostream& out, const vec<DIM,T>& v) {
    for(unsigned int i=0; i<DIM; i++) {
        out << v[i] << " " ;
    }
    return out ;
}
#endif