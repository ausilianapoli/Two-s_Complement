#include <string>
#include <cstring>
#include <string.h>
using namespace std;

class Number {
private:
	string binary;		//num Binario
	string ca2;		//num Compl. a 2
	int dec;		//num Decimale
	int bit;		//num Bit
	int type;		//tipo: 1->binario, 2->Ca2

	//funzioni serivizio operazioni
	string BuildStr();
	void BuildRiporto(string &r, int &index);
	void FixPrintOutput(string op1, string op2, string rip, string sum);
	void PrintSub(string op1, string op2, string res);
	string Complemento();

public:
	Number(int, int, string);	//il primo int corrisponde ai bit, il secondo per capire se è in binario (valore 1) o in Ca2 (valore 2). String è il numero vero e proprio.
	Number(int);	//costruttore solo per numero decimale
	Number();
	~Number();

	void setBin(string);
	string getBin();

	void setCa2(string);
	string getCa2();

	void setDec(int);
	int getDec();

	void setBit(int);
	int getBit();

	void setType(int);
	int getType();

	//funzioni di controllo numero inserito dall'utente
	void parseBin(); 	//verifica se il numero di bit inserito e' corretto
	void parseCa2();

	//funzioni di conversione
	string dec_bin(int);
	int bin_dec(string);
	string dec_ca2(int);
	int ca2_dec(string);
	string bin_ca2(string,bool);	
	string ca2_bin(string);	
	//senza commenti
	string dec_bin_noTxt(int);
	int bin_dec_noTxt(string);
	string dec_ca2_noTxt(int);	
	int ca2_dec_noTxt(string);
	string bin_ca2_noTxt(string);
	string ca2_bin_noTxt(string);

	//controllo overflow
	bool isOverflowAdd(Number *n1, Number *n2);
	bool isOverflowSub(Number *n1, Number *n2);

	//esercitazioni operazioni
	string buildOp(int);
	int buildOpDec(int,int);

	//operazioni (solo risultato)
	Number& add(Number &n);
	Number& sub(Number &n);

	//operazioni step by step
	friend Number& operator + (Number & n1, Number & n2);
	friend Number& operator - (Number & n1, Number & n2);

};
