#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mkdisk.h"
#include "rmdisk.h"
#include "fdisk.h"
#include "mount.h"
#include "unmount.h"
#include "rep.h"
#include "exec.h"

#define MAX 9

#define RED   "\x1B[1;31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[1;36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

typedef struct command{
    int id;
    char name[15];
} cmd;

struct command keywords[MAX];
void exec();

void cargar(){
    char ch, buffer[80];
    memset(&buffer,'\0',sizeof(buffer));
    FILE *fp;
    int j=0, line=0;
    fp = fopen("command.txt","r");

    if(fp == NULL)    {
        printf(RED "ERROR: NO SE PUDO ABRIR  EL ARCHIVO\n" RESET);
        exit(0);
    }

    while((ch = fgetc(fp)) != EOF){
        if(isalnum(ch)){
            buffer[j++] = ch;
        }else if((ch == '\n') && (j != 0)){
            buffer[j] = '\0';
            j = 0;
            int id = 0;
            char name[15]="";
            memset(&name,'\0',sizeof(name));
            sscanf( buffer, "%u %s",&id, name);
            cmd mkd;
            mkd.id = id;
            memset(&mkd.name,'\0',sizeof(mkd.name));
            strcat(mkd.name, name);
            keywords[line] = mkd;
            line++;
            memset(&buffer,'\0',sizeof(buffer));
        }

    }
    fclose(fp);

}

int isKeyword(char buffer[]){
    int i;
    for(i = 0; i < MAX; ++i){
        if(strcasecmp(keywords[i].name, buffer) == 0){
            return keywords[i].id;
        }
    }
    return 0;
}


void commandAnalyzer(int state, char str[], int start){
    switch(state){
    case 1:
        processMKDISK(str,start);
        break;
    case 2:
        processRMDISK(str,start);
        break;
    case 3:
        processFDISK(str,start);
        break;
    case 4:
        processMOUNT(str,start);
        break;
    case 5:
        processUNMOUNT(str,start);
        break;
    case 6:
        processREP(str, start);
        break;
    case 7:
        processEXEC(str,start);
        exec();

        break;
    }
}

int processCommand(char str[]){
    char ch, buffer[150];
    memset(&buffer,'\0',sizeof(buffer));
    int i=0,j=0;
    while((ch = str[i++]) != '\0'){
        if(isalnum(ch)){
            buffer[j++] = ch;
        }else if((ch == ' ' || ch == '\n') && (j != 0)){
            buffer[j] = '\0';
            j = 0;
            int state = isKeyword(buffer);
            if(state != 0){
                commandAnalyzer(state,str, i);
            }else{
                printf(RED "%s ERROR: NO ES UN COMANDO VALIDO!\n" RESET, buffer);
            }
            return 0;
        }
    }
    int state = isKeyword(buffer);
    if(state != 0){
        commandAnalyzer(state, str, -1);
    }else{
        printf(RED "%s ERROR: NO ES UN COMANDO VALIDO!\n" RESET, buffer);
    }
    return 0;
}

void exec(){
    char *str = strdup(str2);
    char *tofree = str;
    char *linea;

    while ((linea = strsep(&str, "\n"))){
        if (!strcmp(linea, "")==0){

            int len = strlen(linea);

            if (len > 0){
                if (linea[0] == '#'){
                    printf(YEL "%s \n" RESET, linea);
                }else{
                    //printf(CYN "%s \n" RESET, linea);

                    if (linea[0] != ' '){
                        processCommand(linea);
                    }

                }

            }

        }

    }

    free(tofree);
}
