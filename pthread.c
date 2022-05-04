#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#define RADIUS 1
#define N 1000


// 子執行緒函數
// void *runner (){
//   srand()
// }

// double calculateDistance(double x, double y){
  
// }

// 主程式
int main() {
  // pthread_t t; // 宣告 pthread 變數
  // pthread_create(&t, NULL, runner, ""); // 建立子執行緒

  // // 主執行緒工作
  // for(int i = 0;i < 3;++i) {
  //   printf("Master\n"); // 每秒輸出文字
  //   sleep(1);
  // }

  // pthread_join(t, NULL); // 等待子執行緒執行完成

  srand(time(NULL));

  int sum = 0;
  double min = 0.0;
  double max = 2*RADIUS;
  

  int i;
  for(i = 0 ; i < N ; i++){
    double x = (max) * rand() / (RAND_MAX + 1.0);
    double y = (max) * rand() / (RAND_MAX + 1.0);
    if(x * x + y * y < RADIUS){
      sum++;
    }
    printf("PI = %f\n", (double) 4 * sum / (N - 1));
  }
  

  return 0;
}