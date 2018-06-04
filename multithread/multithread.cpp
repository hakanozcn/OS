#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include <pthread.h>
using namespace std;
string filename="input.txt";// text file
int ct;// her bir thread islem yapacağı counter
// struct 

struct threadst {
    int start;//Baslangıc noktası
    int sonuc;//birlenlerin veri donusunu saglamak icin kullanılan değisken
};
// thread'lere gondereceğimiz fonksiyon
void *threadfunction(void *threadstruct)

{

struct threadst *data;
data=(struct threadst *) threadstruct;
// okuma işleminin yapılacagı obje
 ifstream file;
if(!file.is_open())
    {
    	file.open(filename.c_str());
	}
    if(file.fail())
	{
		cerr<<"Error msg";
		
	}

	int counter=0;
	string item;	
//yazma işlemi icin olustururmus ofstream obje
	ofstream wfile;
	//ss ile int degeri string degerine donusturuyoruz bunun yerıne char(data->start) kullanabilirsiniz
	stringstream *ss;
	ss=new stringstream();
	ss->operator<<(data->start);
//--------------------------------------------------------------------------------------------
	string asd=ss->str()+".txt";
	wfile.open(asd.c_str());
    
//okuma ve yazma işlemi	
	while(!file.eof())
	{ 
	
	std::getline(file,item);
	if(counter>=data->start and counter<data->start+ ct)
	   {
	   
	
	wfile<<item<<endl;
	}
	else if(counter>=data->start+ct)
	{
		break;
	}
	 
	 
	counter++;
}

		 
	delete ss;
	wfile.close();	 
		 
	data->sonuc=int(counter-data->start);

	  
	
	
	
file.close();
pthread_exit(NULL);
}



int main()
{

int n;

float counter=0;
string item;
ifstream file;
	
cout<<"Enter thread count:";
cin>>n;

pthread_t threads[n];
struct threadst *Threadst=new  threadst[n];

	
file.open(filename.c_str());
// text dosyasının line sayısını hesaplamak icin
while(!file.eof())
{
std::getline(file,item);
counter++;

}
file.close();
//her thread kac line okuyacağını tutan degisken
double x=counter/n;
cout<<counter<<endl;
if(x>int(x))
ct=int(x)+1;
else
ct=int(x);

//thread olustururdugu bolum
for(int i=0; i<n;i++)
{
Threadst[i].start=i*ct;
pthread_create(&threads[i], NULL, threadfunction, (void *)&Threadst[i]);
pthread_join(threads[i],NULL);


}

for(int i=0; i<n;i++)
cout<<i+1<<".thread: "<<Threadst[i].sonuc<<endl;

	pthread_exit(NULL);
	
}
