#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "Number.h"

using namespace std;

Number::Number(int b, int type, string num) {
	srand(time(0));
	this->setBit(b);
	this->setType(type);
	if (type == 1) {	//se type è pari ad 1 il numero è binario, altrimenti è in Ca2
		this->setBin(num);
		this->parseBin();
	}
	else {
		this->setCa2(num);
		this->parseCa2();
	}
}

Number::Number(int d) {
	this->setDec(d);
}

Number::Number() {}

Number::~Number() {}

void Number::setBin(string b) { binary = b; }
string Number::getBin() { return binary; }

void Number::setCa2(string c) { ca2 = c; }
string Number::getCa2() { return ca2; }

void Number::setDec(int d) { dec = d; }
int Number::getDec() { return dec; }

void Number::setBit(int b) { bit = b; }
int Number::getBit() { return bit; }

void Number::setType(int t) { type = t; }
int Number::getType() { return type; }


//PARSE PER NUM BINARIO
void Number::parseBin() {
	string aux = this->getBin();
	int size = aux.length();
	int bit = this->getBit();

	if (size > (bit - 1)) {		//troncamento numero
		string tmp = aux.substr(0, bit);
		this->setBin(tmp);
	}
	else {		//aggiunta di 0
		int plus = getBit() - size;
		string tmp("0");
		for (int i = 1; i < plus; i++) tmp += "0";
		aux.insert(0, tmp);
		this->setBin(aux);
	}
}

//PARSE PER NUM IN CA2
void Number::parseCa2() {
	string aux = this->getCa2();
	int size = aux.length();
	int bit = this->getBit();

	if (size > (bit - 1)) {		//dimensione maggiore di n bit: la stringa viene troncata
		string tmp = aux.substr(0, bit);
		this->setCa2(tmp);
	}
	else {		//dimensione minore di n bit: la stringa viene estesa con 0 o 1 a seconda del segno
		int plus = getBit() - size;
		if (aux[0] == '0') {
			string tmp("0");
			for (int i = 1; i < plus; i++) tmp += "0";
			aux.insert(0, tmp);		//inserisci nella pos 0 la stringa tmp
		}
		else {
			string tmp("1");
			for (int i = 1; i < plus; i++) tmp += "1";
			aux.insert(0, tmp);
		}
		this->setCa2(aux);
	}
}

//SEZIONE CONVERSIONI *******************************************************

//CALCOLO CONVERSIONI

//DEC-BIN
string Number::dec_bin(int dec) {
	int resto;
	string r;
	int quoz;
	int div;
	string bin = "";

	//cout << "\n--- PROCEDIMENTO CONVERSIONE DEC-BIN ---" << endl << endl;
	quoz = dec;
	while (quoz > 0) {
		div = quoz;
		resto = quoz % 2;
		quoz /= 2;
		cout << div << " / 2 = " << quoz << " --> R = " << resto << endl;
		r = (char)resto + 48;
		bin.insert(0, r);
	}
	cout << "\nDec: " << dec << " --> Bin: " << bin << endl << endl;
	return bin;
}


//BIN-DEC
int Number::bin_dec(string bin) {
	int bit = this->getBit();
	double exp = 0;
	int dec = 0;
	int aux;
	int cont[bit];
	for (int i = 0; i < bit; i++) cont[i] = 0;

	//cout << "\n--- PROCEDIMENTO CONVERSIONE BIN-DEC ---" << endl << endl;
	for (int i = bit - 1; i >= 0; i--) {
		aux = (bin[i] - 48)*pow(2, exp);
		cout << bin[i] << " * (2^" << exp << ") = " << aux << endl;
		exp++;
		cont[i] = aux;
		dec += aux;
	}
	cout << endl;
	cout << "La somma dei resti e' pari a " << dec << endl;
	//cout << "\nBin: " << bin << " --> Dec: " << dec << endl;

	return dec;
}

//DEC-CA2
string Number::dec_ca2(int dec) {
	string ca2;
	string bin;
	int bit=this->getBit();
	
	cout << "\n--- PROCEDIMENTO CONVERSIONE DEC-CA2 ---" << endl << endl;
	
	
	if(dec<0){
		
		cout << "\t--- 1^ Passaggio ---" << endl;
		cout << "\t--- PROCEDIMENTO CONVERSIONE DEC-BIN DEL VALORE ASSOLUTO ---" << endl << endl;
		bin = this->dec_bin(abs(dec));
		while(bin.length()<bit)		 bin.insert(0,"0");
		this->setBin(bin);
		
		cout << "\t--- 2^ Passaggio ---" << endl << endl;
		ca2 = this->bin_ca2(bin,false);
		
	}else{
		
		ca2=this->dec_bin(dec);
		while(ca2.length()<bit)	 	ca2.insert(0,"0");	
	}
	
	cout << "\nDec: " << dec << " --> Ca2: " << ca2 << endl;
	return ca2;
}

//CA2-DEC
int Number::ca2_dec(string ca2) {
	int dec;
	string bin;

	cout << "\n--- PROCEDIMENTO CONVERSIONE CA2-DEC ---" << endl << endl;
	if(ca2[0] == '1'){
		cout << "\t--- 1^ Passaggio ---" << endl;
		cout << "\t--- PROCEDIMENTO OPERAZIONE UNARIA DI CAMBIAMENTO DEL SEGNO ---" << endl << endl;
		bin = this->ca2_bin(ca2);
		this->setBin(bin);
		cout << "\t--- 2^ Passaggio ---" << endl;
		cout << "\t--- PROCEDIMENTO DI CALCOLO DEL VALORE ASSOLUTO ---" << endl << endl;
		dec = this->bin_dec(bin);
		cout << "\nCa2: " << ca2 << " --> Dec: " << dec*(-1) << endl;
	}else{
		dec = this->bin_dec(ca2);
		cout << "\nCa2: " << ca2 << " --> Dec: " << dec << endl;
	}

	return dec;
}

//BIN-CA2
string Number::bin_ca2(string bin, bool check) {
	string auxca2 = "";
	int riporto;
	int bit = this->getBit();

	if(!check)	cout << "\n--- PROCEDIMENTO OPERAZIONE UNARIA DI CAMBIAMENTO DEL SEGNO ---" << endl << endl;

	//compl. dei bit
	for (int i = 0; i < bit; i++) {
		if ((bin[i] - 48) == 0) {
			auxca2 += '1';
			cout << "\n0 --> 1";
		}
		else {
			auxca2 += '0';
			cout << "\n1 --> 0";
		}
	}
	cout << endl << endl;
	//aggiunta di 1
	bit = this->getBit() - 1;
	string ca2 = auxca2;
	if ((auxca2[bit] - 48) == 0) {
		ca2[bit] += 1;
	}
	else {
		riporto = 1;		//l'ultima cifra è 1 quindi 1+1=0 con riporto 1
		ca2[bit] -= 1;	//diventa 0
		bit--;
		while (riporto == 1) {
			if ((ca2[bit] - 48) == 0) {
				ca2[bit] += 1;	//diventa 1
				riporto = 0;
			}
			else {
				riporto = 1;
				ca2[bit] -= 1;	//diventa 0
				bit--;
			}
		}
	}
	cout << auxca2 << " + 1 = " << ca2 << endl;
	if(!check) cout << "\nn: " << bin << " --> -n: " << ca2 << endl << endl;

	return ca2;
}

//CA2-BIN
string Number::ca2_bin(string ca2) {
	string bin;

	//cout << "\n--- PROCEDIMENTO CONVERSIONE CA2-BIN ---" << endl << endl;
	
	bin = bin_ca2(ca2,true);		
	//cout << "\nCa2: " << ca2 << " --> Bin: " << bin << endl << endl;

	return bin;
}

//CONVERSIONI SENZA COMMENTI

//DEC-BIN
string Number::dec_bin_noTxt(int dec) {
	int resto;
	string r;
	string bin = "";

	while (dec > 0) {
		resto = dec % 2;
		dec /= 2;
		r = (char)resto + 48;
		bin.insert(0, r);
	}
	
	while(bin.length()<this->getBit())	 bin.insert(0,"0");
	return bin;
}


//BIN-DEC
int Number::bin_dec_noTxt(string bin) {
	int bit;
	double exp = 0;
	int dec = 0;
	int aux;

	bit = this->getBit();
	for (int i = bit - 1; i >= 0; i--) {
		aux = (bin[i] - 48)*pow(2, exp);
		exp++;
		dec += aux;
	}
	return dec;
}

//DEC-CA2
string Number::dec_ca2_noTxt(int dec) {
	string ca2;
	string bin;


	if(dec<0){
		bin = this->dec_bin_noTxt(abs(dec));
		this->setBin(bin);
		ca2 = this->bin_ca2_noTxt(bin);
		
	}else{
		ca2=this->dec_bin(dec);
		while(ca2.length()<bit)	 	ca2.insert(0,"0");	
	}
	
	cout << "\nDec: " << dec << " --> Ca2: " << ca2 << endl;
	
	return ca2;
}

//CA2-DEC
int Number::ca2_dec_noTxt(string ca2) {
	int dec;
	string bin;

	if(ca2[0] == '1'){
		bin = this->ca2_bin_noTxt(ca2);
		this->setBin(bin);
		dec = this->bin_dec_noTxt(bin);
		dec*=-1;
	}else	dec = this->bin_dec_noTxt(ca2);

	return dec;
}

//BIN-CA2
string Number::bin_ca2_noTxt(string bin) {
	string auxca2 = "";
	int riporto;
	int bit = this->getBit();

	//compl. dei bit
	for (int i = 0; i < bit; i++) {
		if ((bin[i] - 48) == 0) {
			auxca2 += '1';
		}
		else {
			auxca2 += '0';
		}
	}
	//aggiunta di 1
	bit = this->getBit() - 1;
	string ca2 = auxca2;
	if ((auxca2[bit] - 48) == 0) {
		ca2[bit] += 1;
	}
	else {
		riporto = 1;		//l'ultima cifra è 1 quindi 1+1=0 con riporto 1
		ca2[bit] -= 1;	//diventa 0
		bit--;
		while (riporto == 1) {
			if ((ca2[bit] - 48) == 0) {
				ca2[bit] += 1;	//diventa 1
				riporto = 0;
			}
			else {
				riporto = 1;
				ca2[bit] -= 1;	//diventa 0
				bit--;
			}
		}
	}
	
	return ca2;
}

//CA2-BIN
string Number::ca2_bin_noTxt(string ca2) {
	string bin;

	bin = bin_ca2_noTxt(ca2);
	return bin;
}


//FINE SEZIONE CONVERSIONI ************************************************

//SEZIONE OPERAZIONI *****************************************************

//CALCOLO OPERAZIONI

//funzioni servizio operazioni
string Number::BuildStr() {
	int sizeRiporto = this->getBit();
	string riporto("*");
	for (int i = 1; i < sizeRiporto; i++) riporto += "*";
	return riporto;
}

void Number::BuildRiporto(string &r, int &index) {
	r[index - 1] = '1';
}

void Number::FixPrintOutput(string op1, string op2, string rip, string sum) {
	cout << "'RIPORTO': " << "\t" << rip << "\n"
		<< "'OPERANDO 1': " << "\t" << op1 << "  +\n"
		<< "'OPERANDO 2': " << "\t" << op2 << "  =\n"
		<< "'RISULTATO: " << "\t" << sum << "\n\n";
}

void Number::PrintSub(string op1, string op2, string res) {
	cout << "Ricapitolando:\t" << op1 << " - " << op2 << " = " << res << endl << endl;
}

string Number::Complemento() {
	string s = this->getCa2();
	int size = s.length();
	for (int i = 0; i < size; i++) {
		if (s[i] == '1') s[i] = '0';
		else s[i] = '1';
	}
	return s;
}

//overflow

bool Number::isOverflowAdd(Number *n1, Number *n2) {
	char a = n1->getCa2()[0];
	char b = n2->getCa2()[0];
	int x = a - '0';
	int y = b - '0';
	if (x ^ y == 1) return false; //i due operandi sono discordi: non c'è overflow
	char c = this->getCa2()[0];
	int z = c - '0';
	if (z ^ x == 1) return true; //il risultato è discorde con gli operandi: c'è overflow
	else return false;
}

bool Number::isOverflowSub(Number *n1, Number *n2) {
	char a = n1->getCa2()[0];
	char b = n2->getCa2()[0];
	int x = a - '0';
	int y = b - '0';
	if (x ^ y == 0) return false; //i due operandi sono concordi: non c'è overflow
	char c = this->getCa2()[0];
	int z = c - '0';
	if (z ^ x == 1) return true; //il risultato è discorde con il primo operando: c'è overflow
	else return false;
}

//SOMMA
Number& Number::add(Number &n) {
	string riporto = n.BuildStr();
	string result = n.BuildStr();
	int count = n.getBit() - 1;
	while (count >= 0) {
		//sommo le cifre dei due operandi e salvo l'eventuale riporto
		char a = n.getCa2()[count];
		char b = this->getCa2()[count];
		int x = a - '0';
		int y = b - '0';
		int s = x ^ y;
		if (count > 0 && x == 1 && y == 1) n.BuildRiporto(riporto, count);

		//controllo se nella stessa colonna è presente un bit di riporto
		char c = riporto[count];
		bool flag = false;
		if (c != '*') flag = true;
		if (flag) {
			int z = c - '0';
			int tmp = s;
			s = tmp ^ z;
			if (count > 0 && tmp == 1 && z == 1) n.BuildRiporto(riporto, count);
		}

		char  d = s + '0';

		result[count] = d; //inserisco s(d) nel risultato

		count--;
	}

	Number* sum = new Number(n.getBit(), 2, result);
	return *sum;
}

Number& operator + (Number& n1, Number& n2) {
	string riporto = n1.BuildStr();
	string result = n1.BuildStr();
	int count = n1.getBit() - 1;
	while (count >= 0) {
		//sommo le cifre dei due operandi e salvo l'eventuale riporto
		char a = n1.getCa2()[count];
		char b = n2.getCa2()[count];
		int x = a - '0';
		int y = b - '0';
		int s = x ^ y;
		if (count > 0 && x == 1 && y == 1) n1.BuildRiporto(riporto, count);

		//controllo se nella stessa colonna è presente un bit di riporto
		char c = riporto[count];
		bool flag = false;
		if (c != '*') flag = true;
		if (flag) {
			int z = c - '0';
			int tmp = s;
			s = tmp ^ z;
			if (count > 0 && tmp == 1 && z == 1) n1.BuildRiporto(riporto, count);
		}

		char  d = s + '0';

		result[count] = d; //inserisco s(d) nel risultato

		count--;
	}

	n2.FixPrintOutput(n1.getCa2(), n2.getCa2(), riporto, result);
	Number* sum = new Number(n1.getBit(), 2, result);
	return *sum;
}


//SOTTRAZIONE

Number& Number::sub(Number &n) {
	int bit = n.getBit();
	string one("1");
	for (int i = 1; i < bit; i++) one += "1";

	Number* tmp = new Number(bit, 2, one);

	Number first = this->add(*tmp);
	string s = first.Complemento();
	first.setCa2(s);

	Number sum = n.add(first);

	Number* result = new Number(n.getBit(), 2, sum.getCa2());

	return *result;
}

Number& operator - (Number& n1, Number& n2) {
	int bit = n1.getBit();
	string one("1");
	for (int i = 1; i < bit; i++) one += "1";

	Number sottraendo = Number(bit, 2, one);

	cout << "Si svolge il punto (1) dell'operazione:\n\n";
	string sot=n2.bin_ca2(n2.getCa2(), false);
	sottraendo.setCa2(sot);
	sottraendo.setType(2);

	cout << "Viene svolto, infine, il punto (2)\n\n";
	Number sum = n1 + sottraendo;
	
	Number* result = new Number(n1.getBit(), 2, sum.getCa2());

	n1.PrintSub(n1.getCa2(), n2.getCa2(), result->getCa2());

	return *result;
}

//ESERCITAZIONE

string Number::buildOp(int b) {
	string aux("1");
	for (int i = 1; i < b; i++) aux += "1";
	for (int i = 0; i < b; i++) {
		int cifra = rand() % 2;
		char a = cifra + '0';
		aux[i] = a;
	}
	return aux;
}

int Number::buildOpDec(int bit,int type){
	int dec;
	int pot=pow(2.0,bit);
	if(type==1)		//dec. bin.
		dec=rand()%pot;
	else		//dec in ca2 (neg e pos)
		dec=(rand()%pot)-bit/2;	
	
	return dec;
}

//FINE SEZIONE OPERAZIONI *******************************************************
