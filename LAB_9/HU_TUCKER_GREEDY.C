#include <stdio.h>
#include <stdlib.h>

struct Node {
    int weight;
    struct Node *left, *right;
};

struct Node* createNode(int weight) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->weight = weight;
    node->left = node->right = NULL;
    return node;
}

void simulateHuTucker(int weights[], int n) {
    struct Node** nodes = (struct Node**)malloc(n * sizeof(struct Node*));
    for (int i = 0; i < n; i++) {
        nodes[i] = createNode(weights[i]);
    }
    
    int size = n;
    while (size > 1) {
        // Find the adjacent pair with the minimum sum
        int min_idx = 0;
        int min_sum = nodes[0]->weight + nodes[1]->weight;
        for (int i = 1; i < size - 1; i++) {
            int sum = nodes[i]->weight + nodes[i+1]->weight;
            if (sum < min_sum) {
                min_sum = sum;
                min_idx = i;
            }
        }
        
        // Merge nodes[min_idx] and nodes[min_idx + 1]
        struct Node* parent = createNode(min_sum);
        parent->left = nodes[min_idx];
        parent->right = nodes[min_idx + 1];
        
        nodes[min_idx] = parent;
        for (int i = min_idx + 1; i < size - 1; i++) {
            nodes[i] = nodes[i+1];
        }
        size--;
    }
    
    printf("\nOptimal Tree Root Weight: %d\n", nodes[0]->weight);
    free(nodes);
}

int main() {
    int n;
    
    printf("Enter the number of weights: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input.\n");
        return 1;
    }

    int* weights = (int*)malloc(n * sizeof(int));
    printf("Enter %d weights separated by spaces: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &weights[i]);
    }

    simulateHuTucker(weights, n);
    
    free(weights);
    return 0;
}