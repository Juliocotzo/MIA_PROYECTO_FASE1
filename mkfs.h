#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <dirent.h>
#include <errno.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
//#include "estructuras.h"
//#include "mount.h";

#define RED   "\x1B[1;31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[1;36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"


typedef struct mkfs{
    char id[15];
    char type[15];
} mkfs_init;

int processMKFS(char str[], int cont){
    if(cont == -1){
        printf(RED "ERROR: COMANDO SIN PARAMETROS \n" RESET);
        return 0;
    }
    mkfs_init rm;
    memset(&rm.id,'\0',sizeof(rm.id));
    memset(&rm.type,'\0',sizeof(rm.type));
    strcat(rm.type, "FULL");
    // Base Program
    char ch, buffer[100];
    memset(&buffer,'\0',sizeof(buffer));
    int j=0;
    bool read = true;
    bool num = true;
    char name[10];
    memset(&name,'\0',sizeof(name));
    while((ch = str[cont++]) != '\0'){
        if(ch == '-' && read){
            buffer[j] = '\0';
            memset(&name,'\0',sizeof(name));
            strcat(name, buffer);
            j = 0;
            // num = !num;
            memset(&buffer,'\0',sizeof(buffer));
        }
        if(ch == '\"' || ch == '\”'){
            read = !read;
        }
        if(isdigit(ch) && num){
            buffer[j++] = ch;
        }
        if(isalpha(ch) || ch == '/' || ch == '.' || ch == '_'){
            buffer[j++] = ch;
        }
        if(ch == '#'){
            break;
        }
        if(ch == ' ' && !read){
            buffer[j++] = ch;
        }else if((ch == ' ' || ch == '\n') && (j != 0) && read){
            buffer[j] = '\0';
            if(strcasecmp("ID", name) == 0){
                strcat(rm.id, buffer);
            }
            else if(strcasecmp("TYPE", name) == 0){
                memset(&rm.type,'\0',sizeof(rm.type));
                if (strcasecmp("Fast",buffer)==0) {
                    strcat(rm.type, "FAST");
                }else  if (strcasecmp("Full",buffer)==0) {
                    strcat(rm.type, "FULL");
                }else {
                    printf("\nELSE\n");
                    strcat(rm.type, "FULL");

                }

            }else{
                printf(RED "ERROR: COMANDO INEXISTENTE\n" RESET);
                return 0;
            }
            j = 0;
            memset(&buffer,'\0',sizeof(buffer));
        }
    }
    if((j != 0) && read){
        buffer[j] = '\0';
        // Posible optimizacion
        if(strcasecmp("ID", name) == 0){
            strcat(rm.id, buffer);
        }
        else if(strcasecmp("TYPE", name) == 0){
            memset(&rm.type,'\0',sizeof(rm.type));
            if (strcasecmp("Fast",buffer)==0) {
                strcat(rm.type, "FAST");
            }else  if (strcasecmp("Full",buffer)==0) {
                strcat(rm.type, "FULL");
            }else {
                strcat(rm.type, "FULL");
            }

        }else{
            printf(RED "ERROR: COMANDO INEXISTENTE\n" RESET);
            return 0;
        }
        j = 0;
        memset(&buffer,'\0',sizeof(buffer));
    }

    printf("\nid->%s|type->%s|\n",rm.id,rm.type);



    return 0;
}
