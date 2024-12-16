#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int id;
    char name[50];
    int age;
} User;

// Function to create a new user file if it doesn't exist
void createFile() {
    FILE *filePtr = fopen("users.txt", "w");
    if (filePtr == NULL) {
        printf("Error creating file!\n");
        exit(1);
    }
    fclose(filePtr);
}

// Function to add a new user to the file
void addUser() {
    FILE *filePtr = fopen("users.txt", "a");
    if (filePtr == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    User user;
    printf("Enter User ID: ");
    scanf("%d", &user.id);
    printf("Enter User Name: ");
    scanf("%s", user.name);
    printf("Enter User Age: ");
    scanf("%d", &user.age);

    fprintf(filePtr, "%d %s %d\n", user.id, user.name, user.age);
    fclose(filePtr);
    printf("User added successfully!\n");
}

// Function to read and display all users
void displayUsers() {
    FILE *filePtr = fopen("users.txt", "r");
    if (filePtr == NULL) {
        printf("Error opening file!\n");
        return;
    }

    User user;
    int foundUser = 0;
    printf("\n--- User List ---\n");

    printf("\nID\tName\tAge\n");
    printf("---------------------\n");
    while (fscanf(filePtr, "%d %s %d", &user.id, user.name, &user.age) == 3) {
        printf("%d\t%s\t%d\n", user.id, user.name, user.age);
    }
    if(!foundUser){
        printf("No user found  \n");
    }
    fclose(filePtr);
}

// Function to update a user's details
void updateUser() {
    FILE *filePtr = fopen("users.txt", "r");
    FILE *tempf = fopen("temp.txt", "w");
    if (filePtr == NULL || tempf == NULL) {
        printf("Error opening file.\n");
        return;
    }

    User user;
    int Id, found = 0;
    printf("Enter User ID to update: ");
    scanf("%d", &Id);

    while (fscanf(filePtr, "%d %s %d", &user.id, user.name, &user.age) == 3) {
        if (user.id == Id) {
            found = 1;
            printf("Enter updated User ID: ");
            scanf("%d", &user.id);
            printf("Enter updated Name: ");
            scanf("%s", user.name);
            printf("Enter updated Age: ");
            scanf("%d", &user.age);
        }
        fprintf(tempf, "%d %s %d\n", user.id, user.name, user.age);
    }

    fclose(filePtr);
    fclose(tempf);

    if (found) {
        remove("users.txt");
        rename("temp.txt", "users.txt");
        printf("User updated successfully!\n");
    } else {
        printf("User not found.\n");
        remove("temp.txt");
    }
}

// Function to delete a user
void deleteUser() {
    FILE *filePtr = fopen("users.txt", "r");
    FILE *tempf = fopen("temp.txt", "w");
    if (filePtr == NULL || tempf == NULL) {
        printf("Error opening file.\n");
        return;
    }

    User user;
    int id, found = 0;
    printf("Enter User ID to delete: ");
    scanf("%d", &id);

    while (fscanf(filePtr, "%d %s %d", &user.id, user.name, &user.age) == 3) {
        if (user.id != id) {
            fprintf(tempf, "%d %s %d\n", user.id, user.name, user.age);
        } else {
            found = 1;
        }
    }

    fclose(filePtr);
    fclose(tempf);

    if (found) {
        remove("users.txt");
        rename("temp.txt", "users.txt");
        printf("User deleted successfully!\n");
    } else {
        printf("User not found.\n");
        remove("temp.txt");
    }
}

// To get a valid choice, no invalid input
int getValidChoice() {
    int choice;
    char input[5];
    while (1) {
        printf("Enter your choice: ");
        if (fgets(input, sizeof(input), stdin)) {
            if (sscanf(input, "%d", &choice) == 1 && choice >= 1 && choice <= 5) {
                return choice;
            } else {
                printf("Please enter a valid choice (1-5).\n");
            }
        }
    }
}
//main function
int main() {
    int choice;
    createFile();

    do {
        printf("\n1. Add User\n2. Display Users\n3. Update User\n4. Delete User\n5. Exit\n");
        choice = getValidChoice();

        switch (choice) {
            case 1:
                addUser();
                break;
            case 2:
                displayUsers();
                break;
            case 3:
                updateUser();
                break;
            case 4:
                deleteUser();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 5);

    return 0;
}
