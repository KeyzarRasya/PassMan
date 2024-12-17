#include <stdio.h>
#include "cli.h"

struct Cli cli;

void start(char *argv[]){
    char *action = argv[1];
    char *key = argv[2];
    char *values = argv[3];

    if(action == NULL || key == NULL){
        printf("You need 3 arguments {acrion} {key} {value}\n");
        return;
    }

    if(strcmp(key, "store") && values != NULL){
        insert_val(&cli, key, values);
        return;
    }else if(strcmp(key, "find")){
        find_values(&cli, key);
        return;
    }else{
        printf("Action argument has only two option 'store' and 'find' option\n");
        return;
    }
}

int main(int args, char *argv[]){
    init(&cli, "{filepath}");

    start(argv);

    return 0;
}