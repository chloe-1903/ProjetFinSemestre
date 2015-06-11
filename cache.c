#include <stdlib.h>
struct Cache *cache;



/**
*initialise les données (headers )de la cache.
**/
struct Cache_Block_Header* create_Blocks(struct Cache* pcache){
	struct Cache_Block_Header* headerblocks =
	(struct Cache_Block_Header*)malloc( sizeof(struct Cache_Block_Header) * pcache->nblocks );
	if(!headerblocks) return NULL;
	for(int i = 0; i < pcache->nblocks; i++){
		headerblocks[i].ibcache = i;
		headerblocks[i].data = (char*)malloc( pcache->recordsz * pcache->nrecords );
		headerblocks[i].ibfile = -1;
	}
	return headerblocks;
}

/**
*crée une nouvelle cache 
**/
struct Cache *Cache_Create(const char *fic, unsigned nblocks, unsigned nrecords,size_t recordsz, unsigned nderef){
	struct Cache *cache =malloc(sizeof(struct Cache));
//Ouvre le fichier FIC - et le crée si ça n'existe pas encore.
	if( (file = fopen(fic, "r+b")) == NULL)
	file = fopen(fic, "w+b");
	FILE *file;
	cache ->fp=file;
	cache->file= fic;
	cache->nblocks= nblocks;
	cache->nrecords=nrecords;
	cache->blocksz=n*recordsz;
	cache->ndref= nderef;
	cache->instrument.n_reads = 0;
    cache->instrument.n_writes = 0; 
	cache->instrument.n_hits = 0;
	cache->pstrategy = Strategy_Create(cache);
	cache->pfree = Get_Free_Block(cache); //1er bloc?
	cache->headers=create_block(cache);
	return cache;
}
/**
*Synchronise le contenu du cache avec celui du fichier
*vérifie si les blocks de cache sont modifié ,si c'est le cas cherche l'endroit correspondant dans le disque(fichier) pour faire la copie
*et remet a zero le flag 
**/
Cache_Error Cache_Sync(struct Cache *pcache){
	for (int i =0; i<pcache->nblocks; i++){
		if ((pcache->headers[i].flags & MODIF) > 0){
			fseek(char *fic,DADDR(pcache, ibfile),SEEK_SET);
			fwrite(block->data, pcache->nblocks,pcache->nrecords,fic);
		}
		pcache->headers[i].flags &= ~MODIF;
	}
	return CACHE_OK;
}
/**
*Détruit le cache pointé par pcache : synchronise le cache et le fichier grâce à Cache_Sync() ,
*ferme le fichier et détruit toutes les structures de données du cache.
**/
Cache_Error Cache_Close(struct Cache *pcache){

	Cache_sync(pcache);
//fermer ce qu'il faut fermer 
	fclose(pcache->fp);//ferme le fichier
	Strategy_Close(pcache->pstrategy);
//free tout les struct
	free(pcache);
	free(pcache->headers);
	pcache=pcache->headers=NULL;
	return CACHE_OK;
}

/**
*Invalide le cache, c’est-à-dire met à 0 le bit V de tous les blocs. C’est donc comme si
*le cache était vide : aucun bloc ne contient plus d’information utile.
**/
Cache_Error Cache_Invalidate(struct Cache *pcache){
	for(int i=0; i<pcache->nblocks; i++){
		pcache->headers[i].flags &= ~VALID;
	}

	pcache->pfree =Get_Free_Block(cache);
	Strategy_Invalidate(pcache);
	return CACHE_OK;
}


Cache_Error Cache_Read(struct Cache *pcache, int irfile, const void *precord){
	
}

Cache_Error Cache_Write(struct Cache *pcache, int irfile, const void *precord){
	
}
/**
*Retourne une copie de la structure d’instrumentation du cache pointé par pcache .
* tous les compteurs de la structure courante sont remis à 0 par cette fonction.
**/
struct Cache_Instrument *Cache_Get_Instrument(struct Cache *pcache){
	//Copier champ INSTRUMENT de pcache
	struct Cache_Instrument* copy = (struct Cache_Instrument*)malloc( sizeof(struct Cache_Instrument) );
	memcpy( copy, &pcache->instrument, sizeof(struct Cache_Instrument) );
	//Met tous à zero
	pcache->instrument.n_reads = 0;
    pcache->instrument.n_writes = 0; 
	pcache->instrument.n_hits = 0;
return copy;
}


