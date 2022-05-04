#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#define RADIUS 1
#define N 100001


// 子執行緒函數
void *runner (){

  srand(time(NULL));
  int i;
  int *result = malloc(sizeof(int) * 1);
  result[0] = 0;

  for(i = 0 ; i < N ; i++){
    double x = (double) rand() / (RAND_MAX);
    double y = (double) rand() / (RAND_MAX);
    if(x * x + y * y < RADIUS){
      result[0]++;
    }
  }
  pthread_exit((void *) result); // 傳回結果
}


// 主程式
int main() {
  void *ret1, *ret2, *ret3;
  pthread_t t1; // 宣告 pthread 變數
  pthread_t t2; // 宣告 pthread 變數
  pthread_t t3; // 宣告 pthread 變數
  pthread_create(&t1, NULL, runner, NULL); // 建立子執行緒
  // pthread_create(&t2, NULL, runner, NULL); // 建立子執行緒
  // pthread_create(&t3, NULL, runner, NULL); // 建立子執行緒

  pthread_join(t1, &ret1); // 等待子執行緒執行完成
  // pthread_join(t2, &ret2); // 等待子執行緒執行完成
  // pthread_join(t3, &ret3); // 等待子執行緒執行完成

  int *sum = (int *) ret1 ;

  printf("PI = %f\n", (double) 4 * sum[0] / (N - 1));

  return 0;
}