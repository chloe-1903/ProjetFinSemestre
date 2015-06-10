#include <stdlib.h>
struct Cache *cache;

struct Cache *Cache_Create(const char *fic, unsigned nblocks, unsigned nrecords,size_t recordsz, unsigned nderef){
	cache->file= fic;
	cache->nblocks= nblocks;
	cache->nrecords=nrecords;	
	cache->ndref= nderef;
	cache->instrument.n_reads = 0;
    cache->instrument.n_writes = 0; 
	cache->instrument.n_hits = 0;
	//pstrategy = Strategy_Create( __paramètres__ );
	//pfree =Get_Free_Block(__paramètre__);
	
}

/*int Cache_Sync(struct Cache *pcache){
	for (int i =0; i<pcache->nblocks; i++){
		if ((pcache->headers[num_bloc].flags & MODIF) > 0){
		}
		fseek(fic , , );
	}

}*/
int Cache_Close(struct Cache *pcache){
	Cache_sync(pcache);
	close(pcache->fp);
	free(pcache);

}

int Cache_Invalidate(struct Cache *pcache){

}

int Cache_Read(struct Cache *pcache, int irfile, const void *precord){
	
}

int Cache_Write(struct Cache *pcache, int irfile, const void *precord){
	
}

struct Cache_Instrument *Cache_Get_Instrument(struct Cache *pcache){
	
}


