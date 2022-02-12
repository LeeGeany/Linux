#include "parse.h"

int str_strcmp(char* oper1, char* oper2){
    char* o1 = oper1;
    char* o2 = oper2;
    
    while(1){
        if(*o1 != *o2)
        {
            return 1;
        }

        if(*o1 == '\0' && *o2 == '\0')
        {
            return 0;
        }

        if(*o1 == '\0' || *o2 == '\0')
        {
            return 1;
        }
        o1++; o2++;
    }

    return 0;
}

int str_strlen(char* str)
{
    int ret = 0;
    for(char* idx = str; *idx !='\0'; ++idx)
    {
        ret++;
    }
    
    return ret;
}

int str_indexof(const char* str, const char* target, int start)
{
    for(char* idx = str + start; *idx != '\0'; idx++)
    {
        if(*idx == *target)
        {
            char* start = idx;
            int flag = 0;
            for(char* sidx = target; *sidx != '\0'; ++sidx)
            {
                if(*sidx != *start)
                {
                    flag = 1;
                    break;
                }
                start++;
            }
            if(!flag)
            {
                return idx-str;
            }
        }
    }
   
    return -1;
}

char* str_trim(char* str)
{
    int len = str_strlen(str);
    char* rstr = (char*)malloc(sizeof(char) * len);
    
    char* head = NULL;
    char* tail = NULL;
    for(head = str; *head != '\0'; ++head)
    {
        if(*head != ' ') 
        {
            break;
        }
    }

    for(tail = str + str_strlen(str) - 1; tail != str; --tail )
    {
        if(*tail != ' ')
        {
            break;
        }   
    }
    memcpy(rstr, head, (tail + 1 - head));
    return rstr;
}

char* str_insert(char* str, char* target, int index)
{
	char* result = (char*)malloc(sizeof(str) + sizeof(target) + index);
	int r_cnt = 0;

	for(int i =0; i < index;i++)
	{
		result[r_cnt++] = str[i];
	}

	for(char* i = target ; *i != '\0'; i++)
	{
		result[r_cnt++] = *i;
	}

	for(char* i = str + index + 1; *i != '\0'; i++)
	{
		result[r_cnt++] = *i;
	}
    result[r_cnt] = '\0';
    return result;
}

char* str_delete(char* str, int target_index, int num)
{
	char* result = (char*)malloc(sizeof(str));
	int idx = target_index + num;
    int len = str_strlen(str);

    memcpy(result, str, target_index);
    memcpy(result + target_index, str + idx, len - idx);
	
    return result;
}

char* str_substring(char* str, int start, int cnt)
{   
    char* rstr = (char*)malloc(sizeof(char) * (cnt + 1));
    
    for(int i = 0; i < cnt; ++i )
    {
        rstr[i] = str[start + i]; 
    }
    
    rstr[cnt] = '\0';
    return rstr;
}

int str_split(char* str, char* tokens[], char target)
{
    int token_cnt = 0;
    char* start = str;
    char* idx = NULL;

    for(idx = str; *idx != '\0'; ++idx)
    {
        if(*idx == target)
        {
            char* nstr = (char*)malloc(sizeof(char) * (idx - start + 2));
            
            int sidx = 0;
            for(sidx = 0; sidx < (idx - start); sidx++)
            {
                nstr[sidx] = *(start + sidx);
            }
            nstr[++sidx] = '\0';
            start = idx + 1;
            tokens[token_cnt++] = nstr;
        }
    }
    
    char* nstr = (char*)malloc(sizeof(char) * (++idx - start + 2));
            
    int sidx = 0;
    for(sidx = 0; sidx < (idx - start); sidx++)
    {
        nstr[sidx] = *(start + sidx);
    }
    nstr[++sidx] = '\0';
    start = idx + 1;
    tokens[token_cnt++] = nstr;

    return token_cnt;
}

char *str_replace(char *s, const char *olds, const char *news) {
  char *result, *sr;
  size_t i, count = 0;
  size_t oldlen = strlen(olds); if (oldlen < 1) return s;
  size_t newlen = strlen(news);


  if (newlen != oldlen) {
    for (i = 0; s[i] != '\0';) {
      if (memcmp(&s[i], olds, oldlen) == 0) count++, i += oldlen;
      else i++;
    }
  } else i = strlen(s);


  result = (char *) malloc(i + 1 + count * (newlen - oldlen));
  if (result == NULL) return NULL;

  sr = result;

  while (*s) {
    if (memcmp(s, olds, oldlen) == 0) {
      memcpy(sr, news, newlen);
      sr += newlen;
      s  += oldlen;
    } else *sr++ = *s++;
  }
  *sr = '\0';

  return result;
} 

char* str_tostring(int num){
    int tmp = num;
    int cnt = 0;
    while(tmp!=0){
        tmp/=10;
        cnt++;
    }
    char* s = (char*)malloc(sizeof(char) * cnt);
    s[cnt]='\0'; 
    do{ 
        cnt--;              
        s[cnt]=(char)(num%10+48);
        num = num/10;
        
    }while(num!=0);   

    return s;
}

int str_tointeger(char *s, char last){
    int tmp=0;
    for(char* n = s; *s != last; ++n){    
        tmp = tmp * 10 + (int)*s-48;      
        s++;
    }
    return tmp;
}
