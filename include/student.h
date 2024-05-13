#ifndef STUDENT_H
#define STUDENT_H

#include <stdbool.h>
struct student
{
    int rollno;
    char name[20];
    struct student *next;
};

bool check_if_record_exists(struct student *current, int rollno);

void swap(struct student* a, struct student* b);

void sort_list(struct student* HEAD);

struct student *create_student(int rollno, char *name);

void add_student(struct student **HEAD, int rollno, char *name);

void update_specific_student_data(struct student *HEAD, int rollno, char *name);

void delete_specific_student_data(struct student **HEAD, int rollno);

void delete_all_student_data(struct student **HEAD);

int print_specific_student_data(struct student *HEAD, int rollno);

void print_all_students_data(struct student *HEAD);

#endif