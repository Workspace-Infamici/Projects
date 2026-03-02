#include "Branzino/archivio.h"
#include "utils/general.h"

#include <stdio.h>

static void menu(void) {
    printf("\n===== Archivio (Admin) =====\n");
    printf("1. Aggiungi record\n");
    printf("2. Visualizza archivio\n");
    printf("3. Modifica record\n");
    printf("4. Cancellazione fisica\n");
    printf("5. Esci\n");
}

int main(void) {
    int choice = 0;
    
    //le menti più sagaci riconosceranno il riferimento nella seguente riga
    for (;;) {
        menu();
        read_int("Scelta: ", &choice);
        switch (choice) {
            case 1:
                archivio_add();
                break;
            case 2:
                archivio_read_all();
                break;
            case 3:
                archivio_update();
                break;
            case 4:
                archivio_delete_physical();
                break;
            case 5:
                printf("Uscita.\n");
                return 0;
            default:
                printf("Scelta non valida.\n");
        }
    }
}
