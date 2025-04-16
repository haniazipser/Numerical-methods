//Hanna Zipser
#include <iostream>
#include <cmath>
#include "funkcja.h"
using namespace std;


template <typename T>
struct FAD {

    T value;
    T dx;
    T dy;
    T dx2;
    T dxy;
    T dy2;

    FAD() : value(0), dx(0), dy(0), dx2(0), dxy(0), dy2(0) {}

    FAD(T v) : value(v), dx(0), dy(0), dx2(0), dxy(0), dy2(0) {}

    FAD(T v, T dx, T dy, T dx2, T dxy, T dy2) {
        value = v;
        this->dx = dx;
        this->dy = dy;
        this->dx2 = dx2;
        this->dxy = dxy;
        this->dy2 = dy2;
    }



    FAD operator+(const FAD& o) const {
        return FAD(value + o.value, dx + o.dx, dy + o.dy, dx2 + o.dx2,  dxy + o.dxy, dy2 + o.dy2);
    }

    FAD operator-(const FAD& o)const  {
        return FAD(value - o.value, dx - o.dx, dy - o.dy, dx2 - o.dx2,  dxy - o.dxy, dy2 - o.dy2);
    }

    FAD operator-()const  {
        return FAD(-value, -dx, -dy, -dx2, -dxy, dy2);
    }

    FAD operator*(const FAD& o)const {
        return FAD(value * o.value,
                   value * o.dx + dx * o.value,
                   value * o.dy + dy * o.value,
                   value * o.dx2 + 2 * dx * o.dx + dx2 * o.value,
                   value * o.dxy + dx * o.dy + dy * o.dx + dxy * o.value,
                   value * o.dy2 + 2 * dy * o.dy + dy2 * o.value);
    }

    FAD operator/(const FAD& o)const {
        T temp = value / o.value;
        T tempdx = (dx - temp * o.dx)/o.value;
        T tempdy = (dy - temp * o.dy)/o.value;
        T tempdx2 = (dx2 - temp * o.dx2 - 2 * tempdx * o.dx) /o.value;
        T tempdy2 = (dy2 - temp * o.dy2 - 2 * tempdy * o.dy) /o.value;
        T tempdxy = (dxy - tempdx * o.dy - tempdy * o.dx - temp * o.dxy) /o.value;
        return FAD( temp,
                   tempdx,
                   tempdy,
                   tempdx2,
                   tempdxy,
                   tempdy2);
   }

    friend FAD sin(const FAD& o) {
        T sinValue = std::sin(o.value);
        T cosValue = std::cos(o.value);

        return FAD(sinValue,
                cosValue * o.dx,
                cosValue * o.dy,
                -sinValue * o.dx * o.dx + cosValue * o.dx2,
                -sinValue * o.dx * o.dy + cosValue * o.dxy,
                -sinValue * o.dy * o.dy + cosValue * o.dy2);
    }

    friend FAD cos(const FAD& o) {
        T sinValue = std::sin(o.value);
        T cosValue = std::cos(o.value);

        return FAD(cosValue,
                -sinValue * o.dx,
                -sinValue * o.dy,
                -cosValue * o.dx * o.dx - sinValue * o.dx2,
                -cosValue * o.dx * o.dy - sinValue * o.dxy,
                -cosValue * o.dy * o.dy - sinValue * o.dy2
                );
    }

    friend FAD exp(const FAD& o) {
        T expValue = std::exp(o.value);
        return FAD(expValue,
                   expValue * o.dx,
                   expValue * o.dy,
                   expValue * (o.dx * o.dx + o.dx2),
                   expValue * (o.dx * o.dy + o.dxy),
                   expValue * (o.dy * o.dy + o.dy2)
                   );
    }


};

template <typename T>
FAD<T> operator+(const double& c, const FAD<T>& fad) {
    return FAD<T>(c) + fad;
}

template <typename T>
FAD<T> operator+(const FAD<T>& fad, const double& c) {
    return fad + FAD<T>(c);
}

template <typename T>
FAD<T> operator-(const double& c, const FAD<T>& fad) {
    return FAD<T>(c) - fad;
}

template <typename T>
FAD<T> operator-(const FAD<T>& fad, const double& c) {
    return fad - FAD<T>(c);
}

template <typename T>
FAD<T> operator*(const double& c, const FAD<T>& fad) {
    return FAD<T>(c) * fad;
}

template <typename T>
FAD<T> operator*(const FAD<T>& fad, const double& c) {
    return fad * FAD<T>(c);
}


template <typename T>
FAD<T> operator/(const int& c, const FAD<T>& fad) {
    return FAD<T>(c) / fad;
}

template <typename T>
FAD<T> operator/(const FAD<T>& fad, const double& c) {
    return fad / FAD<T>(c);
}

int main()
{
    int m;
    double x, y;
    cin >> m;
    cout.precision(15);
    for (int i = 0; i < m; i++){
        cin>>x>>y;
        FAD<double> X(x, 1, 0,0,0,0);
        FAD<double> Y(y, 0, 1,0,0,0);

        FAD<double> result = funkcja(X, Y);
        cout<< result.value <<" "<<result.dx<<" "<<result.dy<<" "<<result.dx2<<" "<<result.dxy << " "<<result.dy2<<endl;

    }

}
