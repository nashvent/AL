#include <stdio.h>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <omp.h>
using namespace std;


int main(int argc,char* argv[]){
    int thread_count=strtol(argv[1],NULL,10);
    string sz=argv[2];
    int size=atoi( sz.c_str());;
    
    vector<int>vect(size);
    vector<int>vect2(size);
    vector<vector<int> > matrix(size, vector<int> (size,0));
    int i,j;
    clock_t tStart = clock();

    # pragma omp parallel for num_threads(thread_count) default(none) private(i,j) shared(matrix,vect,vect2,size)
    for(i=0;i<size;i++){
        vect2[i]=0.0;
        for(j=0;j<size;j++){
            vect2[i]+=matrix[i][j]*vect[j];
        }
    }

    cout<<"matriz "<< (double)(clock() - tStart)/CLOCKS_PER_SEC<<endl;
   
    return 0;
}

