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

void archivio_add(void);
void archivio_read_all(void);
void archivio_update(void);
void archivio_delete_physical(void);

#endif
