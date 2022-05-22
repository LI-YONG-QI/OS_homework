#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PAGE_NUMS 20


int pageSequence[PAGE_NUMS] = {7, 2, 3, 1, 2, 5, 3, 4, 6, 7, 7, 1, 0, 5, 4, 6, 2, 3, 0, 1};

int frameSize;
int* state;
int* stateOrder;
int pageFault = 0;

void getRandomPageSequence(){
    for (int i = 0; i < PAGE_NUMS; i++){
        pageSequence[i] = (rand()%10);
    }
}

void showPageSequence(){
    for (int i = 0; i < PAGE_NUMS; i++) printf("%d ",pageSequence[i]);
    printf("\n");
}

int checkInState(int element){
    int is_inState = 0;

    for(int i = 0 ; i < frameSize ; i++){
        if(state[i] == element){
            is_inState = 1;
            return is_inState;
        }
    }

    return is_inState;
}

int checkStateOrderIsEmpty(){
    int is_check = 0;

    for(int i = 0 ; i < frameSize ; i++){
        if(stateOrder[i] == -1){
            is_check = 1;
            return is_check;
        }
    }

    return is_check;
}

void initAll(){
    for(int i = 0 ; i < frameSize ; i++){
        state[i] = -1;
        stateOrder[i] = -1;
    }
    pageFault = 0;
}

void initStateOrder(){
    for(int i = 0 ; i < frameSize ; i++){
        stateOrder[i] = -1;
    }
}

void showState(){
    int i;
    for(i = 0 ; i < frameSize ; i++){
        printf("%d ", state[i]);
    }
    printf("\n");
}

int findStateIndex(int value){
    for(int i = 0 ; i < frameSize ; i++){
        if(state[i] == value){
            return i;
        }
    }
    return 0;
}

void updateStateOrder(int index){
    int i ;
    for(i = 0 ; i < frameSize ; i++){
        if(stateOrder[i] != -1){
            stateOrder[i] += 1;
        }  
    }
    stateOrder[index] = 0;
}

int findTargetIndex(int currentSequenceIndex){
    //update stateOrder
    initStateOrder();

    for(int i = currentSequenceIndex+1 ; i < PAGE_NUMS ; i++){
        if(checkInState(pageSequence[i]) == 1){
            updateStateOrder(findStateIndex(pageSequence[i]));
            if(checkStateOrderIsEmpty() == 0){
                break;
            }
        }
    }

    //find target index in stateOrder
    int temp = 0;
    for(int j = 0 ; j < frameSize ; j++){
        if(stateOrder[j] == -1){
            return j;
        }else if(stateOrder[j] == 0){
            temp = j;
        }   
    }
    return temp;
}

void appendElementInState(int element){
    int i;
    for(i = 0 ; i < frameSize ; i++){
        if(stateOrder[i] == -1 || stateOrder[i] == 2){
            state[i] = element;
            return;
        }
    }
}

void appendElementInOPAState(int element, int elementIndexInSequence){
    int i;
    for(i = 0 ; i < frameSize ; i++){
        if(state[i] == -1){
            state[i] = element;
            return;
        }
    }
    int target = findTargetIndex(elementIndexInSequence);
    state[target] = element;
}

void FIFO(){
    printf("\nFIFO algorithm start\n\n");

    for(int i = 0 ; i < PAGE_NUMS ; i++){
        if(checkInState(pageSequence[i]) == 0){
            appendElementInState(pageSequence[i]);
            updateStateOrder(findStateIndex(pageSequence[i]));
            pageFault += 1;
        }
        printf("current: %d ==> ", pageSequence[i]);
        showState(); 
    }
    printf("FIFO page falut is %d\n", pageFault);
}

void LRU(){
    printf("\nLRU algorithm start\n\n");

    for(int i = 0 ; i < PAGE_NUMS ; i++){
        if(checkInState(pageSequence[i]) == 0){
            appendElementInState(pageSequence[i]);
            pageFault += 1;
        }
        updateStateOrder(findStateIndex(pageSequence[i]));
        printf("current: %d ==> ", pageSequence[i]);
        showState(); 
    }
    printf("LRU page falut is %d\n", pageFault);
}

void OPA(){
    printf("\nOPA algorithm start\n\n");

    for(int i = 0 ; i < PAGE_NUMS ; i++){
        if(checkInState(pageSequence[i]) == 0){
            appendElementInOPAState(pageSequence[i], i);
            pageFault += 1;
        }
        printf("current: %d ==> ", pageSequence[i]);
        showState(); 
    }

    printf("OPA page fault is %d\n", pageFault);
}

int main(int argc, char* argv[]){
    frameSize = atoi(argv[1]);
    state = malloc(sizeof(int) * frameSize);
    stateOrder = malloc(sizeof(int) * frameSize);

    srand(time(NULL));
    getRandomPageSequence();
    showPageSequence();

    initAll();
    FIFO();

    initAll();
    LRU();

    initAll();
    OPA();

    return 0;
}