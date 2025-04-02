// student.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 20
#define MAX_ADDR_LEN 50
#define MAX_PHONE_LEN 20

struct student {
    int id;
    char name[MAX_NAME_LEN];
    char address[MAX_ADDR_LEN];
    char phone[MAX_PHONE_LEN];
    int birth_year;
};