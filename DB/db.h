#include "../include/cJSON.h"
void serialize_list(struct student* head, cJSON* root);

struct student* deserialize_list(cJSON* root);
