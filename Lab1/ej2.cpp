#include <bits/stdc++.h>
using namespace std;
int MAX=100;
int main(){
    double A[MAX][MAX], B[MAX][MAX],C[MAX][MAX];
    for(int i=0;i<MAX;i++){
        for(int j=0;j<MAX;j++){
            double x = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
            double y = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);    
            A[i][j]=x;    
            B[i][j]=y;
        }           
    }


    auto begin = chrono::high_resolution_clock::now();    

    for (int i = 0; i < MAX; i++){
        for (int j = 0; j < MAX; j++){
            double temp=0;
            for (int k = 0; k < MAX; k++){
                temp=temp+(A[i][k]*B[k][j]);
                C[i][j]=temp;
            }    
        }
    }
    auto end = chrono::high_resolution_clock::now();    
    auto dur = end - begin;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
    cout <<"Clasico: "<< ms <<" millisecs"<< endl;
   
    
    begin = chrono::high_resolution_clock::now();    
    int b=5;
    for (int i0 = 0; i0 < MAX; i0+=b){
        for (int j0 = 0; j0 < MAX; j0+=b){
            for (int k0 = 0; k0 < MAX; k0+=b){
                for (int i = i0; i <min(i0+b-1,MAX); i++){
                    for (int j = j0; j < min(j0+b-1,MAX); j++){
                        
                        for (int k = k0; k < min(k0+b-1,MAX); k++){
                            C[i][j]=C[i][j]+(A[i][k]*B[k][j]);
                            
                        }    
                    }
                }           
            }    
        }
    }
    end = chrono::high_resolution_clock::now();    
    dur = end - begin;
    ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
    cout <<"Bloque: "<< ms <<" millisecs"<< endl;
   


/*TIEMPOS OBTENIDOS*/
    /*
 
    */
}