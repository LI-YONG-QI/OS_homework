#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#define RADIUS 1
#define N 30000

int sum;

pthread_mutex_t mutex_1 = PTHREAD_MUTEX_INITIALIZER;

// 子執行緒函數
void *runner(){
  srand(time(NULL));
  int i;
  int temp = 0;
  for(i = 0 ; i < N ; i++){
    double x = (double) rand() / (RAND_MAX);
    double y = (double) rand() / (RAND_MAX);
    if((x * x + y * y) < RADIUS){
      pthread_mutex_lock( &mutex_1 );
        sum++;
      pthread_mutex_unlock( &mutex_1 );
    }
  }
  // sum += temp;
  // printf("%d\n", temp);
  pthread_exit(0); // 傳回結果
}


// 主程式
int main() {
  sum = 0;
  void *ret1, *ret2, *ret3;  //宣告三個void指標變數
  pthread_t t1; // 宣告 pthread 變數
  pthread_t t2; // 宣告 pthread 變數
  pthread_t t3; // 宣告 pthread 變數
  pthread_create(&t1, NULL, runner, NULL); // 建立子執行緒
  pthread_create(&t2, NULL, runner, NULL); // 建立子執行緒
  pthread_create(&t3, NULL, runner, NULL); // 建立子執行緒

  pthread_join(t1, NULL); // 等待子執行緒執行完成
  pthread_join(t2, NULL); // 等待子執行緒執行完成
  pthread_join(t3, NULL); // 等待子執行緒執行完成

  //int sum = ((int *) ret1)[0] + ((int *) ret2)[0] + ((int *) ret3)[0];

  printf("PI = %f\n", (double) 4 * sum / (N*3));

  return 0;
}