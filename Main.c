#include <stdio.h>
#include <stdbool.h>

int main () {
    int i,j;
    for (i=4;i>=0;i--){
        for (j=0;j<5;j++){
            printf("%d | %d\n", i, j);
        }
    }
}
