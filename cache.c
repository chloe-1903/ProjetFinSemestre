#include <stdlib.h>
struct Cache *cache;

struct Cache *Cache_Create(const char *fic, unsigned nblocks, unsigned nrecords,size_t recordsz, unsigned nderef){
	cache =malloc(sizeof(struct Cache));
	FILE *file;
	if( (file = fopen(fic, "r+b")) == NULL)
	file = fopen(fic, "w+b");
	cache ->fp=file;
	cache->file= fic;
	cache->nblocks= nblocks;
	cache->nrecords=nrecords;
	cache->blocksz=n*recordsz;
	cache->ndref= nderef;
	cache->instrument.n_reads = 0;
    cache->instrument.n_writes = 0; 
	cache->instrument.n_hits = 0;
	pstrategy = Strategy_Create(*cache);
	pfree =Get_Free_Block(*cache);
	
}

int Cache_Sync(struct Cache *pcache){
	for (int i =0; i<pcache->nblocks; i++){
		if ((pcache->headers[i].flags & MODIF) > 0){
			fseek(char *fic,DADDR(pcache, ibfile),SEEK_SET);
			fwrite(block->data, pcache->nblocks,pcache->nrecords,fic);
		}
		pcache->headers[i].flags &= ~MODIF;
	}

}
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


