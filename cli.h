#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef CLI
#define CLI

struct Cli{
    char key[50];
    char values[100];
    char filename[50];
    FILE *fptr;
};

void init(struct Cli *cli, char filename[]){
    strcpy(cli->filename, filename);
    cli->fptr = fopen(filename, "a");
}

char* get_key(char buffer[], int size){
    char* keys = (char*)malloc(size);
    int key_len = 0;
    for(int i = 0; i < size; i++){
        if(buffer[i] == ','){
            break;
        }else{
            keys[key_len] = buffer[i];
            key_len++;
        }
    }
    keys[key_len] = '\0';
    return keys;
}

char *get_val(char buffer[], int size){
    char* keys = (char*)malloc(size);
    int commaIndex = 0;
    int key_len = 0;
    for(int i = 0; i < size; i++){
        if(buffer[i] == ','){
            commaIndex = i;
            break;
        }
    }
    for(int i = commaIndex+1; i <  size; i++){
        if(buffer[i] == ';'){
            break;
        }
        keys[key_len] = buffer[i];
        key_len++;
    }
    keys[key_len] = '\0';
    return keys;
}

int is_key_used(struct Cli *cli, char result[]){
    cli->fptr = fopen(cli->filename, "r");
    char *buffer = NULL;
    size_t buffer_size = 0; 
    size_t line_length;
    while ((line_length = getline(&buffer, &buffer_size, cli->fptr)) != -1) {
        char *keys = get_key(buffer, (int)line_length);
        if(strcmp(keys, result) == 0){
            return 1;
        }
    }
    free(buffer); 
    fclose(cli->fptr); 
    return 0;
}

int check_key_char(char key[]){
   int size = (int)strlen(key);
   for(int i = 0 ; i < size; i++){
        if(key[i] == ' ' || key[i] == ';' || key[i] == ','){
            return 1;
        }
   }
   return 0;
}

void insert_val(struct Cli *cli,char key[], char values[]){
    char result[150] = "";

    if(is_key_used(cli, key)){
        printf("Key already used\n");
        return;
    }

    cli->fptr = fopen(cli->filename, "a");
    if(cli->fptr == NULL){
        printf("Failed to load passman");
        return;
    }

    if(check_key_char(key)){
        printf("No special character allowed\n");
        return;
    }

    strcpy(cli->key, key);
    strcpy(cli->values, values);
    strcat(result, cli->key);
    strcat(result, ",");
    strcat(result, cli->values);
    strcat(result, ";");
    fprintf(cli->fptr, "%s\n", result);
    printf("Success\n");
    fclose(cli->fptr);
}





void keyval_to_array(char buffer[], int size){
    char arrys[100][1];
    int keyX_len = 0;
    int keyY_len =0;

    for(int i = 0; i < size; i++){
        char *keys = get_key(buffer, size);
        
    }

}

void find_values(struct Cli *cli, char key[]){
    cli->fptr = fopen(cli->filename, "r");
    if(cli->fptr == NULL){
        printf("ERROR");
    }
    char *buffer = NULL;
    size_t buffer_size = 0; 
    size_t line_length;
    int state = 0;

    while ((line_length = getline(&buffer, &buffer_size, cli->fptr)) != -1) {
        char *keys = get_key(buffer, (int)line_length);
        if(strcmp(keys, key) == 0){
            char *val = get_val(buffer, (int)line_length);
            printf("%s", val);
            state = 1;
            break;
        }
        
    }

    state == 0 ? printf("No Values found\n") : printf("\n");

    free(buffer); 
    fclose(cli->fptr); 
}


void print_content(struct Cli *cli){
    printf("Key : %s \nValues : %s", cli->key, cli->values);
}

#endif
