#ifndef SHT_TABLE_H
#define SHT_TABLE_H
#include <record.h>
#include <ht_table.h>

#define SHT_RECORDS_PER_BLOCK ((BF_BLOCK_SIZE / sizeof(SHT_Record)) - 1)

/* Δομή αποθήκευσης μεταδεδομένων δευτερεύοντος ευρετηρίου.*/
typedef struct {
    char FileName[15];
    int FileDescriptor;
    int NumberOfBuckets;
    int BucketDefinitionsBlock;
    Bucket_Info *HashtableMapping;
} SHT_info;

/* Δομή αποθήκευσης μεταδεδομένων μπλοκ δευτερεύοντος ευρετηρίου.*/
typedef struct {
    int RecordCount;
    int PreviousBlockId;
} SHT_block_info;

/* Δομή εγγραφών δευτερεύοντος ευρετηρίου.*/
typedef struct{
    char name[15];
    int blockId;
    int numberOfAppearences;
} SHT_Record;


/*Η συνάρτηση SHT_CreateSecondaryIndex χρησιμοποιείται για τη δημιουργία
και κατάλληλη αρχικοποίηση ενός αρχείου δευτερεύοντος κατακερματισμού με
όνομα sfileName για το αρχείο πρωτεύοντος κατακερματισμού fileName. Σε
περίπτωση που εκτελεστεί επιτυχώς, επιστρέφεται 0, ενώ σε διαφορετική
περίπτωση -1.*/
int SHT_CreateSecondaryIndex(
    char *sfileName, /* όνομα αρχείου δευτερεύοντος ευρετηρίου*/
    int buckets, /* αριθμός κάδων κατακερματισμού*/
    char* fileName /* όνομα αρχείου πρωτεύοντος ευρετηρίου*/);



/* Η συνάρτηση SHT_OpenSecondaryIndex ανοίγει το αρχείο με όνομα sfileName
και διαβάζει από το πρώτο μπλοκ την πληροφορία που αφορά το δευτερεύον
ευρετήριο κατακερματισμού.*/
SHT_info* SHT_OpenSecondaryIndex(
    char *sfileName /* όνομα αρχείου δευτερεύοντος ευρετηρίου */);

/*Η συνάρτηση SHT_CloseSecondaryIndex κλείνει το αρχείο που προσδιορίζεται
μέσα στη δομή header_info. Σε περίπτωση που εκτελεστεί επιτυχώς, επιστρέφεται
0, ενώ σε διαφορετική περίπτωση -1. Η συνάρτηση είναι υπεύθυνη και για την
αποδέσμευση της μνήμης που καταλαμβάνει η δομή που περάστηκε ως παράμετρος,
στην περίπτωση που το κλείσιμο πραγματοποιήθηκε επιτυχώς.*/
int SHT_CloseSecondaryIndex( SHT_info* header_info );

/*Η συνάρτηση SHT_SecondaryInsertEntry χρησιμοποιείται για την εισαγωγή μιας
εγγραφής στο αρχείο κατακερματισμού. Οι πληροφορίες που αφορούν το αρχείο
βρίσκονται στη δομή header_info, ενώ η εγγραφή προς εισαγωγή προσδιορίζεται
από τη δομή record και το block του πρωτεύοντος ευρετηρίου που υπάρχει η εγγραφή
προς εισαγωγή. Σε περίπτωση που εκτελεστεί επιτυχώς, επιστρέφεται 0, ενώ σε
διαφορετική περίπτωση -1.*/
int SHT_SecondaryInsertEntry(
    SHT_info* header_info, /* επικεφαλίδα του δευτερεύοντος ευρετηρίου*/
    Record record, /* η εγγραφή για την οποία έχουμε εισαγωγή στο δευτερεύον ευρετήριο*/
    int block_id /* το μπλοκ του αρχείου κατακερματισμού στο οποίο έγινε η εισαγωγή */);

/*Η συνάρτηση αυτή χρησιμοποιείται για την εκτύπωση όλων των εγγραφών που
υπάρχουν στο αρχείο κατακερματισμού οι οποίες έχουν τιμή στο πεδίο-κλειδί
του δευτερεύοντος ευρετηρίου ίση με name. Η πρώτη δομή περιέχει πληροφορίες
για το αρχείο κατακερματισμού, όπως αυτές είχαν επιστραφεί κατά το άνοιγμά
του. Η δεύτερη δομή περιέχει πληροφορίες για το δευτερεύον ευρετήριο όπως
αυτές είχαν επιστραφεί από την SHT_OpenIndex. Για κάθε εγγραφή που υπάρχει
στο αρχείο και έχει όνομα ίσο με value, εκτυπώνονται τα περιεχόμενά της
(συμπεριλαμβανομένου και του πεδίου-κλειδιού). Να επιστρέφεται επίσης το
πλήθος των blocks που διαβάστηκαν μέχρι να βρεθούν όλες οι εγγραφές. Σε
περίπτωση λάθους επιστρέφει -1.*/
int SHT_SecondaryGetAllEntries(
    HT_info* ht_info, /* επικεφαλίδα του αρχείου πρωτεύοντος ευρετηρίου*/
    SHT_info* header_info, /* επικεφαλίδα του αρχείου δευτερεύοντος ευρετηρίου*/
    char* name /* το όνομα στο οποίο γίνεται αναζήτηση */);

int SHT_HashStatistics( char* filename /* όνομα του αρχείου που ενδιαφέρει */ );

#endif // SHT_FILE_H
