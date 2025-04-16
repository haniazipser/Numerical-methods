//Hanna Zipser
#include <iostream>
#include <vector>
using namespace std;


double* SOR(vector<double> a[], double b[], double x0[], int n, int m, int l, double w) {// Jacobi

    for(int iter=0; iter < l; iter++) {
        for (int i = 0; i < n; i++) {
            double s = b[i];
             // Podprzek¹tne
            //A(x,y)=a[m+(x-y)][y]
            for (int j = max(0, i - m); j < i; j++) {
                s -= a[m +(i - j)][j] * x0 [j];
            }


            // Nadprzek¹tne
            //A(x,y)=a[m - (y - x) ][x]
            for (int j = i + 1; j <= min(n - 1, i + m); j++) {
                s -= a[m - (j - i)][i] * x0 [j];
            }


            x0[i] = (1 - w) * x0[i] + w * (s / a[m][i]);
        }
    }
    return x0;
}

int main()
{
    int n,m;
    cin>>n>>m;
    int length = n - m;

    vector <double> a[2*m + 1];

    double b[n];
    double x[n];
    double w;
    int l;
    int i;
    for (i = 0; i < m; i++){
        for (int j = 0; j < length; j++){
            double temp;
            cin>>temp;
            a[i].push_back(temp);
            a[2*m - i].push_back(temp);
        }
        length++;
    }

    for (int j = 0; j < length; j++){
            double temp;
            cin>>temp;
            a[m].push_back(temp);
    }

    for ( int i= 0; i < n; i++){
        cin>>b[i];
    }

    for ( int i= 0; i < n; i++){
        cin>>x[i];
    }
    cin >> w;
    cin >> l;

    SOR(a,b,x,n,m,l,w);

    std::cout.precision(10);
    std::cout <<std::scientific;

    for (int j = 0; j < n; j++){
            cout<<x[j]<<endl;
    }


    return 0;
}
