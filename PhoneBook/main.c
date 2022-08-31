#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* FILE_NAME = "contacts.bin";

typedef struct {
	char name[16];
	char number[13];
} Contact;

int read_contacts_from_file(Contact **contacts, int *len) {
	FILE* input = fopen(FILE_NAME, "rb");
	if (input == NULL) {
		FILE* new_file = fopen(FILE_NAME, "wb");
		fclose(new_file);
		input = fopen(FILE_NAME, "rb");
	}
	if (fread(len, sizeof(*len), 1, input) == 0) {
		*len = 0;
	}
	*contacts = malloc(sizeof(Contact) * *len);
	if (*len != 0 && contacts == NULL) {
		return 1;
	}
	if (fread(*contacts, sizeof(Contact), *len, input) < *len) {
		return 2;
	}
	fclose(input);
	return 0;
}

void write_contacts_to_file(const Contact *contacts, int len) {
	FILE *output = fopen(FILE_NAME, "wb");
	fwrite(&len, sizeof(len), 1, output);
	fwrite(contacts, sizeof(Contact), len, output);
	fclose(output);
}

void list(const Contact *contacts, int len) {
	for (int i = 0; i < len; i++) {
		printf("#################\n");
		printf("name: %s\n", contacts[i].name);
		printf("number: %s\n", contacts[i].number);
	}
}

bool add(Contact** contacts, int *len) {
	Contact *new_contacts = realloc(*contacts, (*len) + 1);
	if (new_contacts == NULL) {
		return false;
	}
	*contacts = new_contacts;
	printf("Input name:\n");
	scanf("%s", (*contacts)[*len].name);
	printf("Input number:\n");
	scanf("%s", (*contacts)[*len].number);
	(*len)++;
}

int main() {
	Contact *contacts;
	int len;
	int read_result = read_contacts_from_file(&contacts, &len);

	switch (read_result) {
	case 1:
		printf("Not enough memory\n");
		return 1;
	case 2:
		printf("File corrupted\n");
		return 2;
	default:
		printf("File read successfully\n");
	}

	printf("You have %i contacts\n", len);

	while (true) {
		char command[11];
		if (scanf("%10s", command) != 1) {
			printf("Something went wrong\n");
			continue;
		}
		if (strcmp(command, "add") == 0) {
			add(&contacts, &len);
		} else if (strcmp(command, "list") == 0) {
			list(contacts, len);
		} else if (strcmp(command, "exit") == 0) {
			break;
		} else {
			printf("Incorrect command\n");
		}
	}
	write_contacts_to_file(contacts, len);
	free(contacts);
	return 0;
}