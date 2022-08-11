#define _CRT_SECURE_NO_WARNINGS

// #pragma pack(??)
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    char name[16];
    float rating;
    char gender;
    bool has_pets;
    int age;
    short height;
} User;

long get_file_size(FILE* f) {
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);
    return size;
}

bool read_users(User* users, int length) {
    FILE* input = fopen("database.bin", "rb");
    long file_size = get_file_size(input);
    if (file_size != sizeof(User) * length) {
        return false;
    }
    fread(users, 1, file_size, input);
    fclose(input);
    return true;
}

void print_user(User user) {
    printf("  name:     %s\n", user.name);
    printf("  age:      %i\n", user.age);
    printf("  rating:   %.2f\n", user.rating);
    printf("  height:   %i\n", user.height);
    printf("  gender:   %c\n", user.gender);
    printf("  has pets: %s\n", user.has_pets ? "true" : "false");
}

void print_users(User* users, int length) {
    for (int i = 0; i < length; i++) {
        printf("======= User #%i\n", i);
        print_user(users[i]);
    }
}

bool check(User* users) {
    return strcmp(users[0].name, "Martin") == 0
        && users[0].age == 42
        && users[0].rating == 4.3f
        && users[0].height == 180
        && users[0].gender == 'm'
        && users[0].has_pets;
}

void validate(int length) {
    User* users = malloc(sizeof(User) * length);
    if (!read_users(users, length)) {
        printf("Incorrect array size\n");
        return;
    }
    if (!check(users)) {
        printf("Incorrect user data:\n");
        print_user(users[0]);
        return;
    }
    print_users(users, length);
    free(users);
}

int main() {
//    validate(??);
    return 0;
}
