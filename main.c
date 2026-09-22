#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASHMAP_SIZE 10

typedef struct Node {
    char *key;
    int value;
    struct Node *next;
} Node;

typedef struct {
    //each spot is the head of a linked list
    Node *hashmap[HASHMAP_SIZE];
} Map;
//key has to be a string
size_t hash(char *key){
    size_t hash = 0;

    for (size_t i=0; key[i] != '\0'; i++){
        hash += ((unsigned char)key[i] * 67) / 3;
    }

    return hash % HASHMAP_SIZE;
}

void init_hashmap(Map *map){
    for (size_t i= 0; i < HASHMAP_SIZE; i ++){
        map->hashmap[i] = NULL;
    }
}

int insert(Map *map, char *key, int value){
    size_t index = hash(key);
    Node *current = map->hashmap[index];
    while(current != NULL){
        if (strcmp(current->key, key) == 0){
            current->value = value;
            return 0;
        }
        current = current->next;
    }
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        return 1;
    }
    new_node->key = malloc(strlen(key) + 1);
    if (new_node->key == NULL) {
        free(new_node);
        return 1;
    }
    strcpy(new_node->key, key);
    new_node->value = value;
    new_node->next = map->hashmap[index];
    map->hashmap[index] = new_node;
    return 0;
}

int remove_key(Map *map, char *key){
    size_t index = hash(key);
    Node *current = map->hashmap[index];
    Node *prev = NULL;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
        if (prev == NULL) {
            map->hashmap[index] = current->next;
        } 
        else {
            prev->next = current->next;
        }
        free(current->key);
        free(current);
        return 0;
        }
        prev = current;
        current = current->next;
    }
    return 1;
}

int get(Map *map, char *key, int *out){
    size_t index = hash(key);
    Node *current = map->hashmap[index];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            *out = current->value;
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void free_map(Map *map){
    for (size_t i = 0; i < HASHMAP_SIZE; i++) {
        Node *current = map->hashmap[i];
        while (current != NULL) {
            Node *next = current->next;
            free(current->key);
            free(current);
            current = next;
        }
    }
    free(map);
}

void print_map(Map *map){
    for (size_t i=0; i < HASHMAP_SIZE; i++){
        Node *current = map->hashmap[i];
        while(current != NULL){
            printf("[%s: %d]\n", current->key, current -> value);
            current = current->next;
        }
        printf("NULL, NULL\n");
    }
}

int main(){
    Map *map = malloc(sizeof(Map));
    if(map == NULL){
        return 1;
    }
    init_hashmap(map);
    insert(map, "telephone", 789);
}