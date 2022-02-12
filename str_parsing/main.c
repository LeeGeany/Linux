#include "sys.h"
#include "iofile.h"

#define MAX_TOKEN_SIZE 10

char* token[MAX_TOKEN_SIZE] =  { NULL, };

int main(void)
{
    // No.1
    printf("No.1 str_indexof()---------------------------------------------\n");
    int index = str_indexof("helworldhelloworldfqwhoworld", "helloworld", 0);
    printf("index : %d\n", index);
    
    // No.2
    printf("\nNo.2 str_trim()--------------------------------------------------\n");
    char* str2 = str_trim("  hello world  ");
    printf("trim  : %sEOF\n", str2);

    //No.3
    printf("\nNo.2 str_insert()--------------------------------------------------\n");
    char* str3 = str_insert("helloworld", "new", 5);
    printf("insert : %s\n", str3);

    // No.4
    printf("\nNo.4 str_delete()------------------------------------------------\n");
    char* str4 = str_delete("hellonewworld", 5, 3);
    printf("delete : %s\n", str4);

    // No.5
    printf("\nNo.5 str_substring()---------------------------------------------\n");
    char * str5 = str_substring("adfahelloworldqefqwe", 4, 10);
    printf("substring : %s\n", str5);

    // No.6
    printf("\nNo.6 str_split()-------------------------------------------------\n");
    int ret = str_split("helloworld goodmorning goodafternoon", token, ' ');
    for(int i = 0; i< 3; ++i)
    {
        printf("%d tokens : %s\n", i + 1, token[i]);
    }

    // No.7
    printf("\nNo.7 str_replace()-------------------------------------------------\n");
    char* str7 = str_replace("helgoodrld", "good", "lowo");
    printf("replace : %s\n", str7);

    // No.8
    printf("\nNo.8 str_tostring()-------------------------------------------------\n");
    char* str8 = str_tostring(12341234);
    printf("tostring : %s\n", str8);

    // No.9
    printf("\nNo.9 str_tointeger()-------------------------------------------------\n");
    int str9 = str_tointeger("1234", '\0');
    printf("tointeger : %d\n", str9);

    printf("\n------------------------------end line-------------------------------\n");

    FILE* fp = fopen("./Linux_2k.log", "r");
    while(1){
        
        char buffer[MAX_BUFFER_LEN] = { 0 };
        char* tokens[MAX_TOKEN_SIZE] =  { NULL, };
        char* ret = fgets(buffer, MAX_BUFFER_LEN, fp);
        if(ret == NULL){break;}
        str_split(buffer, tokens, ' ');
    
// quiz 1
        if(str_indexof(tokens[4], "ftpd", 0) > -1)
        {
            insert_ip_count(tokens[7]);
        }

// quiz 2
        if(str_indexof(tokens[4], "sshd", 0) > -1)
        {
            insert_fail_count(tokens[0], tokens[1]);
        }

// quiz 3
        insert_opt_count(tokens[4]);
    }

    infile1();
    infile2();
    infile3();

    close(fp);
    
    return 0;
}