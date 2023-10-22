#include <stdlib.h>
#include "idtable.h"

#define ID_LEN 64

/* initialize a table of the given size */
void init_id_table(struct id_table* table, int len) {
    table->length = len;
    table->identifiers = malloc(len * ID_LEN);
}

/* adjust the size of the given table */
void resize_id_table(struct id_table* table, int len) {
    table->length = len;
    table->identifiers = realloc(table->identifiers, len * ID_LEN);
}

/* destroy the table */
void free_id_table(struct id_table* table) {
    free(table->identifiers);
}

/* get or add the id name to the table. returns the index. */
int get_id(struct id_table* table, const char* id) {
    int i;
    for (i = 0; i < table->length; i++) {
        if (table->identifiers[i * ID_LEN] == '\0') {
            strncpy(table->identifiers + i * ID_LEN, id, ID_LEN);
            table->identifiers[(i + 1) * ID_LEN - 1] = '\0';
            return i;
        }
        if (strcmp(table->identifiers + i * ID_LEN, id) == 0) {
            return i;
        }
    }
    return -1;
}
