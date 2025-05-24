// Creați un dicționar simplu folosind un hash table.
// Utilizatorii trebuie să poată:
//       să adauge cuvinte noi (perechi chei-valori),
//       să caute definiții folosindu-se de chei,
//       să șteargă cuvinte din dicționar

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct Entry
{
    char *key;
    char *value;
    struct Entry *next;
} Entry;

typedef struct HashTable
{
    Entry **entries;
} HashTable;

unsigned int hashFunction(const char *key)
{
    unsigned long int hashValue = 0;
    size_t keyLen = strlen(key);

    for (unsigned int i = 0; i < keyLen; ++i)
    {
        hashValue = hashValue * 37 + (unsigned char)key[i];
    }
    return hashValue % TABLE_SIZE;
}

Entry *createEntry(const char *key, const char *value)
{
    Entry *newEntry = (Entry *)malloc(sizeof(Entry));
    if (!newEntry)
    {
        fprintf(stderr, "Eroare la alocarea memoriei pentru intrare\n");
        return NULL;
    }
    newEntry->key = strdup(key);
    if (!newEntry->key)
    {
        fprintf(stderr, "Eroare la alocarea memoriei pentru cheia intrarii\n");
        free(newEntry);
        return NULL;
    }
    newEntry->value = strdup(value);
    if (!newEntry->value)
    {
        fprintf(stderr, "Eroare la alocarea memoriei pentru valoarea intrarii\n");
        free(newEntry->key);
        free(newEntry);
        return NULL;
    }
    newEntry->next = NULL;
    return newEntry;
}

HashTable *createTable()
{
    HashTable *newTable = (HashTable *)malloc(sizeof(HashTable));
    if (!newTable)
    {
        fprintf(stderr, "Eroare la alocarea memoriei pentru tabela hash");
        return NULL;
    }
    newTable->entries = (Entry **)calloc(TABLE_SIZE, sizeof(Entry *));
    if (!newTable->entries)
    {
        fprintf(stderr, "Eroare la alocarea memoriei pentru intrarile tabelei");
        free(newTable);
        return NULL;
    }
    return newTable;
}

void htInsert(HashTable *table, const char *key, const char *value)
{
    if (!table || !key || !value)
    {
        return;
    }

    unsigned int slot = hashFunction(key);
    Entry *currentEntry = table->entries[slot];

    if (currentEntry == NULL)
    {
        table->entries[slot] = createEntry(key, value);
        return;
    }

    Entry *previousEntry = NULL;

    while (currentEntry != NULL)
    {
        if (strcmp(currentEntry->key, key) == 0)
        {
            free(currentEntry->value);
            currentEntry->value = strdup(value);
            if (!currentEntry->value)
            {
                fprintf(stderr, "Eroare la actualizarea valorii");
            }
            return;
        }
        previousEntry = currentEntry;
        currentEntry = previousEntry->next;
    }
    previousEntry->next = createEntry(key, value);
}

char *htSearch(HashTable *table, const char *key)
{
    if (!table || !key)
    {
        return NULL;
    }

    unsigned int slot = hashFunction(key);
    Entry *currentEntry = table->entries[slot];

    while (currentEntry != NULL)
    {
        if (strcmp(currentEntry->key, key) == 0)
        {
            return currentEntry->value;
        }
        currentEntry = currentEntry->next;
    }
    return NULL;
}

void htDelete(HashTable *table, const char *key)
{
    if (!table || !key)
    {
        return;
    }

    unsigned int slot = hashFunction(key);
    Entry *currentEntry = table->entries[slot];
    Entry *previousEntry = NULL;

    while (currentEntry != NULL)
    {
        if (strcmp(currentEntry->key, key) == 0)
        {
            if (previousEntry == NULL)
            {
                table->entries[slot] = currentEntry->next;
            }
            else
            {
                previousEntry->next = currentEntry->next;
            }
            free(currentEntry->key);
            free(currentEntry->value);
            free(currentEntry);
            return;
        }
        previousEntry = currentEntry;
        currentEntry = currentEntry->next;
    }
}

void freeTable(HashTable *table)
{
    if (!table)
    {
        return;
    }
    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        Entry *currentEntry = table->entries[i];
        while (currentEntry != NULL)
        {
            Entry *tempEntry = currentEntry;
            currentEntry = currentEntry->next;
            free(tempEntry->key);
            free(tempEntry->value);
            free(tempEntry);
        }
    }
    free(table->entries);
    free(table);
}

int main()
{
    HashTable *dictionar = createTable();
    if (!dictionar)
    {
        return 1;
    }

    int choice;
    char key[256];
    char value[1024];

    do
    {
        printf("\nMeniu Dictionar: (0 pentru iesire)\n");
        printf("1. Adauga cuvant\t");
        printf("2. Cauta definitie\n");
        printf("3. Sterge cuvant\t");
        printf("4. Afiseaza toate intrarile\n");
        printf("Alege o optiune: ");

        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n')
                ;
            printf("Optiune invalida.\n");
            continue;
        }
        while (getchar() != '\n')
            ;

        switch (choice)
        {
        case 1:
            printf("Introdu cheia (cuvantul): ");
            if (fgets(key, sizeof(key), stdin) == NULL)
            {
                fprintf(stderr, "Eroare la citirea cheii.\n");
                continue;
            }
            key[strcspn(key, "\n")] = 0;

            printf("Introdu valoarea (definitia): ");
            if (fgets(value, sizeof(value), stdin) == NULL)
            {
                fprintf(stderr, "Eroare la citirea valorii.\n");
                continue;
            }
            value[strcspn(value, "\n")] = 0;

            htInsert(dictionar, key, value);
            printf("Cuvant adaugat/actualizat.\n");
            break;
        case 2:
            printf("Introdu cheia (cuvantul) de cautat: ");
            if (fgets(key, sizeof(key), stdin) == NULL)
            {
                fprintf(stderr, "Eroare la citirea cheii.\n");
                continue;
            }
            key[strcspn(key, "\n")] = 0;

            char *definitie = htSearch(dictionar, key);
            if (definitie)
            {
                printf("Definitia pentru '%s': %s\n", key, definitie);
            }
            else
            {
                printf("Definitia pentru '%s' nu a fost gasita.\n", key);
            }
            break;
        case 3:
            printf("Introdu cheia (cuvantul) de sters: ");
            if (fgets(key, sizeof(key), stdin) == NULL)
            {
                fprintf(stderr, "Eroare la citirea cheii.\n");
                continue;
            }
            key[strcspn(key, "\n")] = 0;
            htDelete(dictionar, key);
            printf("Cuvantul '%s' sters (daca exista).\n", key);
            break;
        case 4:
            printf("\n--- Toate Intrarile din Dictionar ---\n");
            for (int i = 0; i < TABLE_SIZE; ++i)
            {
                Entry *entry = dictionar->entries[i];
                if (entry != NULL)
                {
                    printf("Bucket %d:\n", i);
                    while (entry != NULL)
                    {
                        printf("  '%s': '%s'\n", entry->key, entry->value);
                        entry = entry->next;
                    }
                }
            }
            printf("--- Sfarsit Lista ---\n");
            break;
        case 0:
            printf("Iesire...\n");
            break;
        default:
            printf("Optiune invalida. Te rog incearca din nou.\n");
        }
    } while (choice != 0);


    freeTable(dictionar);

    return 0;
}