
#include<string>
#include<fstream>
#include <iostream>      
#include <thread>        
#include <mutex>
#include <pthread.h>         
#include <condition_variable>
using namespace std;


 //critical section control
std::mutex mtx;
//cv used desision which threadh working              
std::condition_variable cv; 
//thread status
bool ready = false;
//working threads id          
int current = 0; 
//default threads Number        
int threadnum = 15;
int linecounter=0;
//output file
ofstream outputfile;
//Data structure for threads
struct intt
{
int id;
int start;
int result;
};
/* function for working is thread */
void *print_num(void *a) {
ifstream file;
struct intt  *num;
num=(struct intt *)a;
  unique_lock<std::mutex> lck(mtx);
  while(num->id != current || !ready){ cv.wait(lck); }
  //critical section of readind and writing operations 
current++;
if(!outputfile.is_open())
outputfile.open("output.txt",std::ios::app);
  string item;
  int i=0;

if(!file.is_open())
file.open("input.txt");

while(!file.eof())
{

getline(file,item);

if(i>=num->start&&i<num->start+linecounter)
{
outputfile<<item<<endl;
i++;
}
else if(i>=num->start+linecounter)
break;
else
i++;

}
outputfile.close();

  num->result=i-num->start;
if(num->result<0)
num->result=0;
  //Notify next threads to check if it is their turn 
  cv.notify_all(); 
}

//Changes ready to true and threads ready for working
void run(){
  std::unique_lock<std::mutex> lck(mtx);
  ready = true;
  cv.notify_all();
}
 
int main (){
int x;
//input file
ifstream file;
cout<<"enter number:";// x thread Number
cin>>x;

float rowcount=0.0;
file.open("input.txt");
string item;
//this section give  input file lenght
while ( std::getline(file, item) )
   ++rowcount;


if(int(rowcount/x)<rowcount/x)
 linecounter=int(rowcount/x)+1;
else
linecounter=int(rowcount/x);


cout<<linecounter;
struct intt *a=new intt[x];
  int threadnum = x;
  pthread_t threads[x];

  //creating thread using pthread library
  for (int id = 0; id < threadnum; id++)
   {a[id].id=id;
    a[id].start=id*linecounter;
    pthread_create(&threads[id],NULL,print_num,(void*)&a[id]);}

  

  run(); // Allows threads to run

 
  for(int id = 0; id < threadnum; id++)
    pthread_join(threads[id],NULL);

//print the thread id and result  
for(int i=0;i<x;i++)
cout<<i+1<<".thread :"<<a[i].result<<endl;
  return 0;
}

