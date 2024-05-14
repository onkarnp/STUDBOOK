#include <stdio.h>

#include "../include/cJSON.h"
#include "../include/student.h"

void serialize_list(struct student* head, cJSON* root){
    if(head == NULL){
        cJSON_AddNullToObject(root, "students");
        return;
    }
    cJSON* array = cJSON_CreateArray();
    struct student* current = head;
    while (current != NULL) {
        cJSON* student_json = cJSON_CreateObject();
        cJSON_AddNumberToObject(student_json, "rollno", current->rollno);
        cJSON_AddStringToObject(student_json, "name", current->name);
        cJSON_AddItemToArray(array, student_json);
        current = current->next;
    }
    cJSON_AddItemToObject(root, "students", array);
}

struct student* deserialize_list(cJSON* root){
    struct student* head = NULL;
    cJSON* array = cJSON_GetObjectItem(root, "students");
    if (array) {
        cJSON* current_json = array->child;
        while (current_json != NULL) {
            cJSON* rollno_json = cJSON_GetObjectItem(current_json, "rollno");
            cJSON* name_json = cJSON_GetObjectItem(current_json, "name");
            if (rollno_json && name_json) {
                struct student* new_node = create_student(rollno_json->valueint, name_json->valuestring);
                new_node->next = NULL;
                if (head == NULL) {
                    head = new_node;
                } else {
                    struct student* current = head;
                    while (current->next != NULL) {
                        current = current->next;
                    }
                    current->next = new_node;
                }
            } else {
                fprintf(stderr, "Error: Rollno or Name not found in JSON.\n");
            }
            current_json = current_json->next;
        }
    } else {
        fprintf(stderr, "Error: Students array not found in JSON.\n");
    }
    return head;
}