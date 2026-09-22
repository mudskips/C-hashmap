#include <stdio.h>
#include <string.h>

//key has to be a string
size_t hash(char *key){
    size_t hash = 0;

    for (size_t i=0; i < strlen(key); i++){
        hash += ((int)key[i] * 67) / 3;
    }

    return hash;
}

int main(){

    printf("%zu\n", hash("word"));
    return 0;

}