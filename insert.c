#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	FILE* fp;
	char buff[256];

	// file string input
	fp = fopen("new_file.txt", "w");
	printf("Input : \n");

	gets(buff);
	while(buff[0] != '\0') {
		fputs(buff, fp);
		fputs("\n", fp);
		gets(buff);
	}
	fclose(fp);

	// output
	fp = fopen("new_file.txt", "r");
	printf("Output : \n");
	while(!feof(fp)) {
		fgets(buff, 256, fp);
		if (!feof(fp)) {
			printf("%s", buff);
		}
	}
	fclose(fp);
}
