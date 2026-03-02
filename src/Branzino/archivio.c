#include "archivio.h"
#include "../utils/archivio.h"
#include "../utils/general.h"

#include <stdio.h>

static const char *ARCHIVE_PATH = "src/commons/Archivio.dat";
static const char *ARCHIVE_TMP_PATH = "src/commons/Archivio_tmp.dat";

static int record_exists(FILE *fp, int matricola) {
    Record r;
    rewind(fp);
    while (fread(&r, sizeof(Record), 1, fp) == 1) {
        if (r.matricola == matricola) {
            return 1;
        }
    }
    return 0;
}

void archivio_add(void) {
    Record r;
    FILE *fp = fopen(ARCHIVE_PATH, "ab+");
    if (!fp) {
        printf("Errore apertura archivio: %s\n", ARCHIVE_PATH);
        return;
    }

    read_int("Matricola: ", &r.matricola);
    if (record_exists(fp, r.matricola)) {
        printf("Matricola gia' presente.\n");
        fclose(fp);
        return;
    }
    read_string("Nome: ", r.nome, sizeof(r.nome));
    read_string("Cognome: ", r.cognome, sizeof(r.cognome));
    read_float("Stipendio: ", &r.stipendio);
    read_string("Classe: ", r.classe, sizeof(r.classe));

    if (fwrite(&r, sizeof(Record), 1, fp) != 1) {
        printf("Errore scrittura.\n");
    } else {
        printf("Record aggiunto.\n");
    }
    fclose(fp);
}

void archivio_read_all(void) {
    Record r;
    FILE *fp = fopen(ARCHIVE_PATH, "rb");
    if (!fp) {
        printf("Archivio vuoto o inesistente.\n");
        return;
    }

    printf("---- Archivio ----\n");
    while (fread(&r, sizeof(Record), 1, fp) == 1) {
        print_record(&r);
    }
    fclose(fp);
}

void archivio_update(void) {
    int matricola;
    Record r;
    FILE *fp = fopen(ARCHIVE_PATH, "r+b");
    if (!fp) {
        printf("Archivio vuoto o inesistente.\n");
        return;
    }

    read_int("Matricola da modificare: ", &matricola);
    while (fread(&r, sizeof(Record), 1, fp) == 1) {
        if (r.matricola == matricola) {
            printf("Record trovato. Inserisci i nuovi valori.\n");
            read_string("Nome: ", r.nome, sizeof(r.nome));
            read_string("Cognome: ", r.cognome, sizeof(r.cognome));
            read_float("Stipendio: ", &r.stipendio);
            read_string("Classe: ", r.classe, sizeof(r.classe));

            if (fseek(fp, -(long)sizeof(Record), SEEK_CUR) != 0) {
                printf("Errore posizionamento file.\n");
                fclose(fp);
                return;
            }
            if (fwrite(&r, sizeof(Record), 1, fp) != 1) {
                printf("Errore scrittura.\n");
            } else {
                printf("Record modificato.\n");
            }
            fclose(fp);
            return;
        }
    }

    printf("Matricola non trovata.\n");
    fclose(fp);
}

void archivio_delete_physical(void) {
    int matricola;
    int found = 0;
    Record r;
    FILE *fp = fopen(ARCHIVE_PATH, "rb");
    FILE *tmp = NULL;

    if (!fp) {
        printf("Archivio vuoto o inesistente.\n");
        return;
    }

    read_int("Matricola da cancellare (fisica): ", &matricola);

    tmp = fopen(ARCHIVE_TMP_PATH, "wb");
    if (!tmp) {
        printf("Errore creazione file temporaneo.\n");
        fclose(fp);
        return;
    }

    while (fread(&r, sizeof(Record), 1, fp) == 1) {
        if (r.matricola == matricola) {
            found = 1;
            continue;
        }
        fwrite(&r, sizeof(Record), 1, tmp);
    }

    fclose(fp);
    fclose(tmp);

    if (!found) {
        remove(ARCHIVE_TMP_PATH);
        printf("Matricola non trovata.\n");
        return;
    }

    remove(ARCHIVE_PATH);
    if (rename(ARCHIVE_TMP_PATH, ARCHIVE_PATH) != 0) {
        printf("Errore nel rinominare il file temporaneo.\n");
        return;
    }

    printf("Record cancellato fisicamente.\n");
}
