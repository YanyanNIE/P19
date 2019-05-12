#include <errno.h>
#include <stdio.h>

#include "sem_pv.h"

static int semid = -1;
static struct sembuf op_p = {-1, -1, 0}, //{numéro du sémaphore, valeur, drapeau(osef)}
		     op_v = {-1, 1, 0};

union semun
{
	int val;
	struct semid_ds* buf;
	unsigned short *array;
};

int init_semaphore(void)
{
	int i;
	union semun arg0;


	if(semid != -1)
	{
		fprintf(stderr, "init_semaphore: Sémaphores déjà initialisés");
		return -1;
	}

	if( (semid = semget(IPC_PRIVATE, N_SEM, 0600)) == -1)
	{
		fprintf(stderr, "init_semaphore/semget: Erreur lors de l'appel de semget");
		return -2;
	}

	arg0.val = 0;

	for(i = 0; i < N_SEM; i++)
		if( (semctl(semid, i, SETVAL, arg0)) == -1)
		{
			perror("init_semaphore/semctl: ");
			return -2;
		}

	return 0;
}

int detruire_semaphore(void)
{
	int retour;

	if(semid == -1)
	{
		fprintf(stderr, "detruire_semaphore: Impossible de détruire un sémaphore inexistant");
		return -1;
	}

	//Non demandé
	if((retour = semctl(semid, 0, IPC_RMID, 0)) == -1)
	{
		perror("detruire_semaphore/semctl: ");
		return -2;
	}

	semid = -1;

	return retour;
}

int val_sem(int sem, int val)
{
	int retour;
	union semun arg0;

	if(semid == -1)
	{
		fprintf(stderr, "val_sem: Sémaphore inexistant");
		return -1;
	}

	if(sem < 0 || sem >=N_SEM)
	{
		fprintf(stderr, "val_sem: Numéro de sémaphore inexistant");
		return -2;
	}

	arg0.val = val;

	return semctl(semid, sem, SETVAL, arg0);
}

int P(int numero)
{
	if(semid == -1)
	{
		fprintf(stderr, "V: Sémaphore inexistant");
		return -1;
	}

	if(numero < 0 || numero >=N_SEM)
	{
		fprintf(stderr, "V: Numéro de sémaphore inexistant");
		return -2;
	}

	op_p.sem_num = numero;

	return semop(semid, &op_p, 1);
}

int V(int numero)
{
	if(semid == -1)
	{
		fprintf(stderr, "V: Sémaphore inexistant");
		return -1;
	}

	if(numero < 0 || numero >=N_SEM)
	{
		fprintf(stderr, "V: Numéro de sémaphore inexistant");
		return -2;
	}

	op_v.sem_num = numero;

	return semop(semid, &op_v, 1);
}
