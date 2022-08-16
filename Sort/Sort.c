#include <stdio.h>

void swap(char* l, char* r, int size) {
    for (int i = 0; i < size; i++) {
        char tmp = l[i];
        l[i] = r[i];
        r[i] = tmp;
    }
}

void sort(void* arr, int el_size, int length, int (*cmp) (void*, void*)) {
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            char* l = (char *)arr + el_size * i;
            char* r = (char *)arr + el_size * j;
            if (cmp(l, r) > 0) {
                swap(l, r, el_size);
            }
        }
    }
}

int compare_int_progressive(void* x, void* y) {
    int* px = x;
    int* py = y;

    return *px - *py;
}

int compare_int_regressive(void* x, void* y) {
    int* px = x;
    int* py = y;

    return *py - *px;
}

typedef struct {
    int age;
    int height;
} User;

int compare_users(void* x, void* y) {
    User* px = x;
    User* py = y;

    if (px->height == py->height) {
        return px->age - py->age;
    }
    return px->height - py->height;
}


int main() {
    int arr[] = { 4, 6, 7, 5, 8, 9, 1, 2 };
    sort(arr, sizeof(int), sizeof(arr) / sizeof(int), compare_int_progressive);

    for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
        printf("%i ", arr[i]);
    }
    printf("\n");

    sort(arr, sizeof(int), sizeof(arr) / sizeof(int), compare_int_regressive);

    for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
        printf("%i ", arr[i]);
    }
    printf("\n");





    User users[3];
    users[2].height = 1;
    users[2].age = 1;

    users[1].height = 2;
    users[1].age = 1;

    users[0].height = 2;
    users[0].age = 3;

    sort(users, sizeof(User), sizeof(users) / sizeof(User), compare_users);

    for (int i = 0; i < sizeof(users) / sizeof(User); i++) {
        printf("%i %i\n", users[i].height, users[i].age);
    }
}
