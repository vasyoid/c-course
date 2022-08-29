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


	for (int i = 0; i < 2; i++) {
		printf("%s: %s\n", contacts[i].name, contacts[i].number);
	}

//	Contact contacts[2];
//	strcpy(contacts[0].name, "Vasya");
//	strcpy(contacts[0].number, "+79991234567");
//	strcpy(contacts[1].name, "Kolya");
//	strcpy(contacts[1].number, "+70001234567");
//	write_contacts_to_file(contacts, 2);

// read_contacts_from_file();
//	while (true) {
		// scanf("%s", ...);
		// if (add) { }
		// else if (list) { }
		// else if (exit) { }
//	}
	return 0;
}