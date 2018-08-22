#include <bits/stdc++.h>
using namespace std;
int MAX=1000;

int main(){

    double A[MAX][MAX], x[MAX], y [MAX];
    for(int i=0;i<MAX;i++){
        for(int j=0;j<MAX;j++){
            double x = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
            //
            A[i][j]=x;    
        }
        double y = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
        x[i]=y;   
    }
    auto begin = chrono::high_resolution_clock::now();    

    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            y[i] += A [i][j]*x[j];
    auto end = chrono::high_resolution_clock::now();    
    auto dur = end - begin;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
    cout <<"Bucle 1: "<< ms <<" millisecs"<< endl;

    begin = chrono::high_resolution_clock::now();    
    
    for (int j = 0; j < MAX; j++)
        for (int i = 0; i < MAX; i++)
            y[i] += A [i][j]*x[j];
    end = chrono::high_resolution_clock::now();
    dur = end - begin;
    ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
    cout <<"Bucle 2: "<< ms <<" millisecs"<< endl;


/*TIEMPOS OBTENIDOS*/
    /*
    Bucle 1: 7 millisecs
    Bucle 2: 17 millisecs

    Bucle 1: 8 millisecs
    Bucle 2: 10 millisecs

    */
}