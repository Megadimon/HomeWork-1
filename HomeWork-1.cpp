#include <iostream>
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime> 
#include <string>
#define shift 2
using namespace std;


int main()
{
unsigned int size = 0;
unsigned int bytes = 0;
double *gamma = 0;
int *or = 0;
int *sh = 0;
string txt;


cout << "\t\t********Welcome to the cipher!********\n\n" << endl;

cout << endl << "Please enter the word: ";
cin >> txt;
cout << endl <<"Message text: " << txt << endl;
for ( int i = 0; txt[i] != '\0'; i++ ) size ++; // Узнаём сколько букв в сообщении
cout << endl << "size - " << size;

	cout << endl << "Data size: "; 
	for (int i = 0; i < size; i++ ) bytes +=sizeof(txt[i]);
cout << bytes << " bytes" << endl;

	cout << endl << "Encryption" << endl;
	gamma = (double *)malloc( size*sizeof(double) ); // выделение памяти под гамму
	
	// Печать символов сообщения в десятичной системе счисления
	cout << "Initial numbers: ";
		for ( int i = 0; i < size; i++ ) cout << (int)txt[i] << " ";
	cout << endl;

	// Инициализация гаммы
	cout << "Gamma: ";
	srand(time(NULL));
		for ( int i = 0; i < size; i++ )
		{
			gamma[i] = rand() % 127; 
			cout << gamma[i] << " "; 
		}
	cout << endl;

	//Вычисление "Исключающего или" 
	or = (int *)malloc( size*sizeof(int) );
	cout << "Еxclusive oR: ";
		for ( int i = 0; i < size; i++ ) 
		{
			or[i] = (int)( (int)txt[i] + gamma[i] ) % 127;
			if ( or[i] == 0) or[i] = 127;
			cout << or[i] << " ";
		}
	cout << endl;

	// Циклический сдвиг вправо на shift бит
	sh = (int *)malloc( size*sizeof(int) );
	cout << "Cyclic shift: ";
		for ( int j = 0; j < shift; j++ )
		{
				for ( int i = 0; i < size; i++ ) sh[i] = or[i];
			or[0] = sh[size-1];
				for ( int i = 0; i < size-1; i++ ) or[i+1] = sh[i];
		}
		for (int i = 0; i < size; i++) cout << or[i] << " ";

	// Печать зашифрованного сообщения	
			cout << endl << "The encrypted message: ";
		for (int i = 0; i < size; i++) cout << (char)or[i];
	
	cout << endl << endl << "Decryption" << endl; // Совершаем весь алгоритм в обратную сторону
	
	cout << "Reverse exception: ";
		for ( int j = 0; j < shift; j++ )
		{
				for ( int i = 0; i < size; i++ ) sh[i] = or[i];
			or[size-1] = sh[0];
				for ( int i = 0; i < size-1; i++ ) or[i] = sh[i+1];
		}
		for (int i = 0; i < size; i++) cout << or[i] << " ";
	cout << endl;
	
	cout << "Gamma: ";
		for (int i = 0; i < size; i++) cout << gamma[i] << " ";

	
	cout << endl << "The decrypted numbers: ";
		for ( int i = 0; i < size; i++ ) 
		{
			sh[i] = (int)( or[i] - gamma[i] + 127 ) % 127;
			if ( sh[i] == 0 ) sh[i] = 127;
			cout << sh[i] << " ";
		}
	cout << endl;

	cout << "The decrypted message text: ";
		for ( int i = 0; i < size; i++ ) cout << (char)sh[i];
	cout << endl << endl << "Press any button to exit the program" << endl;
	// Освобождаем память		
	free(gamma);
	free(or);
	free(sh);
	_getch();
	return 0;
}
