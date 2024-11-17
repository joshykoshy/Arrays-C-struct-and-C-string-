#include <stdio.h>
#include <stdbool.h>

/*Definitions to be used in the code*/
#define SIZE 24
#define nRows 8
#define nCols 3

/* Function Prototypes */
bool isValid(const int arr[], int length, int pos);
void remove_element(int arr[], int length, int pos);
void insert_element(int arr[], int length, int pos, int value);
void reshape(const int arr[], int length, int rows, int cols, int arr2d[rows][cols]);
void trans_matrix(int rows, int cols, const int arr2d[rows][cols], int transposed[cols][rows]);
bool found_duplicate(const int arr[], int length);
void print_array(int arr[], int length);
void print_matrix(int rows, int cols, int arr2d[rows][cols]);

int main() {
    /* Initialize a 1D array */
    int arr[SIZE];
    for (int i = 0; i < SIZE; i++) {
        arr[i] = (i + 1) * 5;
    }

    /* Initialize a 2D array and a transposed array */
    int arr2d[nRows][nCols];
    int transposed[nCols][nRows];

    /* We print the 1D array */
    printf("Running print_array function:\n");
    print_array(arr, SIZE);

    printf("\n********************\n");

    /* Test isValid function */
    printf("Testing isValid function:\n");
    printf("isValid(arr, SIZE, 5) = %d\n", isValid(arr, SIZE, 5));  /* Should return true because its a valid position*/
    printf("isValid(arr, SIZE, 25) = %d\n", isValid(arr, SIZE, 25)); /* Should return false because its an invalid position*/

    printf("\n********************\n");

    /* Test remove_element function */
    printf("Testing remove_element function:\n");
    printf("Before removing element at position 5:\n");
    print_array(arr, SIZE);
    remove_element(arr, SIZE, 5);
    printf("After removing element at position 5:\n");
    print_array(arr, SIZE);

    printf("\n********************\n");

    /* Test insert_element function */
    printf("Testing insert_element function:\n");
    insert_element(arr, SIZE, 5, 100);  // Insert 100 at position 5
    printf("After inserting 100 at position 5:\n");
    print_array(arr, SIZE);

    printf("\n********************\n");

    /* Test found_duplicate function */
    printf("Testing found_duplicate function:\n");
    printf("found_duplicate(arr, SIZE) = %d\n", found_duplicate(arr, SIZE)); 

    printf("\n********************\n");

    /* We populate and print the 2D array */
    printf("Populating 2D array for print_matrix function:\n");
    if (SIZE == nRows * nCols) {
        reshape(arr, SIZE, nRows, nCols, arr2d);
        print_matrix(nRows, nCols, arr2d);
    } else {
        printf("Error: Array size does not match matrix dimensions.\n");
    }

    printf("\n********************-\n");

    /* Transpose and print the 2D array */
    printf("Transposed matrix:\n");
    trans_matrix(nRows, nCols, arr2d, transposed);
    print_matrix(nCols, nRows, transposed);

    return 0;
}

/* Check if the position is valid */
bool isValid(const int arr[], int length, int pos) {
    return pos >= 0 && pos < length;
}

/* Remove an element from the array */
void remove_element(int arr[], int length, int pos) {
    if (!isValid(arr, length, pos)) {
        printf("Invalid position: %d\n", pos);
        return;
    }
    for (int i = pos; i < length - 1; i++) {
        arr[i] = arr[i + 1];
    }
    arr[length - 1] = 0;
}

/* Insert an element into the array */
void insert_element(int arr[], int length, int pos, int value) {
    if (!isValid(arr, length, pos)) {
        printf("Invalid position: %d\n", pos);
        return;
    }
    for (int i = length - 1; i > pos; i--) {
        arr[i] = arr[i - 1];
    }
    arr[pos] = value;
}

/* Reshape a 1D array into a 2D array */
void reshape(const int arr[], int length, int rows, int cols, int arr2d[rows][cols]) {
    if (length != rows * cols) {
        printf("Error: The array size does not match the matrix dimensions.\n");
        return;
    }
    int index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr2d[i][j] = arr[index++];
        }
    }
}

/* Transpose a 2D array */
void trans_matrix(int rows, int cols, const int arr2d[rows][cols], int transposed[cols][rows]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transposed[j][i] = arr2d[i][j];
        }
    }
}

/* Check for duplicates in the array */
bool found_duplicate(const int arr[], int length) {
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            if (arr[i] == arr[j]) {
                return true;
            }
        }
    }
    return false;
}

/* Print a 1D array */
void print_array(int arr[], int length) {
    for (int i = 0; i < length; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
}

/* Print a 2D array */
void print_matrix(int rows, int cols, int arr2d[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("arr2d[%d][%d] = %d\n", i, j, arr2d[i][j]);
        }
        puts(""); 
    }
}
