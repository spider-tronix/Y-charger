#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main(){
	double f=200,T,A=20;
	//cout<<"Enter the frequency:";
	//cin>>f;
	T=1/f;
	T/=4;
	ofstream outfile;
	outfile.open("Modified_sine_wave.txt");
	outfile<<"REPEAT FOREVER"<<endl;
	outfile<<0<<" "<<0<<endl;
	outfile<<T/8<<" "<<0<<endl;
	cout<<T/8;
	outfile<<(T/8)<<" "<<A<<endl;
	outfile<<(T*(3.0/8))<<" "<<A<<endl;
	outfile<<(T*(3.0/8))<<" "<<0<<endl;
	outfile<<(T*(5.0/8))<<" "<<0<<endl;
	outfile<<(T*(5.0/8))<<" "<<-A<<endl;
	outfile<<(T*(7.0/8))<<" "<<-A<<endl;
	outfile<<(T*(7.0/8))<<" "<<0<<endl;
	outfile<<T<<" "<<0<<endl;
	outfile<<"ENDREPEAT"<<endl;
	outfile.close();
}
