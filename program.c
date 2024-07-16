#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int roll_number;
    int marks;
} Student;

void add_student(Student **students, int *num_students);
void modify_student(Student *students, int num_students);
void display_students(Student *students, int num_students);
void check_pass_fail(int passing_threshold);
void save_to_file(Student *students, int num_students);
void load_from_file(Student **students, int *num_students);
Student *search_by_roll_number(Student *students, int num_students, int roll_number);
void calculate_average_marks(Student *students, int num_students);
void sort_by_marks(Student *students, int num_students);

int main() {
    Student *students = NULL;
    int num_students = 0;
    int passing_threshold = 40;

    printf("Welcome to the Student Record System!\n");
    printf("Enter your name: ");
    char user_name[50];
    scanf("%s", user_name);
    printf("\nHello, %s!\n\n", user_name);

    while (1) {
        printf("Choose an option:\n");
        printf("1. Add student\n");
        printf("2. Modify student\n");
        printf("3. Display students\n");
        printf("4. Save to file\n");
        printf("5. Load from file\n");
        printf("6. Search by roll number\n");
        printf("7. Calculate average marks\n");
        printf("8. Check pass or fail\n");
        printf("9. Sort by marks\n");
        printf("10. Exit\n");

        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_student(&students, &num_students);
                break;
            case 2:
                modify_student(students, num_students);
                break;
            case 3:
                display_students(students, num_students);
                break;
            case 4:
                save_to_file(students, num_students);
                break;
            case 5:
                load_from_file(&students, &num_students);
                break;
            case 6:
                search_by_roll_number(students, num_students, 0);
                break;
            case 7:
                calculate_average_marks(students, num_students);
                break;
            case 8:
                check_pass_fail(passing_threshold);
                break;
            case 9:
                sort_by_marks(students, num_students);
                break;
            case 10:
                free(students);
                return 0;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}


void add_student(Student **students, int *num_students) {
    *students = (Student *)realloc(*students, sizeof(Student) * (*num_students + 1));

    printf("\nEnter student name: ");
    scanf("%s", (*students)[*num_students].name);

    printf("Enter roll number: ");
    scanf("%d", &(*students)[*num_students].roll_number);

    printf("Enter marks: ");
    scanf("%d", &(*students)[*num_students].marks);

    (*num_students)++;

    printf("\nStudent added successfully!\n\n");
}

void modify_student(Student *students, int num_students) {
    if (num_students == 0) {
        printf("No students to modify.\n");
        return;
    }

    int roll_number;
    printf("\nEnter roll number of the student to modify: ");
    scanf("%d", &roll_number);

    Student *student = search_by_roll_number(students, num_students, roll_number);

    if (student != NULL) {
        printf("Enter new student name: ");
        scanf("%s", student->name);

        printf("Enter new roll number: ");
        scanf("%d", &student->roll_number);

        printf("Enter new marks: ");
        scanf("%d", &student->marks);
    } else {
        printf("Student not found.\n");
    }
}

void display_students(Student *students, int num_students) {
    if (num_students == 0) {
        printf("No students to display.\n");
        return;
    }

    printf("\nStudent Records:\n");
    for (int i = 0; i < num_students; i++) {
        printf("Name: %s\n", students[i].name);
        printf("Roll Number: %d\n", students[i].roll_number);
        printf("Marks: %d\n", students[i].marks);
        printf("-----------------\n");
    }
}

void check_pass_fail(int passing_threshold) {

    double student_mark;
    printf("\nEnter the the student mark to check: ");
    scanf("%lf", &student_mark);

    if (student_mark > passing_threshold) {
        printf("\nStudent has passed.\n\n");
    } else {
        printf("\nStudent has failed.\n\n");
    }
}


void save_to_file(Student *students, int num_students) {
    if (num_students == 0) {
        printf("No students to save.\n");
        return;
    }

    FILE *file = fopen("students.txt", "w");

    for (int i = 0; i < num_students; i++) {
        fprintf(file, "%s %d %d\n", students[i].name, students[i].roll_number, students[i].marks);
    }

    fclose(file);
    printf("\nStudents saved to file successfully.\n\n");
}

void load_from_file(Student **students, int *num_students) {
    FILE *file = fopen("students.txt", "r");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    *num_students = 0;
    char c;
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            (*num_students)++;
        }
    }
    rewind(file);

    *students = (Student *)malloc(sizeof(Student) * (*num_students));

    for (int i = 0; i < *num_students; i++) {
        fscanf(file, "%s %d %d", (*students)[i].name, &(*students)[i].roll_number, &(*students)[i].marks);
    }

    fclose(file);
    printf("\nStudents loaded from file successfully.\n\n");
}

Student *search_by_roll_number(Student *students, int num_students, int roll_number) {
    if (num_students == 0) {
        printf("No students to search.\n");
        return NULL;
    }

    if (roll_number == 0) {
        printf("\nEnter roll number to search: ");
        scanf("%d", &roll_number);
    }

    for (int i = 0; i < num_students; i++) {
        if (students[i].roll_number == roll_number) {
            printf("Name: %s\n", students[i].name);
            printf("Roll Number: %d\n", students[i].roll_number);
            printf("Marks: %d\n", students[i].marks);
            return &students[i];
        }
    }

    printf("\nStudent not found.\n\n");
    return NULL;
}

void calculate_average_marks(Student *students, int num_students) {
    if (num_students == 0) {
        printf("No students to calculate average marks.\n");
        return;
    }

    int total_marks = 0;

    for (int i = 0; i < num_students; i++) {
        total_marks += students[i].marks;
    }

    double average_marks = (double)total_marks / num_students;
    printf("\nAverage Marks: %.2f\n", average_marks);
}

void sort_by_marks(Student *students, int num_students) {
    if (num_students == 0) {
        printf("No students to sort.\n");
        return;
    }

    for (int i = 0; i < num_students - 1; i++) {
        for (int j = 0; j < num_students - i - 1; j++) {
            if (students[j].marks < students[j + 1].marks) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    printf("\nStudents sorted by marks in descending order:\n");
    display_students(students, num_students);
}
