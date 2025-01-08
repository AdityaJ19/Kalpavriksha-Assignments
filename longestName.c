#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME_LENGTH 50
#define MAX_ROWS 10
#define MAX_COLUMNS 101

// Function to check if a character is a vowel
int isVowel(char c) {
   
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

int main() {
    int rows, cols;
    char names[MAX_ROWS][MAX_COLUMNS][MAX_NAME_LENGTH];


    printf("Enter number of rows (1-10): ");
    scanf("%d", &rows);
    while (rows < 1 || rows > 10) {
        printf("Invalid input. Enter number of rows (1-10): ");
        scanf("%d", &rows);
    }

    printf("Enter number of columns (1-101): ");
    scanf("%d", &cols);
    while (cols < 1 || cols > 101) {
        printf("Invalid input. Enter number of columns (1-101): ");
        scanf("%d", &cols);
    }

    printf("Enter the names:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Name at (%d,%d): ", i, j);
            scanf("%s", names[i][j]);
        }
    }

    
    printf("\nThe 2D array of names is:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%s ", names[i][j]);
        }
        printf("\n");
    }

    
    int vowelCount = 0;
    char longestName[MAX_NAME_LENGTH] = "";

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (isVowel(names[i][j][0])) {
                vowelCount++;
            }
            if (strlen(names[i][j]) > strlen(longestName)) {
                strcpy(longestName, names[i][j]);
            }
        }
    }

    // Display results
    printf("\nNumber of names starting with a vowel: %d\n", vowelCount);
    printf("The longest name: %s\n", longestName);

    return 0;
}