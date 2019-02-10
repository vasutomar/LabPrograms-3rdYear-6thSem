#include <iostream>
#include <unistd.h>
#include <semaphore.h>
#include <sys/mman.h>

#define NumberOfPhil 5

using namespace std;

int eatStatus[5] = {0};

/* Semaphore declaration*/
sem_t *redF1   = (sem_t*) mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
sem_t *redF2   = (sem_t*) mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
sem_t *greenF1 = (sem_t*) mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
sem_t *greenF2 = (sem_t*) mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
sem_t *greenF3 = (sem_t*) mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);

/* Semaphore iniialization*/
void initSemaphores() {
    sem_post(redF1);
    sem_post(redF2);
    sem_post(greenF1);
    sem_post(greenF2);
    sem_post(greenF3);
}

/* Philosopher class */
class Philospher {
    
    private:
        int id;
        int eating_time;
        int thinking_time;
        string PickedUpColor;
    	
    public:
    
    int finished;

    Philospher(int id) {
    	finished = 0;
    	eating_time = 0;
    	thinking_time = 0;
    	PickedUpColor = "red";
        this->id = id;
    }

    void exec() {
        int j = 0;
        while(j<=2) {
            if(!sem_trywait(redF1) && !sem_trywait(redF2)) {
                cout<<"Philospher "<<id<<" picks up red chopstics 1 & 2."<<endl;
                cout<<"Philospher "<<id<<" eating with red chopstics."<<endl;
                j++;
                eating_time++;
                sem_post(redF1);
                sem_post(redF2);
            }
            if(!sem_trywait(greenF1) && !sem_trywait(greenF2)) {
                cout<<"Philospher "<<id<<" picks up green chopstics 1 & 2."<<endl;
                cout<<"Philospher "<<id<<" eating with green chopstics."<<endl;
                j++;
                eating_time++;
                sem_post(greenF1);
                sem_post(greenF2);
            }
            if(!sem_trywait(greenF2) && !sem_trywait(greenF3)) {
                cout<<"Philospher "<<id<<" picks up green chopstics 2 & 3."<<endl;
                cout<<"Philospher "<<id<<" eating with green chopstics."<<endl;
                j++;
                eating_time++;
                sem_post(greenF2);
                sem_post(greenF3);
            }
            if(!sem_trywait(greenF1) && !sem_trywait(greenF3)) {
                cout<<"Philospher "<<id<<" picks up green chopstics 3 & 1."<<endl;
                cout<<"Philospher "<<id<<" eating with green chopstics."<<endl;
                j++;
                eating_time++;
                sem_post(greenF1);
                sem_post(greenF3);
            }
            else {
                cout<<"Philospher "<<id<<" is thinking."<<endl;
                thinking_time++;
            }
        }
        cout<<"Philospher "<<id<<" finished eating. ---------------------------------------------------"<<endl;
        cout<<endl;
    }
};


int main() {

	initSemaphores();

    pid_t pid;
    int i;

    for(i = 0; i<NumberOfPhil; i++) {
        pid = fork();
        
        if (pid < 0){  
            cout << "Failed to fork" << endl;
        }
        else if (pid == 0) {
            Philospher ph(i);
            ph.exec();
            break;
        }
    }
    return 0;
}