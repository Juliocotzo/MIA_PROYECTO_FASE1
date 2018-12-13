#include <stdio.h>
#include <stdlib.h>

typedef struct mbr_partition{
    char part_status;
    char part_type;
    char part_fit;
    int part_start;
    int part_size;
    char part_name[16];
} MBR_P;

typedef struct MBR{
    int mbr_tamanio;
    char mbr_fecha_creacion[16];
    int mbr_disk_signature;
    MBR_P mbr_partition[4];
} MBR;

typedef struct EBR{
    char part_status;
    char part_fit;
    int part_start;
    int part_size;
    int part_next;
    char part_name[16];
} EBR_P;

typedef struct nodo{
    char nombre[40];
    char path[100];
    char id[10];
    char letra[10];
    char numero[10];
    int numdiscos;
    struct nodo *siguiente;
    struct nodo *anterior;
}nodo;
