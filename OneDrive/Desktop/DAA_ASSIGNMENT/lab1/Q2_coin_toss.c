#include <stdio.h>
#include <stdlib.h>
#include <time.h>


double simulate_coin(int num_tosses, double prob_head) {
    int heads_count = 0;

    for (int i = 0; i < num_tosses; i++) {
        
        double r = (double)rand() / RAND_MAX;
        if (r < prob_head) {
            heads_count++;
        }
    }

    return (double)heads_count / num_tosses;
}

int main() {
   
    srand((unsigned int)time(NULL));

    int tosses[] = {100, 1000, 10000, 100000, 1000000};
    int num_experiments = sizeof(tosses) / sizeof(tosses[0]);

    double fair_prob = 0.50;   
    double biased_prob = 0.75; 


    printf("%-15s | %-20s | %-20s\n", "No. of Tosses", "Fair Coin P(HEAD)", "Biased Coin P(HEAD)");


    for (int i = 0; i < num_experiments; i++) {
        int num_tosses = tosses[i];

        double fair_result = simulate_coin(num_tosses, fair_prob);
        double biased_result = simulate_coin(num_tosses, biased_prob);

        printf("%-15d | %-20.5f | %-20.5f\n", num_tosses, fair_result, biased_result);
    }

    printf("\nConclusion:\n");
    printf("- As the number of tosses increases, the fair coin probability converges towards 0.5.\n");
    printf("- The biased coin consistently converges towards its true bias (0.75).\n");

    return 0;
}
/*Sample output :
No. of Tosses   | Fair Coin P(HEAD)    | Biased Coin P(HEAD) 
100             | 0.51000              | 0.74000             
1000            | 0.53700              | 0.78500             
10000           | 0.49500              | 0.75240             
100000          | 0.50157              | 0.74875             
1000000         | 0.50064              | 0.75045             

Conclusion:
- As the number of tosses increases, the fair coin probability converges towards 0.5.
- The biased coin consistently converges towards its true bias (0.75).*/