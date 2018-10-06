#include <iostream>
#include "Number.cpp"
using namespace std;

bool isBinary(string op) {
	int size = op.length();
	for (int i = 0; i < size; i++) {
		if (op[i] != '0' && op[i] != '1') return false;
	}
	return true;
}

bool outOfRange(string op){
	int size = op.length();
	int count=0;
	if(op[0]== '1'){
		if(size==1) return true;
		for (int i = 1; i < size; i++) {
			if (op[i] == '0') count++;
			if(count == (size-1)) return true;
		}
	}
	return false;
}

void print_menu(){
	cout << "\n\t\t----- MENU' -----" << endl;
	cout << "\nScegli come vuoi procedere:" << endl;
	cout << "1) Convertire un numero;" << endl;
	cout << "2) Eseguire un'operazione;" << endl;
	cout << "3) Esercitarsi con conversioni o operazioni;" << endl;
	cout << "4) Per chiudere il programma." << endl;
	cout << "Inserisci il numero corrispondente alla tua scelta --> ";
}

void print_conversione(){
	cout << "\nQuale conversione vuoi effettuare?" << endl;
	cout << "1) Decimale (intero) - Compl. a 2 (binario intero);" << endl;
	cout << "2) Compl. a 2 (binario intero) - Decimale (intero);" << endl;
	cout << "\n\t[Inserisci -1 per tornare indietro]\n" << endl;
	cout << "Conversione n. ";
}

void print_operazioni(){
	cout<<"\nQuale tipo di operazione vuoi effettuare?"<<endl;
	cout<<"1) Operazione di cambiamento del segno"<<endl;
	cout<<"2) Operazione aritmetica di somma/sottrazione in Ca2"<<endl;
	cout << "\n\t[Inserisci -1 per tornare indietro]\n" << endl;
	cout<<"Inserisci il numero corrispondente alla tua scelta --> ";
}


// ----------------  CONVERSIONI  ----------------

void conversioni(int conv){
	Number* newnum;
	Number* opConv;
	bool check;
	int dec, bit;
	string bin,ca2;
	
	switch (conv) {
		
		case 1: //DEC-CA2
			cout << "\nConversione Decimale (intero) - Compl a 2 (binario intero)" << endl << endl;
			
			//INSERIMENTO BIT
			do {
				check = false;

				cout<<"A quanti bit vuoi effettuare la conversione?\nInserire il numero di bit (4, 8 o 16 bit): ";
				cin >> bit;
				if (bit != 4 && bit != 8 && bit != 16) {
					cout << "\nERRORE! Il numero di bit non rientra nel range consentito, inserisci un valore corretto." << endl << endl << endl;
					check = true;
				}
			} while (check);
			
			//INSERIMENTO NUMERO
			do {
				check = false;
				cout << "Numero Decimale: ";
				cin >> dec;
				if (dec < ((pow(2.0,bit)/2)*(-1)) || dec > ((pow(2.0,bit)/2)-1)) {
					cout << "\nNumero errato o probabilmente non idoneo al range consentito. Reinseriscilo." << endl << endl;
					cout<< "Range: da "<<((pow(2.0,bit)/2)*(-1)) <<" a +"<< ((pow(2.0,bit)/2)-1) <<endl;
					check = true;
				}
			} while (check);
			
			newnum = new Number(dec);
			newnum->setBit(bit);
			ca2 = newnum->dec_ca2(dec);
			newnum->setCa2(ca2);
							
			break;

		case 2: //CA2-DEC
			cout << "\nConversione Compl a 2 (binario intero) - Decimale (intero)." << endl << endl;
			do {
				check = false;
				cout << "Numero Compl. a 2: ";
				cin >> ca2;
				if (!isBinary(ca2)) {
					cout << "\nNumero errato. Reinseriscilo." << endl << endl;
					check = true;
				}
			} while (check);

			newnum = new Number(ca2.length(), 2, ca2);
			cout << endl;
			dec = newnum->ca2_dec(ca2);
			newnum->setDec(dec);

			break;
			
		case -1:
			return;
			
		default:
			cout << "ERRORE!" << endl << endl;
	}
	return;
}

// ----------------  OPERAZIONI  ----------------

void operaz_unarie(){
	bool check;
	string bin;

	do {
		check = false;
		cout << "Inserisci un intero binario: ";
		cin >> bin;
		if (!isBinary(bin)) {
			cout << "\nNumero errato. Reinseriscilo." << endl << endl;
			check = true;
		}
		if(outOfRange(bin)){
			cout << "\nNumero errato. Reinseriscilo." << endl;
			cout<<"NOTA: Si tratta dell'estremo inferiore dell'intervallo di rappresentazione: \n"
				<<"il risultato di questa operazione non rappresenta il suo opposto (che non e' \n" 
				<<"rappresentabile perche' cade al di fuori dell'intervallo di rappresentazione) \n"
				<<"bensi' lo stesso numero di partenza. "<<endl<<endl;
			check = true;
		}
	} while (check);

	Number* newnum = new Number(bin.length(), 1, bin);
	cout << endl;
	string ca2 = newnum->bin_ca2(bin,false);
	newnum->setCa2(ca2);
}


void operazioni(){
	bool check;
	int operation, bit;
	string s1,s2;
	
	//INSERIMENTO BIT
	do {
		check = false;
		cout << "\nInserire il numero di bit (4, 8 o 16 bit) degli operandi.\n";
		cout << "\n\t[Inserisci -1 per tornare indietro]\n" << endl;
		cout << "Bit --> ";
		cin >> bit;
		if (bit != 4 && bit != 8 && bit != 16 && bit!=-1) {
			cout << "\nERRORE! Il numero di bit non rientra nel range consentito, inserisci un valore corretto." << endl << endl << endl;
			check = true;
		}
	} while (check);

	cout << endl << endl;

	//INSERIMENTO OPERANDI
	if(bit == -1){ 		return;		}
	
	do {
		backOP:
		check = false;

		cout << "\nInserire i due operandi binari interi.\n(NOTA: Se il numero ha dimensione maggiore di " << bit << " bit l'operando verra' troncato)." << endl;
		cout << "Operando 1: ";
		cin >> s1;
		cout << "Operando 2: ";
		cin >> s2;

		if (!isBinary(s1) || !isBinary(s2)) {
			cout << "\nERRORE! Uno dei due operandi non e' stato inserito in codice binario, reinseriscili." << endl << endl;
			check = true;
		}
	} while (check);


	//CREAZIONE OPERANDI
	Number* op1 = new Number(bit, 2, s1);
	Number* op2 = new Number(bit, 2, s2);

	cout << "\nOP1: " << op1->getCa2();
	cout << "\nOP2: " << op2->getCa2() << endl;

	//SCELTA OPERAZIONE
	do {
		check = false;
		cout << "\nQuale operazione vuoi eseguire? (Inserisci il numero corrispondente)\n";
		cout << "1) Somma" << endl;
		cout << "2) Sottrazione" << endl;
		cout << "\n\t[Inserisci -1 per reinserire gli operandi]\n" << endl;
		cout << "Operazione: ";
		cin >> operation;

		if (operation != 1 && operation != 2 && operation != -1) {
			cout << "\nScelta errata! Reinseriscila." << endl << endl;
			check = true;
		}else 
			if(operation == -1) goto backOP; 
			else
				if (operation == 1) {
						cout << "\nL'operazione di somma viene svolta secondo le regole della somma tra numeri "
							<< "binari.\nSe i due operandi sono discordi non c'e' possibilità di overflow; "
							<< "\nse invece sono concordi c'e' possibilita' di overflow: \nse il risultato "
							<< "ha segno discorde dagli operandi c'e' stato overflow.\n\n";
						Number result = *op1 + *op2;
						bool overflow = result.isOverflowAdd(op1, op2);
						if (overflow) cout << "Overflow presente: il risultato ha segno discorde con gli operandi concordi" << endl;
						else cout << "Overflow assente" << endl;
				}else if (operation == 2) {
						cout << "\nL'operazione di sottrazione viene svolta in piu' passaggi:\n"
							<< "1) complemento a due del sottraendo;\n"
							<< "2) il risultato ottenuto al punto (1) viene sommato al minuendo.\n"
							<< "Si e' ottenuto cosi' il risultato della sottrazione.\n"
							<< "Per quanto riguarda l'overflow, se i due operandi iniziali sono concordi "
							<< "non c'e' possibilita' di overflow;\nse invece sono discordi puo' esserci trabocco:"
							<< "\nse il risultato ha segno discorde dal primo operando c'e' overflow" << endl << endl;
			
						Number result = *op1 - *op2;
						bool overflow = result.isOverflowSub(op1, op2);
						if (overflow) cout << "Overflow presente: il risultato ha segno discorde con il primo operando" << endl;
						else cout << "Overflow assente" << endl;
				}
	} while (check);
}

// ----------------  ESERCITAZIONI CONVERSIONI ----------------

int eserc_conv(){
	Number* newnum;
	Number* opConv;
	bool check;
	int conv, dec, bit;
	string bin,ca2, answer;
	
	do {
		check = false;
		cout << "\nQuale conversione vuoi effettuare per esercitarti?" << endl;
		cout << "1) Decimale (intero) - Compl. a 2 (binario intero);" << endl;
		cout << "2) Compl. a 2 (binario intero) - Decimale (intero);" << endl;
		cout << "\n\t[Inserisci -1 per tornare indietro]\n" << endl;
		cout << "Conversione n. ";
		cin >> conv;
		if (conv < -1 || conv==0 || conv > 6) {
			cout << "\nERRORE! Il numero inserito non corrisponde a nessuna scelta." << endl << endl;
			check = true;
		}
	} while (check);
	
	if(conv==-1)	return 1;
	
	//scelta bit
	do {
		check = false;
		cout << "\nInserire il numero di bit (4, 8 o 16 bit) che si vuole usare nella conversione: ";
		cin >> bit;
		if (bit != 4 && bit != 8 && bit != 16) {
			cout << "\nERRORE! Il numero di bit non rientra nel range consentito, inserisci un valore corretto." << endl << endl << endl;
			check = true;
		}
	} while (check);
	
	//esercit. conversione
	switch(conv){
		
		//DEC - CA2
		case 1:
			cout << "\nEs. Conversione Decimale (intero) - Complemento a 2 (binario  intero)" << endl << endl;
				opConv=new Number();
				dec=opConv->buildOpDec(bit,2);
				opConv->setDec(dec);
				opConv->setBit(bit);
				
				cout<<"Inserire la risposta:"<<endl;
				cout<<"Dec: "<<dec<<" --> Ca2: ";
				cin>>answer;
				
				if(answer==opConv->dec_ca2_noTxt(dec))	cout<<"\nRisposta corretta. Esercitazione completata con successo!"<<endl<<endl;
				else{
					cout<<"\nRisultato errato! Ecco il procedimento corretto:"<<endl<<endl;
					answer=opConv->dec_ca2(dec);
				}
			break;
		
		//CA2 - DEC
		case 2:
			cout << "\nEs. Conversione Complemento a 2 (binario intero) - Decimale (intero)" << endl << endl;
				opConv=new Number();
				ca2=opConv->buildOp(bit);
				opConv->setCa2(ca2);
				opConv->setBit(bit);
				opConv->setType(2);
				
				cout<<"Inserire la risposta:"<<endl;
				cout<<"Ca2: "<<ca2<<" --> Dec: ";
				cin>>dec;
				
				if(dec==opConv->ca2_dec_noTxt(ca2))	cout<<"\nRisposta corretta. Esercitazione completata con successo!"<<endl<<endl;
				else{
					cout<<"\nRisultato errato! Ecco il procedimento corretto:"<<endl<<endl;
					dec=opConv->ca2_dec(ca2);
				}
			
			break;
			
		
		default:
			cout << "\n\t--- ERRORE! ---" << endl << endl;
	}	
	return 0;
}

// ----------------  ESERCITAZIONI OPERAZIONI  ----------------

int eserc_operaz(){
	bool check;
	int operation, bit;
	string s1,s2, answer;
	
	do {
		do{
			check = false;
			cout << "\nQuale operazione vuoi eseguire?" << endl;
			cout << "1) Somma;" << endl;
			cout << "2) Sottrazione;" << endl;
			cout<<"3) Operazione di cambiamento del segno."<<endl;
			cout << "\n\t[Inserisci -1 per tornare indietro]\n" << endl;
			cout << "Operazione: ";
			cin >> operation;
			if (operation < -1 || operation==0 || operation > 3) {
				cout << "\nERRORE! Il numero inserito non corrisponde a nessuna scelta." << endl << endl;
				check = true;
			}
		}while(check);
		
		if(operation==-1)	return 1;
		
		if (operation == 1) { //SOMMA
			//scelta bit
			do {
				check = false;

				cout << "Inserire il numero di bit (4, 8 o 16 bit) degli operandi: ";
				cin >> bit;
				if (bit != 4 && bit != 8 && bit != 16) {
					cout << "\nERRORE! Il numero di bit non rientra nel range consentito, inserisci un valore corretto." << endl << endl << endl;
					check = true;
				}
			} while (check);

			//creazione operandi
			Number* op1 = new Number();
			Number* op2 = new Number();

			s1 = op1->buildOp(bit);
			op1->setCa2(s1);
			op1->setType(2);
			op1->setBit(bit);

			s2 = op2->buildOp(bit);
			op2->setCa2(s2);
			op2->setType(2);
			op2->setBit(bit);

			//matching risposta
			cout << "\n" << op1->getCa2();
			cout << " + " << op2->getCa2() << " =" << endl;
			cout << "Inserire il risultato" << endl;
			cin >> answer;

			Number sum = op1->add(*op2);
			if (sum.getCa2() == answer) {
				cout << "Risultato corretto!" << endl;
				cout << "Se e' presente overflow digita 1 altrimenti 0." << endl;
				bool overflow = sum.isOverflowAdd(op1, op2);
				bool answer2;
				cin >> answer2;
				if (answer2 == overflow) cout << "Esercitazione completata con successo!" << endl;
				else {
					cout << "Scelta errata!" << endl;
					bool overflow = sum.isOverflowAdd(op1, op2);
					if (overflow) cout << "Overflow presente: il risultato ha segno discorde con gli operandi concordi" << endl;
					else cout << "Overflow assente" << endl;
				}
			}
			else {
				cout << "Risultato errato! Ecco il procedimento corretto: " << endl;
				sum = *op1 + *op2;
				bool overflow = sum.isOverflowAdd(op1, op2);
				if (overflow) cout << "Overflow presente: il risultato ha segno discorde con gli operandi concordi" << endl;
				else cout << "Overflow assente" << endl;
			}
		}
		else if (operation == 2) { //SOTTRAZIONE

								   //scelta bit
			do {
				check = false;

				cout << "Inserire il numero di bit (4, 8 o 16 bit) degli operandi: ";
				cin >> bit;
				if (bit != 4 && bit != 8 && bit != 16) {
					cout << "\nERRORE! Il numero di bit non rientra nel range consentito, inserisci un valore corretto." << endl << endl << endl;
					check = true;
				}
			} while (check);
			//creazione operandi
			Number* op1 = new Number();
			Number* op2 = new Number();

			s1 = op1->buildOp(bit);
			op1->setCa2(s1);
			op1->setType(2);
			op1->setBit(bit);

			s2 = op2->buildOp(bit);
			op2->setCa2(s2);
			op2->setType(2);
			op2->setBit(bit);

			//matching risposta
			cout << "\n" << op1->getCa2();
			cout << " - " << op2->getCa2() << " =" << endl;
			cout << "Inserire il risultato" << endl;
			cin >> answer;

			Number diff = op1->sub(*op2);
			if (diff.getCa2() == answer) {
				cout << "Risultato corretto!" << endl;
				cout << "Se e' presente overflow digita 1 altrimenti 0." << endl;
				bool overflow = diff.isOverflowSub(op1, op2);
				bool answer2;
				cin >> answer2;
				if (answer2 == overflow) cout << "Esercitazione completata con successo!" << endl;
				else {
					cout << "Scelta errata!" << endl;
					bool overflow = diff.isOverflowSub(op1, op2);
					if (overflow) cout << "Overflow presente: il risultato ha segno discorde con gli operandi concordi" << endl;
					else cout << "Overflow assente" << endl;
				}
			}
			else {
				cout << "Risultato errato! Ecco il procedimento corretto: " << endl;
				diff = *op1 - *op2;
				bool overflow = diff.isOverflowSub(op1, op2);
				if (overflow) cout << "Overflow presente: il risultato ha segno discorde con gli operandi concordi" << endl;
				else cout << "Overflow assente" << endl;
			}
		}
		else if(operation == 3){ //op di segno
			cout << "\nEs. Operazione di Cambiamento del Segno" << endl << endl;
			Number* opConv=new Number();
			int bit;
			cout<<"Inserire il numero di bit: 4, 8 o 16 -> ";
			cin>>bit;
			string bin=opConv->buildOp(bit);
			opConv->setBin(bin);
			opConv->setBit(bit);
			opConv->setType(1);
			
			string answer;
			cout<<"Inserire la risposta:"<<endl;
			cout<<"n: "<<bin<<" --> -n: ";
			cin>>answer;
			
			if(answer==opConv->bin_ca2_noTxt(bin))	cout<<"\nRisposta corretta. Esercitazione completata con successo!"<<endl<<endl;
			else{
				cout<<"\nRisultato errato! Ecco il procedimento corretto:"<<endl<<endl;
				answer=opConv->bin_ca2(bin,false);
			}
		}	
		else check = true;
	} while (check);
	
	return 0;
}

// ----------------  ESERCITAZIONI  ----------------

void esercitazioni(){
	int operation;
	bool check;
	
	do{
		do {
			check = false;
			cout << "\nSu cosa vuoi esercitarti?" << endl;
			cout << "1) Conversioni;" << endl;
			cout << "2) Operazioni." << endl;
			cout << "\n\t[Inserisci -1 per tornare indietro]\n" << endl;
			cout << "Esercitazione: ";
			cin >> operation;
			if (operation != -1 && operation != 1 && operation != 2){
				cout<<"\nScelta errata, reinseriscila."<<endl<<endl;
				check=true;
			}
		}while(check);
	
		if (operation == 1) {
			
			check=eserc_conv();
	
		}else 
			if (operation == 2) {
				
				check=eserc_operaz();
				
			}else	//-1
				return;
	} while (check);
}



int main() {

	string s1, s2, bin, ca2, answer;
	int bit, conv, operation, menu, dec;
	bool check, checkmenu;
	Number* newnum;
	Number* opConv;

	//MENU' INIZIALE
	cout << "\nBenvenuto/a in Two's Complement - Calcolatore Binario'." << endl;
	do {
		checkmenu = true;
		do {
			check = false;
			print_menu();
			cin >> menu;
			cout << "\n\t---------------------------------" << endl;
			if (menu < 1 || menu > 4) {
				cout << "Scelta errata! Reinseriscila." << endl << endl;
				check = true;
			}
		} while (check);

		if (menu == 1) { //CONVERSIONE
			do {
				check = false;
				print_conversione();
				cin >> conv;	
				cout << "\n\t---------------------------------" << endl;
				if (conv < -1 || conv==0 || conv>6) {
					cout << "\nERRORE! Il numero inserito non corrisponde a nessuna scelta." << endl << endl;
					check = true;
				}
			} while (check);
	
			conversioni(conv);
		}
		else { 
			if (menu == 2) { //OPERAZIONE
				
				int scelta;
				bool ctrl;

				do{
					ctrl=false;
					print_operazioni();
					cin>>scelta;

					if(scelta==1)	operaz_unarie();
					else 
						if(scelta==2) operazioni();
						else
							if(scelta==-1)	break;
							else{
								ctrl=true;
								cout<<"\n !--Inserisci un numero corretto--! "<<endl;
							}
				}while(ctrl);
			}else if (menu == 3) { //ESERCITAZIONE
			
				esercitazioni();
					
			}
			else if (menu == 4) checkmenu = false;
		}
	} while (checkmenu);

	return 0;
}
