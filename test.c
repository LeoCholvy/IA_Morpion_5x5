#include <stdio.h>



int main(){
    int test[3];
    for (int i=0;i<3;i++){
        test[i] = i;
    }
    int *stonks[2];
    for (int i=0;i<2;i++){
        stonks[i] = &test[i];
    }
    test[0] = 42;
    for (int i=0;i<2;i++){
        printf("%d\n", *stonks[i]);
    }
}
