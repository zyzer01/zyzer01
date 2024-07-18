#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int roll_number;
    int marks;
} Student;

void add_learner(Student **learners, int *num_learners);
void edit_learner(Student *learners, int num_learners);
void show_learners(Student *learners, int num_learners);
void check_pass_fail(int passing_threshold);
void save_to_file(Student *learners, int num_learners);
void load_from_file(Student **learners, int *num_learners);
Student *find_by_roll_number(Student *learners, int num_learners, int roll_number);
void calculate_average_marks(Student *learners, int num_learners);
void sort_by_marks(Student *learners, int num_learners);

int main() {
    Student *learners = NULL;
    int num_learners = 0;
    int passing_threshold = 40;

    printf("Welcome to the Students Record System!\n");
    printf("Enter your name: ");
    char user_name[50];
    scanf("%s", user_name);
    printf("\nHello, %s!\n\n", user_name);

    while (1) {
        printf("Choose an option:\n");
        printf("1. Add learner\n");
        printf("2. Edit learner\n");
        printf("3. Show learners\n");
        printf("4. Save to file\n");
        printf("5. Load from file\n");
        printf("6. Find by roll number\n");
        printf("7. Calculate average marks\n");
        printf("8. Check pass or fail\n");
        printf("9. Sort by marks\n");
        printf("10. Exit\n");

        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_learner(&learners, &num_learners);
                break;
            case 2:
                edit_learner(learners, num_learners);
                break;
            case 3:
                show_learners(learners, num_learners);
                break;
            case 4:
                save_to_file(learners, num_learners);
                break;
            case 5:
                load_from_file(&learners, &num_learners);
                break;
            case 6:
                find_by_roll_number(learners, num_learners, 0);
                break;
            case 7:
                calculate_average_marks(learners, num_learners);
                break;
            case 8:
                check_pass_fail(passing_threshold);
                break;
            case 9:
                sort_by_marks(learners, num_learners);
                break;
            case 10:
                free(learners);
                return 0;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}

void add_learner(Student **learners, int *num_learners) {
    *learners = (Student *)realloc(*learners, sizeof(Student) * (*num_learners + 1));

    printf("\nEnter learner name: ");
    scanf("%s", (*learners)[*num_learners].name);

    printf("Enter roll number: ");
    scanf("%d", &(*learners)[*num_learners].roll_number);

    printf("Enter marks: ");
    scanf("%d", &(*learners)[*num_learners].marks);

    (*num_learners)++;

    printf("\nLearner added successfully!\n\n");
}

void edit_learner(Student *learners, int num_learners) {
    if (num_learners == 0) {
        printf("No learners to edit.\n");
        return;
    }

    int roll_number;
    printf("\nEnter roll number of the learner to edit: ");
    scanf("%d", &roll_number);

    Student *learner = find_by_roll_number(learners, num_learners, roll_number);

    if (learner != NULL) {
        printf("Enter new learner name: ");
        scanf("%s", learner->name);

        printf("Enter new roll number: ");
        scanf("%d", &learner->roll_number);

        printf("Enter new marks: ");
        scanf("%d", &learner->marks);
    } else {
        printf("Learner not found.\n");
    }
}

void show_learners(Student *learners, int num_learners) {
    if (num_learners == 0) {
        printf("No learners to show.\n");
        return;
    }

    printf("\nLearner Records:\n");
    for (int i = 0; i < num_learners; i++) {
        printf("Name: %s\n", learners[i].name);
        printf("Roll Number: %d\n", learners[i].roll_number);
        printf("Marks: %d\n", learners[i].marks);
        printf("-----------------\n");
    }
}

void check_pass_fail(int passing_threshold) {

    double learner_mark;
    printf("\nEnter the learner mark to check: ");
    scanf("%lf", &learner_mark);

    if (learner_mark > passing_threshold) {
        printf("\nLearner has passed.\n\n");
    } else {
        printf("\nLearner has failed.\n\n");
    }
}

void save_to_file(Student *learners, int num_learners) {
    if (num_learners == 0) {
        printf("No learners to save.\n");
        return;
    }

    FILE *file = fopen("learners.txt", "w");

    for (int i = 0; i < num_learners; i++) {
        fprintf(file, "%s %d %d\n", learners[i].name, learners[i].roll_number, learners[i].marks);
    }

    fclose(file);
    printf("\nLearners saved to file successfully.\n\n");
}

void load_from_file(Student **learners, int *num_learners) {
    FILE *file = fopen("learners.txt", "r");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    *num_learners = 0;
    char c;
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            (*num_learners)++;
        }
    }
    rewind(file);

    *learners = (Student *)malloc(sizeof(Student) * (*num_learners));

    for (int i = 0; i < *num_learners; i++) {
        fscanf(file, "%s %d %d", (*learners)[i].name, &(*learners)[i].roll_number, &(*learners)[i].marks);
    }

    fclose(file);
    printf("\nLearners loaded from file successfully.\n\n");
}

Student *find_by_roll_number(Student *learners, int num_learners, int roll_number) {
    if (num_learners == 0) {
        printf("No learners to search.\n");
        return NULL;
    }

    if (roll_number == 0) {
        printf("\nEnter roll number to search: ");
        scanf("%d", &roll_number);
    }

    for (int i = 0; i < num_learners; i++) {
        if (learners[i].roll_number == roll_number) {
            printf("Name: %s\n", learners[i].name);
            printf("Roll Number: %d\n", learners[i].roll_number);
            printf("Marks: %d\n", learners[i].marks);
            return &learners[i];
        }
    }

    printf("\nLearner not found.\n\n");
    return NULL;
}

void calculate_average_marks(Student *learners, int num_learners) {
    if (num_learners == 0) {
        printf("No learners to calculate average marks.\n");
        return;
    }

    int total_marks = 0;

    for (int i = 0; i < num_learners; i++) {
        total_marks += learners[i].marks;
    }

    double average_marks = (double)total_marks / num_learners;
    printf("\nAverage Marks: %.2f\n", average_marks);
}

void sort_by_marks(Student *learners, int num_learners) {
    if (num_learners == 0) {
        printf("No learners to sort.\n");
        return;
    }

    for (int i = 0; i < num_learners - 1; i++) {
        for (int j = 0; j < num_learners - i - 1; j++) {
            if (learners[j].marks < learners[j + 1].marks) {
                Student temp = learners[j];
                learners[j] = learners[j + 1];
                learners[j + 1] = temp;
            }
        }
    }

    printf("\nLearners sorted by marks in descending order:\n");
    show_learners(learners, num_learners);
}
