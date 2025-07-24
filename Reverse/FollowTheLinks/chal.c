#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Node {
	uint8_t enc_val;
	struct Node *next;
} Node;

char *read_flag(const char *path)
{
	FILE *fp = fopen(path, "r");
	if (!fp) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	fseek(fp, 0, SEEK_END);
	long len = ftell(fp);
	rewind(fp);

	char *buf = malloc(len + 1);
	if (!buf) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	fread(buf, 1, len, fp);
	buf[len] = '\0';
	fclose(fp);

	// 移除尾端換行
	if (buf[len - 1] == '\n')
		buf[len - 1] = '\0';
	return buf;
}

Node *encrypt_flag(const char *flag)
{
	int order[46] = { 7,  42, 12, 27, 0,  29, 36, 25, 16, 23, 30, 15,
			  33, 1,  5,  20, 10, 17, 8,  41, 31, 39, 3,  24,
			  32, 11, 9,  38, 26, 6,  2,  35, 43, 19, 37, 44,
			  4,  34, 13, 21, 22, 14, 18, 28, 40, 45 };

	Node *head = NULL;
	const uint8_t fixed_key = 0x13;

	for (int i = 0; i < 46; i++) {
		Node *n = malloc(sizeof(Node));
		n->enc_val = flag[order[i]] ^ fixed_key;
		n->next = head;
		head = n;
	}
	return head;
}

void write_encrypted(Node *head, const char *path)
{
	FILE *f = fopen(path, "w");
	if (!f) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	for (Node *cur = head; cur; cur = cur->next)
		fprintf(f, "%02x", cur->enc_val);
	fprintf(f, "\n");
	fclose(f);
}

int main()
{
	char *flag = read_flag("flag.txt");
	Node *enc = encrypt_flag(flag);
	write_encrypted(enc, "encrypted.txt");
	return 0;
}
