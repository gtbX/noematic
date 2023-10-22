#ifndef ID_TABLE_H
#define ID_TABLE_H

struct id_table {
    int length;
    char* identifiers;
};

/* initialize a table of the given size */
void init_id_table(struct id_table* table, int len);

/* adjust the size of the given table */
void resize_id_table(struct id_table* table, int len);

/* destroy the table */
void free_id_table(struct id_table* table);

/* get or add the id name to the table. returns the index. */
int get_id(struct id_table* table, const char* id);

#endif  //STRING_TABLE_H
