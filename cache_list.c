#include <stdbool.h>
#include <stdlib.h>
#include "cache_list.h"

/*! Création d'une liste de blocs */
struct Cache_List *Cache_List_Create() {
	struct Cache_List *cache_list = (struct Cache_List*) malloc(sizeof(struct Cache_List));//+1?
    /** On fait pointer next et prev sur lui même parce que circulaire */
	cache_list->prev = cache_list->next = cache_list;
    /** On initialise le header */
	cache_list->pheader=NULL;
	return cache_list;
}



/*! Destruction d'une liste de blocs */
void Cache_List_Delete(struct Cache_List *list) {
    struct Cache_List *bloc;
    if (!Cache_List_Is_Empty(list)) {
        for (bloc = list->next; bloc != list; bloc = bloc->next) {
            bloc->pheader    = NULL; // On met le header à NULL
            bloc->prev->next = bloc->next;  //le next du précédent devient le suivant de l'actuel
            bloc->next->prev = bloc->prev;  // le précédent du next devient le précédent de l'actuel
            free(bloc);                    //on free le bloc actuel
        }
    }
    bloc->pheader = NULL; //? je sais pas si on doit le metttre à null avant de free
    free(list);           // on free la list
}



/*! Insertion d'un élément à la fin */
void Cache_List_Append(struct Cache_List *list, struct Cache_Block_Header *pbh) {
    if (Cache_List_Is_Empty(list)) {
        list->pheader = pbh;
        return;
    }
    /** On va jusqu'à la fin de la liste : tmp est le dernier élément de la liste */
    struct Cache_List *tmp = list->prev;
    
    /** Donc là tmp est le dernier bloc */
    struct Cache_List *element_to_add = Cache_List_Create();
    element_to_add->pheader = pbh;
    /** On fait la connexion de element_to_add */
    element_to_add->next = list;
    element_to_add->prev = tmp;
    /** On fait la connexion du premier element de la liste */
    list->prev = element_to_add;
    /** On fait la connexion de feu le dernier élement de la liste */
    tmp->next = element_to_add;
}






/*! Insertion d'un élément au début*/
void Cache_List_Prepend(struct Cache_List *list, struct Cache_Block_Header *pbh){
    if (Cache_List_Is_Empty(list)){
    list->pheader=pbh;
    return;
    }
    struct Cache_List *element_to_add = Cache_List_Create(); // on crée un nouvel élément

    element_to_add->next = list->next;//?? on fait element_to_add->next = first; après, sert à qqch?
    element_to_add->prev = list;
    element_to_add->pheader = list->pheader; // on met le header du nouvel élément à pbh
    
    list->pheader = pbh;

    struct Cache_List *first = list; // on récupère le second élément de la liste

    first->next->prev = element_to_add;    // le dernier a son next sur le nouvel élément
    first->next=element_to_add;     // le précédent du nouvel élément sera 
}





/*! Retrait du premier élément */
struct Cache_Block_Header *Cache_List_Remove_First(struct Cache_List *list){
    if(Cache_List_Is_Empty(list)) {
        printf("Pas de remove first sur une liste vide\n");
        return;
    }
        struct Cache_List *first=list;
        struct Cache_List *second;
        if (first->next!=first) {
            second = list->next;
        } else {
            first->pheader = NULL;
            return first->pheader;
        }

        first->pheader= second->pheader;
        if (second->next!=second) {
            first->next = second->next;
            second->next->prev = first;
        } else {
            first->next = first;
        }
        free(second);
        //printf("%p , header : %p\n",first,first->pheader); // Montre que le header NULL prend une valeur au hasard
        return first->pheader;
}

/*! Retrait du dernier élément */
struct Cache_Block_Header *Cache_List_Remove_Last(struct Cache_List *list){
    if(Cache_List_Is_Empty(list)) {
        printf("Pas de remove last sur une liste vide\n");
        return;
    }
        struct Cache_List *first=list;
        struct Cache_List *last;
        if (first->prev!=first) {
            last = list->prev;
        } else {
            first->pheader = NULL;
            return first->pheader;
        }

        if (last->prev!=first) {
            last->prev->next = first;
            first->prev = last->prev;
        } else {
            first->prev = first;
        }
        free(last);

        return first->pheader;
    
}


/*! Retrait d'un élément quelconque */
struct Cache_Block_Header *Cache_List_Remove(struct Cache_List *list,
                                             struct Cache_Block_Header *pbh){
    struct Cache_List *cur=list;
    printf("Je rentre");
    while (cur->next!=list){
    if (cur-> pheader == pbh){
        printf("J'ai trouvé celui à sup, son header: %p \n", cur->pheader);
        if (cur==list) {
            return Cache_List_Remove_First(list);//Si c'est le premier element OK
        }
        //S'il est au milieu OK
        else {
            struct Cache_Block_Header *header= cur->pheader;
            (cur->prev)->next=cur->next;
            (cur->next)->prev=cur->prev;
            free(cur);
            printf("J'ai sup le header remove \n");
            return header;
        }
    }
    cur = cur->next;
    }
	printf("pbh: %p pheader: %p", pbh, cur->pheader);
    if (cur->pheader == pbh){
    //Soit c'est il est seul dans la liste OK
    	if (cur->prev=list && cur==list){
		printf("Cest le seul! \n");
		printf("cur prev: %p, list : %p \n  ", cur->prev, list);
		list->pheader=NULL;
		return NULL;
	    }
	    //Soit c'est le dernier
	    else { 
		printf("C'est le dernier!"); 
		return Cache_List_Remove_Last(list);
	    }
    }
    //Si on ne l'a pas trouvé OK
    return NULL;
}


/*! Remise en l'état de liste vide */
void Cache_List_Clear(struct Cache_List *list) {
    list->next = NULL; // lol
}

/*! Test de liste vide */
bool Cache_List_Is_Empty(struct Cache_List *list) {    
    return (list->next==list && list->prev==list && !list->pheader);
}

/*! Transférer un élément à la fin */
void Cache_List_Move_To_End(struct Cache_List *list,
                            struct Cache_Block_Header *pbh) {
    struct Cache_List *cur=list;
    struct Cache_List *element_to_move = Cache_List_Remove(list,pbh);
    if (element_to_move) {
        while (cur->next) cur = cur->next;
        cur->next = element_to_move;
        element_to_move->prev = cur;
    }                      
}

/*! Transférer un élément  au début */
void Cache_List_Move_To_Begin(struct Cache_List *list,
                              struct Cache_Block_Header *pbh) {
    struct Cache_List *element_to_move = Cache_List_Remove(list,pbh);    
    list->prev = element_to_move;
    element_to_move->next=list;
}



/*! Afficher la cache liste entière */
void Cache_List_Print(struct Cache_List *list) {
    
    if (list->pheader == NULL) { printf("Cette liste est NULL\n"); } else {
    
    struct Cache_List *tmp = list;
    while (tmp->next != list) {
        printf("%p , header : %p\n",tmp,tmp->pheader);
        tmp = tmp->next;
    }
    printf("%p , header : %p\n",tmp,tmp->pheader);
}
}
