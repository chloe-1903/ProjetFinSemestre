#include <stdio.h>
#include <stdlib.h>


#include "low_cache.h"

struct Cache_Block_Header *Get_Free_Block(struct Cache *pcache){
    struct Cache_Block_Header *freebloc = NULL;
	for (int num_bloc = 0; num_bloc < pcache->nblocks; ++num_bloc){ 
		if ((pcache->headers[num_bloc].flags & VALID) == 0) {
            freebloc = &(pcache->headers[num_bloc]);
            Init_Free_Bloc_Flags(freebloc);
			break;
        }
	}
	return freebloc;
}


void Init_Free_Bloc_Flags(struct Cache_Block_Header *header) {
    header->flags |= VALID;
    header->flags &= MODIF;
}
