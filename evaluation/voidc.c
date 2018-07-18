/*************************************************************************
    > File Name: voidc.c
    > Author: reeves
    > Mail: seereeves@163.com 
    > Created Time: 17/07/2018 - 09:28
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef double ElemType;

typedef struct list {
    int len;
    int free;
    size_t size;
    void *buf;
} LIST;

LIST *create_list(int len, size_t size) {
    LIST *pl = (LIST *)malloc(sizeof(LIST));
    pl->len = 0;
    pl->free = len;
    pl->size = size;
    pl->buf = (void *)malloc(size*len);
    return pl;
}

int get_buf_len(LIST *pl) {
    if (NULL == pl)
        return 0;
    return pl->len;
}

void *assign_value(void *dest, const void *val, size_t size) {
    memcpy(dest, val, size);
    return dest;
}

int insert_list_sq(LIST *pl, void *val, size_t size) {
    assign_value(pl->buf+(pl->len)*size, val, size);
    ++pl->len;
    --pl->free;
    return 0;
}

void traversal(LIST *pl) {
    printf("****** traversal ******\n");
  /*  if (4 == pl->size)
        float *tmp;
    else if (1 == pl->size)
        char *tmp;
    else
        double *tmp;
*/
    ElemType *tmp;
    char *itr;
    for (int i=0; i<pl->len; ++i) {
        assign_value(tmp, pl->buf+i*pl->size, pl->size);
        printf("%f ", *(tmp));
    }
    printf("\n****** traversal ******\n");
}

int main() {
    LIST *pl = create_list(100, sizeof(ElemType));
    void *vp;
    for (ElemType i = 0; i < 11; ++i) {
        vp = (void *)&i;
        insert_list_sq(pl, vp, sizeof(ElemType));
    }
    traversal(pl);
    return 0;
}
