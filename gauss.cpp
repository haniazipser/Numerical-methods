//Hanna Zipser
#include <iostream>
#include "vectalg.h"
#define  NDEBUG

using namespace std;

void swapRows(Matrix &a, int i, int j, int n){
    Vector temp (n);
    for (int k = 0; k < n; k++){
        temp[k] = a(i,k);
        a(i,k) = a(j,k);
    }

    for (int k = 0; k < n; k++){
        a(j,k) = temp[k];
    }
}

void gauss (Matrix &a, Vector &b, int n){
    Vector row (n);
    Vector scales (n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            row[j] = a(i,j);
        }
        double norm = row.max_norm();
        scales[i] = norm;
    }

    for(int i=0;i<n-1;i++){
        int maxRow = i;
        double maks = std::abs(a(i, i)) / scales[i];

        for (int j = i + 1; j < n; j++) {
            double r = std::abs(a(j, i)) / scales[j];
            if (r > maks) {
                maks = r;
                maxRow = j;
            }
        }

        if (maxRow != i) {
            swapRows(a,i, maxRow, n);
            std::swap(b[i], b[maxRow]);
            std::swap(scales[i], scales[maxRow]);
        }

      for(int j=i+1;j<n;j++){
           double r = a(j,i)/a(i,i);

           for(int k=0;k< n;k++)
           {
                a(j,k) = a(j,k) - r*a(i,k);
           }
           b[j] = b[j] - r* b[i];
      }
    }
}


Vector substitution (Matrix &a, Vector &b, int n){
    Vector x(n);
    x[n - 1] = b[n-1]/a(n-1,n-1);

	 for(int i=n-2;i>=0;i--){
		  x[i] = b[i];
		  for(int j=i+1;j<n;j++){
		  		x[i] = x[i] - a(i,j)*x[j];
		  }
		  x[i] = x[i]/a(i,i);
	 }
	 return x;
}

Vector iterativeFix ( Matrix &a, Vector &b, Vector &x, double eps){
    Matrix a1 (a);
    while(1){
       Vector r = residual_vector(a,b,x);
       if (r.max_norm() < eps){
            return x;
       }
       a1 = a;
       gauss(a1,r,a1.size());
       Vector e = substitution(a1,r,a1.size());
       for (int i = 0; i < a.size(); i++){
         x[i] += e[i];
       }
    }
}


Vector solveEquations(
        const Matrix & A,   // Macierz
        const Vector & b,   // Wektor
        double  eps         // dopuszczalny b³¹d
){
    Matrix a1 (A);
    Vector b1(b);
    int n = a1.size();
    gauss (a1,b1,n);
    Vector solution = substitution(a1,b1,n);
    a1 = A;
    b1 = b;
    iterativeFix(a1,b1,solution,eps);
    return solution;
}


