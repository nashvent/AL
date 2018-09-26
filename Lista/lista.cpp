#include <bits/stdc++.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
using namespace std;
int thread_count;
int member_count=100000;
int insert_count=10000;
int delete_count=10000;
int Tmember_count;
int Tinsert_count;
int Tdelete_count;
pthread_rwlock_t rwlock; 
pthread_mutex_t mutex_p;

struct list_node_s {
    int data;
    struct list_node_s* next;
    
};

int Member(int value, struct list_node_s* head_p) {
    struct list_node_s* curr_p = head_p;
    while (curr_p != NULL && curr_p->data < value)
        curr_p=curr_p->next;
    if(curr_p==NULL || curr_p->data>value){
        return 0;
    }
    else{
        return 1;
    }

}

int Insert(int value, struct list_node_s** head_p){
    struct list_node_s* curr_p=*head_p;
    struct list_node_s* pred_p=NULL;
    struct list_node_s* temp_p;
    while(curr_p!=NULL && curr_p->data<value){
        pred_p=curr_p;
        curr_p=curr_p->next;
    }
    
    if(curr_p==NULL || curr_p->data > value){
        temp_p=(list_node_s*) malloc(sizeof(struct list_node_s*));
        temp_p->data=value;
        temp_p->next=curr_p;
        if(pred_p==NULL)
            *head_p=temp_p;
        else
            pred_p->next=temp_p;
        return 1;
    }   else{
        return 0;
    }
}

int Remove(int value, struct list_node_s** head_p){
    
    struct list_node_s* curr_p=*head_p;
    struct list_node_s* pred_p=NULL;
    while(curr_p!=NULL && curr_p->data<value){
        pred_p=curr_p;
        curr_p=curr_p->next;
    }
    if(curr_p==NULL && curr_p->data == value){
        if(pred_p==NULL){
            *head_p=curr_p->next;
            free(curr_p);
        }else{
            pred_p->next=curr_p->next;
            free(curr_p);
        }

        return 1;
    }   else{
        return 0;
    }
}

/******************************************
 * 
 * Mutex per Node
 * 
*********************************************/





void Print(struct list_node_s**head_p){
    struct list_node_s* curr_p=*head_p;
    while(curr_p!=NULL ){
        cout<<curr_p->data<<" ";
        curr_p=curr_p->next;
    }
    cout<<endl;
}



/*READWIRTELOCKs*/
void* FuncEval(void *rootTemp){
    list_node_s *root=(list_node_s *)rootTemp;
    for(int x=0;x<Tinsert_count;x++){
        pthread_rwlock_rdlock(&rwlock);
        Insert(rand()%10001,&root);
        pthread_rwlock_unlock(&rwlock);
    }
    for(int x=0;x<Tmember_count;x++){
        pthread_rwlock_wrlock(&rwlock);
        Member(rand()%10001,root);
        pthread_rwlock_unlock(&rwlock);
    }
    for(int x=0;x<Tdelete_count;x++){
        pthread_rwlock_wrlock(&rwlock);
        Remove(rand()%10001,&root);
        pthread_rwlock_unlock(&rwlock);
    }
    return NULL;
}
/*MUTEX*/

void* FuncEvalMutex(void *rootTemp){
    list_node_s *root=(list_node_s *)rootTemp;
    for(int x=0;x<Tinsert_count;x++){
        pthread_mutex_lock(&mutex_p);
        Insert(rand()%10001,&root);
        pthread_mutex_unlock(&mutex_p);
    }
    for(int x=0;x<Tmember_count;x++){
        pthread_mutex_lock(&mutex_p);
        Member(rand()%10001,root);
        pthread_mutex_unlock(&mutex_p);
    }
    for(int x=0;x<Tdelete_count;x++){
        pthread_mutex_lock(&mutex_p);
        Remove(rand()%10001,&root);
        pthread_mutex_unlock(&mutex_p);
    }
    return NULL;
}

/**********************************************
 * 
 * Main
 * 
 * ********************************************/

int main(int argc, char* argv[]){
    long thread;
    pthread_t*thread_handles;
    thread_count=strtol(argv[1],NULL,10);
    thread_handles= (pthread_t*) malloc(thread_count * sizeof(pthread_t));    
    
    srand (time(NULL));
    list_node_s *root;
    root=new list_node_s();
    int elementos=5000;
    for(int x=0;x<elementos;x++){
        Insert(rand()%10001,&root);
    }
    Tmember_count=member_count/atoi(argv[1]);
    Tinsert_count=insert_count/atoi(argv[1]);
    Tdelete_count=delete_count/atoi(argv[1]);

    /*Read write locks*/
    clock_t tStart = clock();
    for(thread=0;thread<thread_count;thread++){
        pthread_create(&thread_handles[thread],NULL,
        FuncEval,(list_node_s *)root);
    }

    for(thread=0;thread<thread_count;thread++){
        pthread_join(thread_handles[thread],NULL);
    }

    cout<<"Tiempo RWL "<< (double)(clock() - tStart)/CLOCKS_PER_SEC<<endl;

    tStart = clock();
    for(thread=0;thread<thread_count;thread++){
        pthread_create(&thread_handles[thread],NULL,
        FuncEvalMutex,(list_node_s *)root);
    }

    for(thread=0;thread<thread_count;thread++){
        pthread_join(thread_handles[thread],NULL);
    }
    //FuncEval(root);
    cout<<"Tiempo MUTEX "<< (double)(clock() - tStart)/CLOCKS_PER_SEC<<endl;


    return 0;
}