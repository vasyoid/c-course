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

void read_contacts_from_file(Contact **contacts, int *len) {
	FILE* input = fopen(FILE_NAME, "rb");
	fread(len, sizeof(*len), 1, input);
	*contacts = malloc(sizeof(Contact) * *len);
	fread(*contacts, sizeof(Contact), *len, input);
	fclose(input);
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
	read_contacts_from_file(&contacts, &len);

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