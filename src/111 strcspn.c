#include "s21_string.h"

size_t strcspn(const char *str1, const char *str2) {
    int i, j, a[256];
    for(i=0; i<256; i++) {
        a[i]=0;
    }
    for(j=0; str2[j]; j++) {
        a[(unsigned int)str2[j]]=1; 
        }
    for(i=0; str1[i]; i++) {
        if(a[(unsigned int)str1[i]]) {
            return i;
        }
    }
    return i;
}
