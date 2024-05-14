#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "../include/student.h"
#include "../include/cJSON.h"
#include "../DB/db.h"

// struct student{
//     int rollno;
//     char name[20];
// };

struct student *HEAD = NULL;

enum eventCode
{
    ADD = 1,
    UPDATE,
    DELETE_SPECIFIC,
    DELETE_ALL,
    PRINT_SPECIFIC,
    PRINT_ALL,
    EXIT
};

// Read data from students.json and store it in memory (linked list)
void read_data_from_json()
{
    FILE *f = fopen("students.json", "r");
    if (f)
    {
        fseek(f, 0, SEEK_END);
        long fsize = ftell(f);
        fseek(f, 0, SEEK_SET);

        char *json_str = (char *)malloc(fsize + 1);
        fread(json_str, 1, fsize, f);
        fclose(f);

        json_str[fsize] = '\0';

        cJSON *json_read = cJSON_Parse(json_str);
        if (json_read)
        {
            HEAD = deserialize_list(json_read);
        }
        else
        {
            fprintf(stderr, "Error: Failed to parse JSON file.\n");
        }

        free(json_str);
        cJSON_Delete(json_read);
    }
    else
    {
        fprintf(stderr, "Error: Failed to open JSON file for reading.\n");
    }
}

// Write linked list data to students.json just before program termination
void write_data_to_json()
{
    cJSON *root = cJSON_CreateObject();
    serialize_list(HEAD, root);

    char *json_write_str = cJSON_Print(root);
    FILE *write_f = fopen("students.json", "w");
    fprintf(write_f, "%s\n", json_write_str);
    fclose(write_f);

    cJSON_Delete(root);
    free(json_write_str);
}

int main()
{
    read_data_from_json();
    printf("\n********************* Welcome to STUDBOOK *********************\n");
    while (1)
    {
        int tmp;
        printf("\n\nChoose action on student data:"
               "\n1. Add "
               "\n2. Update "
               "\n3. Delete specific record "
               "\n4. Delete all records "
               "\n5. Print student using roll no "
               "\n6. Print all students data "
               "\n7. Exit"
               "\nYour option: ");
        scanf("%d", &tmp);

        if (tmp < 1 || tmp > 7)
        {
            printf("\n!!!!!!!! Invalid input, try again !!!!!!!!\n");
            continue;
        }
        else
        {
            switch (tmp)
            {
                case ADD:
                {
                    // adding new student data
                    int rollno; // declaration is not allowed immediately after label as case, so use {}
                    char name[50];
                    printf("\nEnter rollno: ");
                    scanf("%d", &rollno);
                    while (getchar() != '\n')
                        ;
                    printf("\nEnter student name: ");
                    scanf("%s", name);
                    add_student(&HEAD, rollno, name);
                    break;
                }

                case UPDATE:
                {
                    // update specific student using rollno
                    int rollno;
                    char name[50];
                    printf("\nEnter roll no: ");
                    scanf("%d", &rollno);
                    if (!print_specific_student_data(HEAD, rollno))
                        break;
                    printf("\nEnter updated name: ");
                    scanf("%s", name);
                    update_specific_student_data(HEAD, rollno, name);
                    break;
                }

                case DELETE_SPECIFIC:
                {
                    // Delete specific student using rollno
                    int rollno;
                    printf("\nEnter roll no to delete: ");
                    scanf("%d", &rollno);
                    if (!print_specific_student_data(HEAD, rollno))
                        break;
                    delete_specific_student_data(&HEAD, rollno);
                    printf("\nDeleted above record!!");
                    break;
                }

                case DELETE_ALL:
                {
                    // Delete all records
                    char confirmation[10];
                    printf("\nARE YOU SURE? (Y or N): ");
                    scanf("%s", confirmation);
                    if (strcmp(confirmation, "y") == 0 || strcmp(confirmation, "yes") == 0 || strcmp(confirmation, "YES") == 0 || strcmp(confirmation, "Y") == 0 || strcmp(confirmation, "Yes") == 0)
                    {
                        delete_all_student_data(&HEAD);
                        break;
                    }
                    printf("\nRecords not deleted!!");
                    break;
                }

                case PRINT_SPECIFIC:
                {
                    // Print student using rollno
                    int rollno;
                    printf("\nEnter roll no: ");
                    scanf("%d", &rollno);
                    if (!print_specific_student_data(HEAD, rollno))
                        break;
                    break;
                }
                case PRINT_ALL:
                    // Print all students data
                    print_all_students_data(HEAD);
                    break;

                case EXIT:
                {
                    // terminating infinite loop, exiting application
                    write_data_to_json();
                    delete_all_student_data(&HEAD);
                    printf("\nFreed memory.......... Exiting application!!");
                    return 0;
                }
            }
        }
    }

    return 0;
}