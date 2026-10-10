#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    double v;       // Base value
    double w;       // Weight
    double lambda;  // Decay rate
    double density; // Initial value density v/w
} Item;

// Greedy sorting rule: items with high decay / initial density rank higher
int compareItems(const void *a, const void *b) {
    Item *itemA = (Item *)a;
    Item *itemB = (Item *)b;
    
    // Custom heuristic score balancing density and decay rate
    double scoreA = itemA->density + itemA->lambda;
    double scoreB = itemB->density + itemB->lambda;

    if (scoreB > scoreA) return 1;
    if (scoreB < scoreA) return -1;
    return 0;
}

double solveFractionalKnapsackDeteriorating(Item items[], int n, double W) {
    // 1. Sort items according to greedy heuristic
    qsort(items, n, sizeof(Item), compareItems);

    double totalValue = 0.0;
    double currentWeight = 0.0; // Acts as elapsed time t

    printf("Processing Order:\n");
    for (int i = 0; i < n; i++) {
        if (currentWeight >= W) break;

        double remainingCap = W - currentWeight;
        double weightToTake = (items[i].w <= remainingCap) ? items[i].w : remainingCap;

        // Effective density integrated over the weight consumed:
        // Density at start t1 = (v/w) - lambda * t1
        // Density at end   t2 = (v/w) - lambda * t2
        double t1 = currentWeight;
        double t2 = currentWeight + weightToTake;
        double avgDensity = items[i].density - items[i].lambda * ((t1 + t2) / 2.0);

        if (avgDensity < 0) avgDensity = 0; // Prevent negative value contribution

        double valueGained = weightToTake * avgDensity;
        totalValue += valueGained;
        currentWeight += weightToTake;

        printf("Item %d: Took weight %.2f, Value Gained: %.2f\n", 
               items[i].id, weightToTake, valueGained);
    }

    return totalValue;
}

int main() {
    int n = 3;
    double W = 10.0;

    Item items[] = {
        {1, 30.0, 5.0, 1.0, 30.0 / 5.0}, // Density = 6, Lambda = 1.0
        {2, 40.0, 5.0, 0.1, 40.0 / 5.0}, // Density = 8, Lambda = 0.1
        {3, 20.0, 4.0, 0.5, 20.0 / 4.0}  // Density = 5, Lambda = 0.5
    };

    double maxValue = solveFractionalKnapsackDeteriorating(items, n, W);
    printf("Maximum Total Value: %.2f\n", maxValue);

    return 0;
}