/*
* @Author: v4if
* @Date:   2016-11-15 21:45:46
* @Last Modified by:   v4if
* @Last Modified time: 2016-11-26 16:18:37
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

typedef struct s
{
	char event_key;
	char prompt[1024];
	char lib[128];
	char method[128];
}EventMap;

int invoke_method(char *lib, char *method, float v1, float v2) {
	void *dl_handle;
	float (*func)(float v1, float v2);
	char *error;

	/* Open the shared object */
	dl_handle = dlopen( lib, RTLD_LAZY );
	if (!dl_handle) {
		printf( "!!! %s\n", dlerror() );
		return -1;
	}

	/* Resolve the symbol (method) from the object */
	func = dlsym( dl_handle, method );
	error = dlerror();
	if (error != NULL) {
		printf( "!!! %s\n", error );
		return -1;
	}

	/* Call the resolved method and print the result */
	printf("  result: %.2f\n", (*func)(v1, v2) );

	/* Close the object */
	dlclose(dl_handle);

	return 0;
}

int file_line() {
	FILE *fin = fopen("local.xml", "r");
	if (fin == NULL)
	{
		printf("local.xml is not found!! \n");
		return -1;
	}
	char ch;
	int no = 0;
	while((ch = fgetc(fin)) && (ch != EOF)) {
		if (ch == '\n')
		{
			no++;
		}
	}
	fclose(fin);

	return no;
}

void fill_envent_map(EventMap *head) {
	FILE *fin = fopen("local.xml", "r");
	if (fin == NULL)
	{
		printf("local.xml is not found!! \n");
		return;
	}

	char ch;
	// skip first line
	while((ch = fgetc(fin)) && (ch != EOF)) {
		if (ch == '\n')
		{
			break;
		}
	}

	char buff[1024];
	int no = 0;
	while((ch = fgetc(fin)) && (ch != EOF)) {
		head[no].event_key = ch;

		fscanf(fin, "%s", buff);
		strncpy(head[no].prompt, buff, 1024);

		fscanf(fin, "%s", buff);
		strncpy(head[no].lib, buff, 128);

		fscanf(fin, "%s", buff);
		strncpy(head[no].method, buff, 128);

		// skip white
		while((ch = fgetc(fin)) && (ch != '\n'));
		no++;
	}
	fclose(fin);
}

int get_map_entry(EventMap *head, char event_key, int no) {
	for (int i = 0; i < no; ++i)
	{
		if (head[i].event_key == event_key)
		{
			return i;
		}
	}
	return -1;
}

void print_menu(EventMap *head, int no) {
	printf("===== Entry Menu =====\n");
	for (int i = 0; i < no; ++i)
	{
		printf("%c\t%s\n", head[i].event_key, head[i].prompt);
	}
	printf("simple:\n");
	printf("> a 1 2 [Enter]\n");
	printf("=====  End  Menu =====\n");
}

int 
main() {
	EventMap *event_head = NULL;
	int no = file_line() -1;
	// malloc memory
	event_head = (EventMap*)malloc(sizeof(EventMap) * no);

	fill_envent_map(event_head);

	int ch;
	int index;
	float v1, v2;
	print_menu(event_head, no);
	while(1) {
		printf("> ");
		scanf("%c%f%f", &ch, &v1, &v2);
		index = get_map_entry(event_head, ch, no);

		if (index == -1)
		{
			printf("event key is not found!!\n");
			while((ch = getc(stdin)) && ch != '\n');
			continue;
		}

		invoke_method(event_head[index].lib, event_head[index].method, v1, v2);

		
		while((ch = getc(stdin)) && ch != '\n');
	}
	
    return 0;
}
