#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    int age;
} User;

// Function to create a new user file if it doesn't exist
void createFile() {
    FILE *fp = fopen("users.txt", "w");
    if (fp == NULL) {
        printf("Error creating file!\n");
        exit(1);
    }
    fclose(fp);
}

// Function to add a new user to the file
void addUser() {
    FILE *fp = fopen("users.txt", "a");
    if (fp == NULL) {
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

    fprintf(fp, "%d %s %d\n", user.id, user.name, user.age);
    fclose(fp);
    printf("User added successfully!\n");
}

// Function to read and display all users
void displayUsers() {
    FILE *fp = fopen("users.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    User user;
    printf("ID\tName\tAge\n");
    while (fscanf(fp, "%d %s %d", &user.id, user.name, &user.age) != EOF) {
        printf("%d\t%s\t%d\n", user.id, user.name, user.age);
    }
    fclose(fp);
}

// Function to update a user's details
void updateUser() {
    FILE *fp = fopen("users.txt", "r+");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    int id;
    printf("Enter User ID to update: ");
    scanf("%d", &id);

    User user;
    int found = 0;
    while (fscanf(fp, "%d %s %d", &user.id, user.name, &user.age) != EOF) {
        if (user.id == id) {
            found = 1;
            printf("Enter new name: ");
            scanf("%s", user.name);
            printf("Enter new age: ");
            scanf("%d", &user.age);
            fseek(fp, -sizeof(user), SEEK_CUR);
            fprintf(fp, "%d %s %d\n", user.id, user.name, user.age);
            break;
        }
    }

    if (!found) {
        printf("User not found!\n");
    }

    fclose(fp);
}

// Function to delete a user
void deleteUser() {
    FILE *fp = fopen("users.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Error creating temporary file!\n");
        exit(1);
    }

    int id;
    printf("Enter User ID to delete: ");
    scanf("%d", &id);

    User user;
    int found = 0;
    while (fscanf(fp, "%d %s %d", &user.id, user.name, &user.age) != EOF) {
        if (user.id != id) {
            fprintf(temp, "%d %s %d\n", user.id, user.name, user.age);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("users.txt");
    rename("temp.txt", "users.txt");

    if (!found) {
        printf("User not found!\n");
    } else {
        printf("User deleted successfully!\n");
    }
}

int main() {
    int choice;
    createFile();

    do {
        printf("\n1. Add User\n2. Display Users\n3. Update User\n4. Delete User\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

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
                printf("Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}