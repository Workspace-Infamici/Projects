#include "menu.h"
#include "archivio.h"
#include "general.h"

#include <stdio.h>

void menu_principale() {
    printf("\n===== MENU PRINCIPALE =====\n");
    printf("1. Accesso Utente\n");
    printf("2. Accesso Amministratore\n");
    printf("3. Esci dal programma\n");
}

void menu_admin() {
    printf("\n===== Archivio (Admin) =====\n");
    printf("1. Aggiungi un record\n");
    printf("2. Visualizza archivio\n");
    printf("3. Modifica un record\n");
    printf("4. Cancellazione fisica\n");
    printf("5. Cancellazione logica\n");
    printf("6. Ripristina record\n");
    printf("7. Logout (Torna al Menu Principale)\n");
}

void menu_user() {
    printf("\n===== Archivio (Utente) =====\n");
    printf("1. Aggiungi un record\n");
    printf("2. Visualizza archivio\n");
    printf("3. Cancellazione logica\n");
    printf("4. Logout (Torna al Menu Principale)\n");
}

void sessione_admin() {
    int choice = 0;
    int result = 0;

    // le menti piu' sagaci riconosceranno il riferimento nella seguente riga
    for (;;) {
        menu_admin();
        read_int("Scelta: ", &choice);
        switch (choice) {
            case 1: {
                Record r;
                read_int("Matricola: ", &r.matricola);
                read_string("Nome: ", r.nome, sizeof(r.nome));
                read_string("Cognome: ", r.cognome, sizeof(r.cognome));
                read_float("Stipendio: ", &r.stipendio);
                read_string("Classe: ", r.classe, sizeof(r.classe));
                r.cancellato = 0;

                result = archivio_add(&r);
                if (result == 1) {
                    printf("Record aggiunto.\n");
                } else if (result == 0) {
                    printf("Matricola gia' presente.\n");
                } else {
                    printf("Errore scrittura.\n");
                }
                break;
            }
            case 2:
                result = archivio_read_all();
                if (result < 0) {
                    printf("Archivio vuoto o inesistente.\n");
                } else if (result == 0) {
                    printf("Archivio vuoto.\n");
                }
                break;
            case 3: {
                int matricola = 0;
                Record nuovo;
                read_int("Matricola da modificare: ", &matricola);
                read_string("Nome: ", nuovo.nome, sizeof(nuovo.nome));
                read_string("Cognome: ", nuovo.cognome, sizeof(nuovo.cognome));
                read_float("Stipendio: ", &nuovo.stipendio);
                read_string("Classe: ", nuovo.classe, sizeof(nuovo.classe));
                nuovo.matricola = matricola;
                nuovo.cancellato = 0;

                result = archivio_update(matricola, &nuovo);
                if (result == 1) {
                    printf("Record modificato.\n");
                } else if (result == 0) {
                    printf("Matricola non trovata.\n");
                } else {
                    printf("Errore scrittura.\n");
                }
                break;
            }
            case 4: {
                int matricola = 0;
                read_int("Matricola da cancellare (fisica): ", &matricola);
                result = archivio_delete_physical(matricola);
                if (result == 1) {
                    printf("Record cancellato fisicamente.\n");
                } else if (result == 0) {
                    printf("Matricola non trovata.\n");
                } else {
                    printf("Errore durante la cancellazione.\n");
                }
                break;
            }
            case 5: {
                int matricola = 0;
                read_int("Matricola da cancellare (logica): ", &matricola);
                result = archivio_delete_logical(matricola);
                if (result == 1) {
                    printf("Record cancellato logicamente.\n");
                } else if (result == 0) {
                    printf("Matricola non trovata o gia' cancellata.\n");
                } else {
                    printf("Errore durante la cancellazione.\n");
                }
                break;
            }
            case 6: {
                int matricola = 0;
                read_int("Matricola da ripristinare: ", &matricola);
                result = archivio_restore(matricola);
                if (result == 1) {
                    printf("Record ripristinato.\n");
                } else if (result == 0) {
                    printf("Matricola non trovata o non cancellata.\n");
                } else {
                    printf("Errore durante il ripristino.\n");
                }
                break;
            }
            case 7:
                printf("Uscita.\n");
                return;
            default:
                printf("Scelta non valida.\n");
        }
    }
}

void sessione_user() {
    int choice = 0;
    int result = 0;
    int in_esecuzione = 1; // flag per controllare il loop


    // ### DA VALUTARE QUALI OPERAZIONI PERMETTERE AGLI UTENTI (FORSE SOLO AGGIUNTA E VISUALIZZAZIONE?) ###
    do {
        // mostra il menu utente e legge la scelta
        menu_user();
        read_int("Scelta: ", &choice);

        switch (choice) {
            // aggiungi un record
            case 1: {
                Record r;
                read_int("Matricola: ", &r.matricola);
                read_string("Nome: ", r.nome, sizeof(r.nome));
                read_string("Cognome: ", r.cognome, sizeof(r.cognome));
                read_float("Stipendio: ", &r.stipendio);
                read_string("Classe: ", r.classe, sizeof(r.classe));
                r.cancellato = 0;

                result = archivio_add(&r);
                if (result == 1) {
                    printf("Record aggiunto.\n");
                } else if (result == 0) {
                    printf("Matricola gia' presente.\n");
                } else {
                    printf("Errore scrittura.\n");
                }
                break;
            }
            // visualizza archivio
            case 2:
                result = archivio_read_all();
                if (result < 0) {
                    printf("Archivio vuoto o inesistente.\n");
                } else if (result == 0) {
                    printf("Archivio vuoto.\n");
                }
                break;
            // cancellazione logica
            case 3: {
                int matricola = 0;
                read_int("Matricola da cancellare (logica): ", &matricola);
                result = archivio_delete_logical(matricola);
                if (result == 1) {
                    printf("Record cancellato logicamente.\n");
                } else if (result == 0) {
                    printf("Matricola non trovata o gia' cancellata.\n");
                } else {
                    printf("Errore durante la cancellazione.\n");
                }
                break;
            }
            // logout
            case 4:
                printf("Uscita.\n");
                in_esecuzione = 0; // imposta il flag a 0 per uscire dal loop
                break;
            // scelta non valida
            default:
                printf("Scelta non valida.\n");
        }
    } while (in_esecuzione); // il loop continua finché in_esecuzione è vero
}