#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct student
{
    int rollno;
    char name[20];
    struct student *next;
};

bool check_if_record_exists(struct student *current, int rollno)
{
    while (current != NULL && current->rollno != rollno)
    {
        current = current->next;
    }
    return current == NULL ? false : true;
}

void swap(struct student* a, struct student* b){
    char name[50];
    int tmp = a->rollno;
    a->rollno = b->rollno;
    b->rollno = tmp;
    strcpy(name, a->name);
    strcpy(a->name, b->name);
    strcpy(b->name, name);
}

void sort_list(struct student* HEAD){
    struct student* current = HEAD;
    while(current != NULL){
        struct student *min_node = current;
        struct student *tmp = current->next;
        while(tmp!=NULL){
            if(tmp->rollno < min_node->rollno){
                min_node = tmp;
            }
            tmp = tmp->next;
        }
        swap(current, min_node);
        current = current->next;
    }
}

struct student *create_student(int rollno, char *name)
{
    struct student *tmp = (struct student *)malloc(sizeof(struct student));
    tmp->rollno = rollno;
    strcpy(tmp->name, name);
    tmp->next = NULL;
    return tmp;
}

void add_student(struct student **HEAD, int rollno, char *name)
{
    if (!check_if_record_exists(*HEAD, rollno))
    {
        struct student *tmp = create_student(rollno, name);
        struct student *tmp_head = *HEAD;
        if (*HEAD == NULL)
        {
            *HEAD = tmp;
            printf("First student ADDED %d %s", tmp->rollno, tmp->name);
            return;
        }

        while (tmp_head->next != NULL)
        {
            tmp_head = tmp_head->next;
        }
        tmp_head->next = tmp;
        printf("ADDED %d %s", tmp->rollno, tmp->name);
        sort_list(*HEAD);
    }
    else
    {
        printf("\nERROR: record with provided roll no already exist");
    }
}

void update_specific_student_data(struct student *HEAD, int rollno, char *name)
{
    struct student *tmp = HEAD;
    while (tmp != NULL)
    {
        if (tmp->rollno == rollno)
        {
            strcpy(tmp->name, name);
            printf("\nRecord updated successfully");
            return;
        }
        tmp = tmp->next;
    }
}

void delete_specific_student_data(struct student **HEAD, int rollno)
{
    struct student *current = *HEAD;
    struct student *tmp = NULL;
    if (current == NULL)
    {
        printf("\nERROR: No student with provided roll no");
        return;
    }

    if (current != NULL && current->rollno == rollno)
    {
        *HEAD = current->next;
        free(current);
        return;
    }
    while (current != NULL)
    {
        if (current->rollno == rollno)
        {
            tmp->next = current->next;
            free(current);
            return;
        }
        tmp = current;
        current = current->next;
    }
    
}

void delete_all_student_data(struct student **HEAD)
{
    struct student *current = *HEAD;
    struct student *tmp;
    while (current != NULL)
    {
        tmp = current;
        current = current->next;
        free(tmp);
    }
    *HEAD = NULL;
    printf("\nDeleted all data!!!!");
}

int print_specific_student_data(struct student *HEAD, int rollno)
{
    struct student *tmp = HEAD;
    while (tmp != NULL)
    {
        if (tmp->rollno == rollno)
        {
            printf("\nStudent data:\nRollno\tName");
            printf("\n%d\t%s", tmp->rollno, tmp->name);
            return 1;
        }
        tmp = tmp->next;
    }
    if (tmp == NULL)
    {
        printf("\nERROR: No student with provided roll no");
        return 0;
    }
}

void print_all_students_data(struct student *HEAD)
{
    struct student *tmp = HEAD;
    if (tmp == NULL)
    {
        printf("\nNo student data available!!!!");
        return;
    }
    printf("\nStudent's data: \nRollNo\tName");
    while (tmp != NULL)
    {
        printf("\n%d\t%s", tmp->rollno, tmp->name);
        tmp = tmp->next;
    }
}
