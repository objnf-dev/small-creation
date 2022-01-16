/*
 * Count the horse.
 * ZWT. 18/11/2
*/
#include <stdio.h>

int main() {
    int smallHorse,middleHorse,bigHorse,sum1,sum2;
    for(smallHorse=0;smallHorse<=100;smallHorse+=2)
        for(middleHorse=0;middleHorse<=50;middleHorse++)
            for(bigHorse=0;bigHorse<=34;bigHorse++)
            {
                sum1=smallHorse+middleHorse+bigHorse;   // Calculate the horse number
                sum2=smallHorse/2+middleHorse*2+bigHorse*3;  // Calculate the weight of goods.
                if(sum1 ==100 && sum2 == 100)
                    printf("small=%d middle=%d big=%d\n",smallHorse,middleHorse,bigHorse);  // Output
            }
    return 0;
}