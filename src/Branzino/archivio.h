#ifndef BRANZINO_ARCHIVIO_H
#define BRANZINO_ARCHIVIO_H

#define NAME_LEN 32
#define SURNAME_LEN 32
#define CLASS_LEN 4

typedef struct {
    int matricola;
    char nome[NAME_LEN];
    char cognome[SURNAME_LEN];
    float stipendio;
    char classe[CLASS_LEN];
} Record;

int archivio_add(const Record *r);
int archivio_read_all();
int archivio_update(int matricola, const Record *nuovo);
int archivio_delete_physical(int matricola);

#endif
