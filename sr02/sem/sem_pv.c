# include "semaph.h"

/*********** Rappel ************************************************
--- Creation shmid ----------------------------
int semget (key_t key, int nsems, int semflg );
        
        ex: semid = semget(IPC_PRIVATE, N_SEM, 0600);

--- Controle indiquée par cmd -----------------
int semctl (int semid, int semnum, int cmd, union semun arg);
    SETVAL- Placer la valeur arg.val dans le champ semval 
    semun - voir <man semctl>

        ex: semctl(semid, semnum, SETVAL, arg)

--- Operation P ou V sur semid --------------
int semop(int semid, struct sembuf *sops, size_t nsops);
    sembuf - sops = {sem_num, sem_op, sem_flag}
        
        ex.semop(semid, &sops_p, 1)

***************************************************************/

static int semid = -1;
static struct sembuf 
    sops_p = {-1, -1, 0},
	sops_v = {-1, 1, 0};

union semun
{
	int val;
};


int init_semaphore(){
    int i;
	union semun arg0;

	if(semid != -1)
	{
		fprintf(stderr, "init_semaphore: Semaphores deja initialises\n");
		return -1;
	}

	if( (semid = semget(IPC_PRIVATE, N_SEM, 0600)) == -1)
	{
		fprintf(stderr, "init_semaphore/semget: Echec %d\n", errno);
		return -2;
	}

	arg0.val = 0;

	for(i = 0; i < N_SEM; i++)
		if( (semctl(semid, i, SETVAL, arg0)) == -1)
		{
            fprintf(stderr, "init_semaphore/semctl: Echec\n");
			return -2;
		}

	return 0;
}

int detruire_semaphore(){
    int i;
    int retour;

	if(semid == -1)
	{
		fprintf(stderr, "detruire_semaphore: semaphore inexistant\n");
		return -1;
	}

    retour = semctl(semid, 0, IPC_RMID, 0);
	semid = -1;

	return retour;
}

int val_sem(int sem, int val){
	union semun arg0;

	if(semid == -1)
	{
		fprintf(stderr, "val_sem: Semaphore inexistant\n");
		return -1;
	}

	if(sem < 0 || sem >=N_SEM){
		fprintf(stderr, "val_sem: Num de semaphore inexistant\n");
		return -2;
	}

	arg0.val = val;

	return semctl(semid, sem, SETVAL, arg0);
}

int P(int sem){
    if(semid == -1)
	{
		fprintf(stderr, "P: Sémaphore inexistant\n");
		return -1;
	}

	if(sem < 0 || sem >=N_SEM)
	{
		fprintf(stderr, "P: Numéro de sémaphore inexistant\n");
		return -2;
	}
    
	sops_p.sem_num = sem;

	return semop(semid, &sops_p, 1);

}

int V(int sem){
    if(semid == -1)
	{
		fprintf(stderr, "V: Semaphore inexistant\n");
		return -1;
	}

	if(sem < 0 || sem >=N_SEM)
	{
		fprintf(stderr, "V: Num de semaphore inexistant\n");
		return -2;
	}

	sops_v.sem_num = sem;

    return semop(semid, &sops_v, 1);
}

// gcc -c sem_pv.c