#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define PH 5  //PHILOSOPHERS

sem_t forks[PH];

void * philosopher(void *);
void think(int);
void eat(int);

int main(){
	pthread_t ph_threads[PH];
	int ph_n[PH];

	for(int i = 0; i < PH; i++){
		sem_init(&forks[i], 0, 1);
	}
		
	for(int i = 0; i < PH; i++){
		ph_n[i] = i;
		pthread_create(&(ph_threads[i]), NULL, philosopher,(void *)&ph_n[i]);
	}

	for(int i = 0; i < PH; i++){
		pthread_join(ph_threads[i], NULL);
	}
}

void * philosopher(void * num)
{
	while(1){
		int phi=*(int *)num;

		sem_wait(&forks[phi]);
		sem_wait(&forks[(phi + 1) % PH]);

		eat(phi);
		sleep(2);
		printf("\nPhilosopher %d ate\t😋",phi);

		sem_post(&forks[(phi + 1) % PH]);
		sem_post(&forks[phi]);
		
		think(phi);
		sleep(1);
		printf("\nPhilosopher %d hungry\t😐",phi);
	}
}

void eat(int phi){
	printf("\nPhilosopher %d eating\t🍴",phi);
}
void think(int phi){
	printf("\nPhilosopher %d thinking\t🤔",phi);
}
