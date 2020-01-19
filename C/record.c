// createDataFile.c :
// Creates a file records.dat with some test data.
// ---------------------------------------------------------------
#include <stdio.h>
#include "record.h"

char dataFile[] = "/tmp/records.dat"; // Filename.

int main() // Creates a file records.dat (inFile) with some test data.
{
    FILE *fp;
    Record_t records[] = {{1789L, "George"},
                          {1797L, "John"},
                          {0L, "Harry"},
                          {1801L, "Thomas"},
                          {1809L, "James"},
                          {1825L, "Quincy"}};
    size_t n = sizeof(records) / sizeof(*records);

    if ((fp = fopen(dataFile, "wb")) == NULL)
    {
        fprintf(stderr, "Error on opening output file \"%s\".\n", dataFile);
        return 1;
    }
    if (fwrite(records, sizeof(Record_t), n, fp) < n)
    {
        fprintf(stderr, "Error on writing to output file \"%s\".\n", dataFile);
        return 1;
    }
    printf("%zu records written.\n", n);
    //it is better to close all open files by code
    //but anyway, the kernel will close all open files  
    return 0;
}
