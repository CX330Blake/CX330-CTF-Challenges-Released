#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUF_SIZE 256

// 一些簡單的 ANSI 顏色（前景）
const char *colors[] = {
	"\x1b[31m", // 紅
	"\x1b[32m", // 綠
	"\x1b[33m", // 黃
	"\x1b[34m", // 藍
	"\x1b[35m", // 紫
	"\x1b[36m", // 青
	"\x1b[91m", // 亮紅
	"\x1b[92m", // 亮綠
	"\x1b[93m", // 亮黃
	"\x1b[94m", // 亮藍
	"\x1b[95m", // 亮紫
	"\x1b[96m" // 亮青
};
const int NUM_COLORS = sizeof(colors) / sizeof(colors[0]);

// Fisher-Yates shuffle
void shuffle(char *arr, int n)
{
	for (int i = n - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		char tmp = arr[i];
		arr[i] = arr[j];
		arr[j] = tmp;
	}
}

int tree(int width)
{
	// 確保是奇數
	if (width % 2 == 0) {
		fprintf(stderr, "Error: The width must be an odd number.\n");
		return 1;
	}

	// 設定隨機種子
	srand((unsigned int)time(NULL));

	int numRows = (width + 1) / 2;

	// 畫樹頂
	for (int i = 0; i < numRows; i++) {
		int numAsterisks = i * 2 + 1;
		int numSpaces = (width - numAsterisks) / 2;

		int numOrnaments = rand() % (numAsterisks + 1);

		// 建這一行的 ornament 陣列
		char *ornaments = (char *)malloc(numAsterisks * sizeof(char));
		if (!ornaments) {
			perror("malloc");
			return 1;
		}

		for (int j = 0; j < numOrnaments; j++) {
			ornaments[j] = 'o';
		}
		for (int j = numOrnaments; j < numAsterisks; j++) {
			ornaments[j] = '*';
		}

		// 打亂
		shuffle(ornaments, numAsterisks);

		// 綠色（樹的基本顏色）
		printf("\x1b[32m"); // green

		// 左邊空白
		for (int j = 0; j < numSpaces; j++)
			putchar(' ');

		// 畫每個 ornament
		for (int j = 0; j < numAsterisks; j++) {
			if (ornaments[j] == 'o') {
				// 隨機顏色
				const char *c = colors[rand() % NUM_COLORS];
				printf("%s", c);
				putchar('o');
				printf("\x1b[32m"); // 切回綠色
			} else {
				putchar('*');
			}
		}

		// 右邊空白
		for (int j = 0; j < numSpaces; j++)
			putchar(' ');

		// 換行
		printf("\n");

		free(ornaments);
	}

	// 畫樹幹（深紅）
	printf("\x1b[31m"); // red 當作 DarkRed
	for (int k = 0; k < 2; k++) {
		for (int j = 0; j < width / 2; j++)
			putchar(' ');
		putchar('|');
		for (int j = 0; j < width / 2; j++)
			putchar(' ');
		putchar('\n');
	}

	// Reset 顏色
	printf("\x1b[0m\n");

	// 印訊息
	const char *message = "Merry Christmas!";
	int msgLen = (int)strlen(message);
	int leftSpaces = (width - msgLen) / 2;
	if (leftSpaces < 0)
		leftSpaces = 0;

	printf("\x1b[37m"); // 白色
	for (int j = 0; j < leftSpaces; j++)
		putchar(' ');
	printf("%s\n", message);
	printf("\x1b[0m"); // reset

	return 0;
}

char *init_flag()
{
	FILE *fp = fopen("./flag.txt", "r");
	if (fp == NULL) {
		printf("No flag.txt QQ\n");
		exit(-1);
	}

	// Determine the length of the file
	fseek(fp, 0, SEEK_END);
	long length = ftell(fp);
	fseek(fp, 0, SEEK_SET); // Reset file pointer to the beginning

	// Allocate memory for the flag
	char *flag = (char *)malloc(length + 1); // null terminator
	if (flag == NULL) {
		printf("Memory allocation failed\n");
		fclose(fp);
		exit(-1);
	}

	// Read the contents of the file into the flag
	fread(flag, 1, length, fp);
	flag[length] = '\0'; // Null-terminate the string

	fclose(fp);
	return flag;
}

void say_goodbye()
{
	printf("Well, fine. Still wish u a merry x'mas! :)\n");
	exit(0);
}

int menu(int money)
{
	int choice;
	printf("===============================\n"
	       "Buy a gift! Your money: $%d\n"
	       "===============================\n"
	       "1. Snow Globe: $99\n"
	       "2. Gingerbread House: $10\n"
	       "3. Mulled Wine: $5\n"
	       "4. Santa's Reindeer: $1\n"
	       "99. Leave the store\n"
	       "> ",
	       money);
	if (scanf("%d", &choice) != 1) {
		return -1;
	}
	return choice;
}

void buy(int *money, int price)
{
	int counts;
	printf("How many?\n"
	       "> ");
	if (scanf("%d", &counts) != 1) {
		printf("Invalid input...\n");
		exit(-1);
	}

	int total = price * counts;
	if (*money < total) {
		printf("Woah! No money, no gift!\n");
		exit(-1);
	}

	*money -= counts * price;
}

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	int money = 100;
	char *flag = init_flag();
	tree(29);
	printf("Welcome to the Christmas store!\n");
	for (;;) {
		int choice = menu(money);
		switch (choice) {
		case 1:
			buy(&money, 99);
			printf("Look! It's so beautiful...\n");
			break;
		case 2:
			buy(&money, 10);
			printf("Yum... Do you want some?\n");
			break;
		case 3:
			buy(&money, 5);
			printf("Here u r! Don't drive after drinking!\n");
			break;
		case 4:
			buy(&money, 1);
			printf("Ho ho ho! Wait, where's my Reindeer?\n");
			break;
		case 5:
			buy(&money, 101);
			printf("Haha, you found the hidden gift!\nFlag: %s\n",
			       flag);
			break;
		case 99:
			say_goodbye();
			break;
		default:
			printf("Invalid option. Get out of my store!\n");
			exit(-1);
			break;
		}
	}
}
