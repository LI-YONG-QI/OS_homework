#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#define n 10

pthread_mutex_t northSelfMutex;
pthread_mutex_t southSelfMutex;

pthread_mutex_t northPublicMutex;
pthread_mutex_t southPublicMutex;

int northCount;
int southCount;

double min = 0;
double max = 30;

void *northRunner(int* index){
  srand(time(NULL));
  double time = (max - min) * rand() / (RAND_MAX + 1.0) + min;
  sleep(time);
  printf("[%d] North bound farmar want to across the bridge...\n",*index);

  pthread_mutex_lock(&northPublicMutex);
  pthread_mutex_unlock(&northPublicMutex);

  pthread_mutex_lock(&northSelfMutex);
  northCount++;
  if(northCount == 1){
    pthread_mutex_lock(&southPublicMutex);
  }
  pthread_mutex_unlock(&northSelfMutex);

  //perform
  printf("[%d] North bound farmar is walking bridge\n", *index);
  sleep(time);
  printf("[%d] North bound farmar is leaving bridge\n", *index);

  pthread_mutex_lock(&northSelfMutex);
  northCount--;
  if(northCount == 0){
    pthread_mutex_unlock(&southPublicMutex);   //southRunner 可以執行
    printf("\nThe bridge is empty\n\n"); 
  }
  pthread_mutex_unlock(&northSelfMutex);

  pthread_exit(0);
}

void *southRunner(int* index){
  srand(time(NULL));
  double time = (max - min) * rand() / (RAND_MAX + 1.0) + min;
  sleep(time);
  printf("[%d] South bound farmar want to across the bridge...\n",*index);

  pthread_mutex_lock(&southPublicMutex);
  pthread_mutex_unlock(&southPublicMutex);

  pthread_mutex_lock(&southSelfMutex);
  southCount++;
  if(southCount == 1){
    pthread_mutex_lock(&northPublicMutex);
  }
  pthread_mutex_unlock(&southSelfMutex);

  //perform
  printf("[%d] South bound farmar is walking bridge\n", *index);
  sleep(time);
  printf("[%d] South bound farmar is leaving bridge\n", *index);

  // sleep
  sleep(time);

  pthread_mutex_lock(&southSelfMutex);
  southCount--;
  if(southCount == 0){
    pthread_mutex_unlock(&northPublicMutex);
    
    printf("\nThe bridge is empty\n\n");
  }
  pthread_mutex_unlock(&southSelfMutex);

  pthread_exit(0);
}


int main() 
{
  int ids[10] = {0,1,2,3,4,5,6,7,8,9};

  northCount = 0;
  southCount = 0; 

  pthread_mutex_init(&northSelfMutex, NULL);
  pthread_mutex_init(&southSelfMutex, NULL);
  pthread_mutex_init(&northPublicMutex, NULL);
  pthread_mutex_init(&southPublicMutex, NULL);

  pthread_t *northBound = (pthread_t *) malloc(sizeof(pthread_t) * n);
  pthread_t *southBound = (pthread_t *) malloc(sizeof(pthread_t) * n);

  int count;
  int i;
  int x;

  for(count = 0 ; count < 2 ; count++){
    //north first
    for(i = 0 ; i < 5 ; i++){
        pthread_create(&northBound[i], NULL, northRunner, &ids[i]);
        pthread_create(&southBound[i], NULL, southRunner, &ids[i]);
    }

    //north first
    for(x = 5 ; x < 10 ; x++){
      pthread_create(&southBound[i], NULL, southRunner, &ids[x]);
      pthread_create(&northBound[i], NULL, northRunner, &ids[x]); 
    }
  }

  int j;
  for( j = 0 ; j < n ; j++){
    pthread_join(northBound[j], NULL);
    pthread_join(southBound[j], NULL);
  }
  
  return 0;
}