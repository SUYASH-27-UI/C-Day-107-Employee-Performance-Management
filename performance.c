
#include <stdio.h>
#include <string.h>

#define MAX 100
#define FILE_NAME "employees.txt"

struct Employee {
    int id;
    char name[50];
    float score;
};

void saveData(struct Employee e[], int count) {
    FILE *fp = fopen(FILE_NAME, "w");

    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d|%s|%.2f\n",
                e[i].id, e[i].name, e[i].score);
    }

    fclose(fp);
}

int loadData(struct Employee e[]) {
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) return 0;

    int count = 0;

    while (count < MAX &&
           fscanf(fp, "%d|%49[^|]|%f",
                  &e[count].id, e[count].name,
                  &e[count].score) == 3) {
        count++;
    }

    fclose(fp);
    return count;
}

int findEmployee(struct Employee e[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (e[i].id == id) return i;
    }
    return -1;
}

void addEmployee(struct Employee e[], int *count) {
    if (*count >= MAX) {
        printf("Employee limit reached!\n");
        return;
    }

    int id;

    printf("Enter Employee ID: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID!\n");
        return;
    }

    if (findEmployee(e, *count, id) != -1) {
        printf("Employee ID already exists!\n");
        return;
    }

    e[*count].id = id;

    printf("Enter Employee Name: ");
    scanf(" %49[^\n]", e[*count].name);

    printf("Enter Performance Score (0-100): ");
    if (scanf("%f", &e[*count].score) != 1 ||
        e[*count].score < 0 || e[*count].score > 100) {
        printf("Invalid score!\n");
        return;
    }

    (*count)++;
    saveData(e, *count);
    printf("Employee added successfully!\n");
}

void viewEmployees(struct Employee e[], int count) {
    if (count == 0) {
        printf("No employee records found.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("\nID: %d\nName: %s\nScore: %.2f\n",
               e[i].id, e[i].name, e[i].score);
    }
}

void searchEmployee(struct Employee e[], int count) {
    int id;

    printf("Enter Employee ID: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID!\n");
        return;
    }

    int index = findEmployee(e, count, id);

    if (index == -1) {
        printf("Employee not found.\n");
    } else {
        printf("Name: %s\nScore: %.2f\n",
               e[index].name, e[index].score);
    }
}

void updateScore(struct Employee e[], int count) {
    int id;
    float score;

    printf("Enter Employee ID: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID!\n");
        return;
    }

    int index = findEmployee(e, count, id);

    if (index == -1) {
        printf("Employee not found.\n");
        return;
    }

    printf("Enter New Score (0-100): ");
    if (scanf("%f", &score) != 1 || score < 0 || score > 100) {
        printf("Invalid score!\n");
        return;
    }

    e[index].score = score;
    saveData(e, count);

    printf("Performance score updated!\n");
}

void averageScore(struct Employee e[], int count) {
    if (count == 0) {
        printf("No records available.\n");
        return;
    }

    float total = 0;

    for (int i = 0; i < count; i++) {
        total += e[i].score;
    }

    printf("Average Performance Score: %.2f\n",
           total / count);
}

int main() {
    struct Employee employees[MAX];
    int count = loadData(employees);
    int choice;

    while (1) {
        printf("\n===== EMPLOYEE PERFORMANCE SYSTEM =====\n");
        printf("1. Add Employee\n");
        printf("2. View Employees\n");
        printf("3. Search Employee\n");
        printf("4. Update Performance Score\n");
        printf("5. Average Performance Score\n");
        printf("6. Exit\n");
        printf("Enter Choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            break;
        }

        switch (choice) {
            case 1: addEmployee(employees, &count); break;
            case 2: viewEmployees(employees, count); break;
            case 3: searchEmployee(employees, count); break;
            case 4: updateScore(employees, count); break;
            case 5: averageScore(employees, count); break;
            case 6:
                printf("Program closed.\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
