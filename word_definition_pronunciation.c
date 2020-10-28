//Program to print definition and play pronunciation of a word
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define DICTIONARY_FILE "dictionary.dat"

char* get_definition(char* file_name)
{
	char data[1000];
	FILE* fp_dictionary = fopen(file_name, "r");
	fread(data, sizeof(data), 1, fp_dictionary);
	char* dictionary_data_token = strtok(data, "[{:,\"");
	char is_found = 'n';
	char* definition;
	while(dictionary_data_token != NULL)
	{
		if(strcmp(dictionary_data_token, "definition") == 0)
		{
			is_found = 'y';
		}
		dictionary_data_token = strtok(NULL, "[{:,\"");
		dictionary_data_token = strtok(NULL, "[{:,\"");
		if(is_found == 'y')
		{
			definition = dictionary_data_token;
			printf("%s\n", definition);
			break;
		}
	}
	fclose(fp_dictionary);
	return definition;
}

void play_audio()
{
	char data[1000];
	FILE* fp_dictionary = fopen(DICTIONARY_FILE, "r");
	fread(data, sizeof(data), 1, fp_dictionary);
	char* dictionary_data_token = strtok(data, "[{:,\"");
	char is_found = 'n';
	char* definition;
	char cmd[100];
	while(dictionary_data_token != NULL)
	{
		if(strcmp(dictionary_data_token, "audio") == 0)
		{
			is_found = 'y';
		}
		dictionary_data_token = strtok(NULL, "[{,\"");
		dictionary_data_token = strtok(NULL, "[{,\"");
		if(is_found == 'y')
		{
			definition = dictionary_data_token;
			printf("%s", definition);
			break;
		}
	}
	fclose(fp_dictionary);
	sprintf(cmd, "vlc \"%s\" --qt-start-minimized", definition);
	system(cmd);
}


void display_definition()
{
	char cmd[100];
	char word[30];
	printf("Enter word: ");
	scanf("%s", word);
	sprintf(cmd, "curl \"https://api.dictionaryapi.dev/api/v2/entries/en/%s\" > %s -s", word, DICTIONARY_FILE);
	system(cmd);
	printf("Definition for word %s: ", word);
	char* definition = get_definition(DICTIONARY_FILE);
}

int main()
{
	display_definition();
	play_audio();
}
