#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUM_EMPLOYEES 3
#define INF 1e9

// Structure for a book
typedef struct {
    int num_pages;
} Book;

// Function to calculate the maximum of two values
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to find optimal cutting points using dynamic programming
void divide_books(Book *books, int num_books, int limits[NUM_EMPLOYEES - 1], int sums[NUM_EMPLOYEES]) {
    int cumulative_sums[num_books];

    // Calculating cumulative sums of pages
    cumulative_sums[0] = books[0].num_pages;
    for (int i = 1; i < num_books; i++) {
        cumulative_sums[i] = cumulative_sums[i - 1] + books[i].num_pages;
    }

    int dp[num_books + 1][NUM_EMPLOYEES + 1];
    int parent[num_books + 1][NUM_EMPLOYEES + 1];

    // Initialization
    for (int i = 0; i <= num_books; i++) {
        for (int j = 0; j <= NUM_EMPLOYEES; j++) {
            dp[i][j] = (j == 0 && i == 0) ? 0 : INF;
            parent[i][j] = -1;
        }
    }

    // Calculating DP values
    for (int j = 1; j <= NUM_EMPLOYEES; j++) {
        for (int i = 1; i <= num_books; i++) {
            for (int k = 0; k < i; k++) {
                int cost = (k == 0) ? cumulative_sums[i - 1] : cumulative_sums[i - 1] - cumulative_sums[k - 1];
                if (dp[i][j] > max(dp[k][j - 1], cost)) {
                    dp[i][j] = max(dp[k][j - 1], cost);
                    parent[i][j] = k;
                }
            }
        }
    }

    // Reconstructing cutting points
    int idx = num_books;
    for (int j = NUM_EMPLOYEES; j > 1; j--) {
        limits[j - 2] = parent[idx][j] - 1;
        idx = parent[idx][j];
    }

    // Calculating sums for each employee
    for (int i = 0; i < NUM_EMPLOYEES; i++) {
        int start = (i == 0) ? 0 : limits[i - 1] + 1;
        int end = (i == NUM_EMPLOYEES - 1) ? num_books - 1 : limits[i];
        for (int j = start; j <= end; j++) {
            sums[i] += books[j].num_pages;
        }
    }
}

int main() {
    // Input number of books
    int num_books;
    printf("Enter the number of books: ");
    scanf("%d", &num_books);

    // Memory allocation for the array of books
    Book *books = (Book *)malloc(num_books * sizeof(Book));

    // Input number of pages for each book
    printf("Enter the number of pages for each book:\n");
    for (int i = 0; i < num_books; i++) {
        printf("Book %d: ", i + 1);
        scanf("%d", &books[i].num_pages);
    }

    // Allocating pages for each employee
    int limits[NUM_EMPLOYEES - 1] = {0};
    int sums[NUM_EMPLOYEES] = {0};
    divide_books(books, num_books, limits, sums);

    // Displaying each employee's workload and sum of pages
    printf("\nWorkload for each employee:\n");
    for (int i = 0; i < NUM_EMPLOYEES; i++) {
        printf("Employee %d: ", i + 1);
        int start = (i == 0) ? 0 : limits[i - 1] + 1;
        int end = (i == NUM_EMPLOYEES - 1) ? num_books - 1 : limits[i];
        for (int j = start; j <= end; j++) {
            printf("%d ", books[j].num_pages);
        }
        printf("(Total: %d pages)\n", sums[i]);
    }
    printf("\n");

    // Freeing allocated memory for the array of books
    free(books);

    return 0;
}

