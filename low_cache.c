#include <stdio.h>
#include <stdlib.h>

#include "low_cache.h"

struct Cache_Block_Header *Get_Free_Block(struct Cache *pcache){
	for (int num_bloc = 0; num_bloc < pcache->nblocks; ++num_bloc){ 
		if (pcache->headers[num_bloc].flags & VALID == 0)
			return &(pcache->headers[num_bloc]);
	}
	return NULL;
}
