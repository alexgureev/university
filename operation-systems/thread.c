#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <errno.h>
#include <math.h>       /* ceil */
// max parent will be SIZE - 1

// #define SIZE 8
// #define N 2

// #define SIZE 4
// #define N 1

// #define SIZE 12
// #define N 3

// at least 1 parent
// #define SIZE 7
// #define N 10

#define SIZE 7
#define N 3

struct elt {
    struct elt *next;
    int value;
};

struct queue {
    struct elt *head;
    struct elt *tail;
};

int *children[SIZE];
int n_parents = 0;
int parent_to_go = 0;
typedef struct queue *q;
struct queue *p_queue;	
time_t timer;
char buffer[26];
struct tm* tm_info;

    
pthread_mutex_t region_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t space_available = PTHREAD_COND_INITIALIZER;
pthread_cond_t data_available = PTHREAD_COND_INITIALIZER;

unsigned int randr(unsigned int min, unsigned int max);
char * getTimestamp();
struct queue * queueCreate(void);
int isParentInQueue(struct queue *q, int value);
void enq(struct queue *q, int value);
int queueEmpty(const struct queue *q);
int deq(struct queue *q);
void queuePrint(struct queue *q);
void queueDestroy(struct queue *q);
void parentEnq(int value);
int isChildInRoom(int id);
int getLastParent();
int getFirstParent();
void printKids();
void *putChildIntoRoom(int id);
void *releaseChildFromRoom(int id);
void *handleEntrance();
void *handleRelease();
int getNumberOfChild();
void *leftChildInRoom(int id);
int isChildReadyToGo(int id);

main()
{
    p_queue = queueCreate();
    
	pthread_t producer_thread;
	pthread_t consumer_thread;
	void *producer();
	void *consumer();

	pthread_create(&consumer_thread, NULL, consumer, NULL);
	pthread_create(&producer_thread, NULL, producer, NULL);
	pthread_join(consumer_thread,NULL);
}

int getLastParent() {
	return p_queue->tail->value;
}

int getFirstParent() {
	return p_queue->head->value;
}

void parentEnq(int value) 
{
	// printf("enq %i\n", value);
	n_parents++;
	enq(p_queue, value);
}

void printKids() {
	int i;
	for(i = 0; i<SIZE; i++) {
		if(children[i]>=1) {
			printf("%i,", i);	
		}
	}
}

int getNumberOfChild() {
	int i, calc = 0;
	for(i = 0; i<SIZE; i++) {
		if(children[i]>=1) {
			calc++;
		}
	}

	return calc;
}

int isChildInRoom(int id) {
	return children[id] >= 1;
}

int isChildReadyToGo(int id) {
	return children[id] == 2;
}

void *putChildIntoRoom(int id) {
	children[id] = 1;
}

void *leftChildInRoom(int id) {
	children[id] = 2;
}

void *releaseChildFromRoom(int id) {
	children[id] = 0;
}

void *producer()
{
	while (1)
	{
		pthread_mutex_lock(&region_mutex);
		if (!queueEmpty(p_queue)) {
			pthread_cond_wait(&space_available, &region_mutex);
		}


		int value = randr(1, SIZE-1);

		// printf("Value %i, check: %i\n", value, isParentInQueue(p_queue, value));
		// queuePrint(p_queue);
		// printf("\n");
		if(!isParentInQueue(p_queue, value)){
			if(isChildReadyToGo(value)) {
				parent_to_go = value;
			} else {
				parentEnq(value);
			}
			
			sleep(1);
			pthread_cond_signal(&data_available);
		}

		pthread_mutex_unlock(&region_mutex);
	}

	pthread_exit(NULL);
}

void *consumer()
{
	while(1) {
		pthread_mutex_lock(&region_mutex);

		if (queueEmpty(p_queue)) {
			pthread_cond_wait(&data_available, &region_mutex);
		}

		handleEntrance();
		handleRelease();
    	
    	pthread_cond_signal(&space_available);
		pthread_mutex_unlock(&region_mutex);
		
	}

	pthread_exit(NULL);
}

void *handleEntrance() 
{
	/**
		12:01:10.353 Родитель №1 привел ребенка. В комнате: ребенок №1, родитель №1.
		12:01:11.412 Родитель №2 привел ребенка. В комнате: дети №1,2, родители №1,2.
		...
		12:01:11.701 Родитель №3 привел ребенка. В комнате: дети №1,2,3, родители №1,3.
		...
		12:01:14.810 Родитель №4 привел ребенка. В комнате: дети №1,2,3,4, родители №3,4.
	*/

	if(!isChildInRoom(getLastParent())) {
		printf("%s Родитель №%i привел ребенка. ", 
			getTimestamp(), 
			getLastParent()
		);

		putChildIntoRoom(getLastParent());
	
		printf("В комнате: дети №");
		printKids();

		printf(" родители №");
		queuePrint(p_queue);

		printf("\n");
	}
}

void *handleRelease() 
{
	/**
		12:01:11.700 Родитель №2 ушел. В комнате: дети №1,2, родитель №1.
		...
		12:01:11.910 Родитель №1 ушел. В комнате: дети №1,2,3, родитель №3.
		12:01:11.815 Родитель №2 забрал ребенка. В комнате: дети №1,3, родитель №3.
		...
		12:01:14.951 Родитель №1 забрал ребенка. В комнате: дети №2,3,4, родители №3,4.
		12:01:15.118 Родитель №4 ушел. В комнате: дети №2,3,4, родитель №3.
	*/
		// printf("%i - %i - %i, %i\n", n_parents, getNumberOfChild(), getNumberOfChild()/N, (n_parents - getNumberOfChild()/N));
	// if(n_parents - getNumberOfChild()/N >= 1) {
	if(isChildReadyToGo(parent_to_go)) {
		
		printf("%s Родитель №%i забрал ребенка. ", 
			getTimestamp(), 
			parent_to_go
		);

		releaseChildFromRoom(parent_to_go);

		printf("В комнате: дети №");
		printKids();

		printf(" родители №");
		queuePrint(p_queue);
		
		printf("\n");

	//12:01:15.118 Родитель №4 ушел. В комнате: дети №2,3,4, родитель №3.
	} 

	if((n_parents - getNumberOfChild()/N) > 1) {
		printf("%s Родитель №%i ушел. ", 
			getTimestamp(), 
			getFirstParent()
		);

		leftChildInRoom(getFirstParent());
		deq(p_queue);
		n_parents--;

		printf("В комнате: дети №");
		printKids();

		printf(" родители №");
		queuePrint(p_queue);
		
		printf("\n");
	}
}

char *getTimestamp()
{
	time(&timer);
    tm_info = localtime(&timer);

    strftime(buffer, 26, "%H:%M:%S", tm_info);
    return buffer;
}

unsigned int randr(unsigned int min, unsigned int max)
{
   double scaled = (double)rand()/RAND_MAX;
   return (max - min +1)*scaled + min;
}

/* queue implementation http://www.cs.yale.edu/homes/aspnes/classes/223/examples/linkedLists/queue.c */

struct queue * queueCreate(void)
{
    struct queue *q;
    q = malloc(sizeof(struct queue));
    q->head = q->tail = 0;
    return q;
}

/* push a new value onto top of Queue */
void enq(struct queue *q, int value)
{
    struct elt *e;
    e = malloc(sizeof(struct elt));
    assert(e);
    e->value = value;
    /* Because I will be the tail, nobody is behind me */
    e->next = 0;
    if(q->head == 0) {
        /* If the queue was empty, I become the head */
        q->head = e;
    } else {
        /* Otherwise I get in line after the old tail */
        q->tail->next = e;
    }
    /* I become the new tail */
    q->tail = e;
}

int queueEmpty(const struct queue *q)
{
    return (q->head == 0);
}

int deq(struct queue *q)
{
    int ret;
    struct elt *e;
    assert(!queueEmpty(q));
    ret = q->head->value;
    /* patch out first element */
    e = q->head;
    q->head = e->next;
    free(e);
    return ret;
}

/* print contents of queue on a single line, head first */
void queuePrint(struct queue *q)
{
    struct elt *e;
    for(e = q->head; e != 0; e = e->next) {
        printf("%d ", e->value);
    }
    // putchar('\n');
}

int isParentInQueue(struct queue *q, int value)
{
    struct elt *e;
    for(e = q->head; e != 0; e = e->next) {
    	if(e->value == value) {
    		return 1;
    	}
    }
    return 0;
}

/* free a queue and all of its elements */
void queueDestroy(struct queue *q)
{
    while(!queueEmpty(q)) {
        deq(q);
    }
    free(q);
}