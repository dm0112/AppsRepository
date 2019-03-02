#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <string>
#include <errno.h>
#include <functional>
#include <regex>
#include <unordered_map>
#include <fstream>

using namespace std;

#define PORT 6666

#define maxAppPerClient 100

class hardware {

public:
	string ram;
	string procesor;
	string size; // in cm
	string name;
	string putere; // curent, in w
	string weight; // kg
	string producator;
	string category;


	/// input

	void setCategory(auto cat) {
		category = cat;
	}
	void setProducator(auto prod) {
		producator = prod;
	}
	void setRam(auto rm) {
		ram = rm;
	}
	void setSize(auto siz) {
		size = siz;
	}
	void setName(auto nam)
	{
		name = nam;
	}
	void setProcesor(auto proc) {
		procesor = proc;
	}
	void setPutere(auto w) {
		putere = w;
	}
	void setWeight(auto weigh) {
		weight = weigh;
	}
	/*//setallHard
	void setAllHard(auto prod, auto rm, auto sizee, auto nam,
		auto proc, auto w, auto weigh, auto catu) {
		setProducator(prod);
		setRam(rm);
		setSize(sizee);
		setName(nam);
		setProcesor(proc);
		setPutere(w);
		setWeight(weigh);
		setCategory(catu);
	}*/

	///////////// output
	//
	void retCategory(auto) {
		cout << endl << "Category: ";
		cout << category;
	}
	void retRam(auto) {
		cout << endl << "Ram: ";
		cout << ram;
	}
	void retProducator(auto) {
		cout << endl << "Manufacturer: ";
		cout << producator;
	}
	void retProcesor(auto) {
		cout << endl << "Processor: ";
		cout << procesor;
	}
	void retName(auto) {
		cout << endl << "Name: ";
		cout << name;
	}

	// folosim auto - orice char pentru a ne functiona clasa executorul

	void retSize(auto) {
		cout << endl << "Dimensions: " << size;
	}
	void retPutere(auto) {
		cout << endl << "Power (w): " << putere;
		cout << "W";
	}
	void retWeight(auto) {
		cout << endl << "Weight (kg): " << weight;

	}
	// retAllHard
	void retAllHard(auto) {
		cout << "Specifications:";
		retProducator("notNull");
		retRam("notNull");
		retSize("notNull");
		retName("notNull");
		retProcesor("notNull");
		retPutere("notNull");
		retWeight("notNull");
		retCategory("notNull");
		cout << endl;

	}


};


class software : public hardware {

public:
	string platforma; //cu virgula intre ele
	string biblioteci; //cu virgula intre ele
	string statut;
	string dimensions;

	//input
	void setPlatform(auto plat) {
		platforma = plat;
	}
	void setBiblioteci(auto bib) {
		biblioteci = bib;
	}
	void setStatut(auto stat) {
		statut = stat;
	}
	void setDimensions(auto dim) {
		dimensions = dim;
	}

	///out

	///int + string
	void retPlatform(auto) {
		cout << endl << "Supported on: ";
		cout << platforma;
	}
	void retDimensions(auto) {

		cout << endl << "Size: ";
		cout << dimensions;
	}
	void retBiblioteci(auto) {
		cout << endl << "Using: ";
		cout << biblioteci;
	}
	void retStatut(auto) {
		cout << endl << "Software type: ";
		cout << statut;
	}

	/// void
	///// retAllSoftware
	void retAllSoftware(auto) {
		cout << "Software specifications:";
		retPlatform("notNull");
		retBiblioteci("notNull");
		retStatut("notNull");
		retDimensions("notNull");
		cout << endl;
	}
	///// retAll
	void retAllSpecifications(auto) {
		retAllHard("notNull");
		retAllSoftware("notNull");
	}

};

/////////////////////


/*
class simple {

public:
	void lel(const string) {
		cout << "working";
	}
	void test(const string) {
		cout << "dup" << endl;
	}
};
*/
class CommandExecutor : public software//, public simple
{
public:
	void execute(const string& command)
	{
		cmatch match;
		if (regex_match(command.c_str(), match, command_expression_))
		{
			const string command_name(match[1].first, match[1].second - match[1].first);
			const string argument(match[2].first, match[2].second - match[2].first);

			const auto it = commands_.find(command_name);
			if (it != commands_.end())
			{
				it->second(argument);
			}
			
		}
		
	}
	/*void save(){ //prototype
		ofstream fout(name);
		fout.write((char*)this,sizeof(*this));
		fout.close();
		cout<<"DONE";

	}
	void read(string Fname){
		ifstream fin(Fname);



	}*/


	friend ostream& operator<<(ostream& os, const CommandExecutor& s)
	{
		// write out individual members of s with an end of line between each one
		os << s.name << endl;
		os << s.putere << endl;
		os << s.procesor << endl;
		os << s.producator << endl;
		os << s.weight << endl;
		os << s.size << endl;
		os << s.ram << endl;
		os << s.dimensions << endl;
		os << s.statut << endl;
		os << s.biblioteci << endl;
		os << s.platforma << endl;
		os << s.category << endl;
		return os;
	}

	
	friend istream& operator >> (istream& is, CommandExecutor& s)
	{
		// read in individual members of s
		is >> s.name;
		is >> s.putere;
		is >> s.procesor;
		is >> s.producator;
		is >> s.weight;
		is >> s.size;
		is >> s.ram;
		is >> s.dimensions;
		is >> s.statut;
		is >> s.biblioteci;
		is >> s.platforma;
		is >> s.category;
		return is;
	}





	/*private:
			void foo(const string arg)
			{
					cout << "Executing foo(" << arg << ")\n";
			}

			void bar(const string arg)
			{
					cout << "Executing bar(" << arg << ")\n";
			}
	 */


#define REGISTER_COMMAND(name) \
        {#name, [this](const string arg) { this->name(arg); }}

	unordered_map<string, function<void(string)>> commands_ =
	{
		/*REGISTER_COMMAND(foo),
		REGISTER_COMMAND(bar),
		REGISTER_COMMAND(lel), */
		//---------------------- input
		REGISTER_COMMAND(setWeight),
		REGISTER_COMMAND(setPutere),
		REGISTER_COMMAND(setProcesor),
		REGISTER_COMMAND(setName),
		REGISTER_COMMAND(setSize),
		REGISTER_COMMAND(setRam),
		REGISTER_COMMAND(setProducator),
		REGISTER_COMMAND(setDimensions),
		REGISTER_COMMAND(setStatut),
		REGISTER_COMMAND(setBiblioteci),
		REGISTER_COMMAND(setPlatform),
		REGISTER_COMMAND(setCategory),
		//---------------------- output
		REGISTER_COMMAND(retStatut),
		REGISTER_COMMAND(retBiblioteci),
		REGISTER_COMMAND(retDimensions),
		REGISTER_COMMAND(retPlatform),
		REGISTER_COMMAND(retWeight),
		REGISTER_COMMAND(retPutere),
		REGISTER_COMMAND(retSize),
		REGISTER_COMMAND(retName),
		REGISTER_COMMAND(retProcesor),
		REGISTER_COMMAND(retProducator),
		REGISTER_COMMAND(retRam),
		REGISTER_COMMAND(retAllHard),
		REGISTER_COMMAND(retAllSoftware),
		REGISTER_COMMAND(retAllSpecifications),
		REGISTER_COMMAND(retCategory)

	};
	regex command_expression_{ "^([a-zA-Z]+)\\((.*)\\)$" };
};



/////////////////////

int i = 0, newMax = 0;
CommandExecutor executor[maxAppPerClient + 1];

void aplicatieNoua() {
	if (newMax > i) i = newMax; //// atunci cand utilizatorul este la alte obiecte decat cel curent,
	++i;                    ////  daca vrea alta aplicatie, il aduce la cel curent    
	++newMax;
	cout << endl << "Redirectionat la noua aplicatie";
	cout << endl << "Vechea aplicatie are numarul de index " << i - 1 << endl
		<< "O noua aplicatie a fost creata, numarul de index " << i << " " << endl;
}

void jumpToApp(int appIndex) {

	if (appIndex < 0)
	{
		cout << endl << "Indexul incepe de la 0";
	}
	else
	{
		i = appIndex;
	}
	if (appIndex > newMax) {
		i = newMax;
		cout << endl << "Aplicatie inexistenta, redirectare catre cea mai recenta (numarul " << i << ")";
	}
	else {
		cout << endl << "Va aflati la aplicatia numarul " << i << endl;
	}

}

void indexes() {
	cout << endl << "Indexul curent este: " << i;
	cout << endl << "Indexul maxim este: " << newMax;
	cout << endl << "Numarul maxim de aplicatii pe care il puteti adauga este: " << maxAppPerClient << endl;
}

void saveFile() {
	string bla;
	if(executor[i].name!=bla){
	ofstream ofs(executor[i].name);
	
	ofs << executor[i];
	ofs.close();
	}
	else {

	cout << " nume inexistent... nu pot salva "<<endl;}


	// while(i<newMax)
	 //{
	 //	i=++i;
	 //}


	 /*for(int poz=i;poz < newMax -1 ; poz++)
	 {
		 executor[poz]=executor[poz+1];
	 }*/
	 //--newMax;
	 /////////// fix this fusahfasuidn bs, 
}
void readFile(auto File) {///////////////incepe cu indexul 1
	
	if (access(File, F_OK) != -1)
	{		
	ifstream ifs(File);
	ifs >> executor[++newMax];
	//executor[newMax].execute("retName()"); /// testing  
	ifs.close();
	jumpToApp(newMax);
	}
	else cout << endl << "Aplicatia nu este salvata" << endl;

}


void compare(auto word, auto quer) {           //bigFunct
	CommandExecutor temp;
	temp.execute(word);
	int saved[maxAppPerClient], count = 0; // indexes numarul indecsilor la care am potrivirea e corecta

	if (strcmp(quer, "category") == 0) {
		for (int everyApp = 0; everyApp <= newMax; everyApp++)
		{
			if (executor[everyApp].category == temp.category)
				saved[++count] = everyApp;
		}
	}

	if (strcmp(quer, "name") == 0) {
		for (int everyApp = 0; everyApp <= newMax; everyApp++)
		{
			if (executor[everyApp].name == temp.name)
				saved[++count] = everyApp;			//++count pentru if-ul de la finalul functiei 

		}
	}

	if (strcmp(quer, "weight") == 0) {
		for (int everyApp = 0; everyApp <= newMax; everyApp++)
		{
			if (executor[everyApp].weight == temp.weight)
				saved[++count] = everyApp;
		}
	}

	if (strcmp(quer, "putere") == 0) {
		for (int everyApp = 0; everyApp <= newMax; everyApp++)
		{
			if (executor[everyApp].putere == temp.putere)
				saved[++count] = everyApp;
		}
	}

	if (strcmp(quer, "procesor") == 0) {
		for (int everyApp = 0; everyApp <= newMax; everyApp++)
		{
			if (executor[everyApp].procesor == temp.procesor)
				saved[++count] = everyApp;
		}
	}

	if (strcmp(quer, "size") == 0) {
		for (int everyApp = 0; everyApp <= newMax; everyApp++)
		{
			if (executor[everyApp].size == temp.size)
				saved[++count] = everyApp;
		}
	}

	if (strcmp(quer, "ram") == 0) {
		for (int everyApp = 0; everyApp <= newMax; everyApp++)
		{
			if (executor[everyApp].ram == temp.ram)
				saved[++count] = everyApp;
		}
	}

	if (strcmp(quer, "producator") == 0) {
		for (int everyApp = 0; everyApp <= newMax; everyApp++)
		{
			if (executor[everyApp].producator == temp.producator)
				saved[++count] = everyApp;
		}
	}

	if (strcmp(quer, "dimensions") == 0) {
		for (int everyApp = 0; everyApp <= newMax; everyApp++)
		{
			if (executor[everyApp].dimensions == temp.dimensions)
				saved[++count] = everyApp;
		}
	}

	if (strcmp(quer, "statut") == 0) {
		for (int everyApp = 0; everyApp <= newMax; everyApp++)
		{
			if (executor[everyApp].statut == temp.statut)
				saved[++count] = everyApp;
		}
	}

	/// biblioteci/ platforma - gandeste-te

	if (strcmp(quer, "biblioteci") == 0) {
		for (int everyApp = 0; everyApp <= newMax; everyApp++)
		{
			char temp1[1024];

			strcpy(temp1, executor[everyApp].biblioteci.c_str());

			char temp2[1024];

			strcpy(temp2, temp.biblioteci.c_str());

			if (strstr(temp1, temp2))
			{
				saved[++count] = everyApp;
			}

		}
	}

	if (strcmp(quer, "platforma") == 0) {
		for (int everyApp = 0; everyApp <= newMax; everyApp++)
		{
			char temp1[1024];

			strcpy(temp1, executor[everyApp].platforma.c_str());

			char temp2[1024];

			strcpy(temp2, temp.platforma.c_str());

			if (strstr(temp1, temp2))
			{
				saved[++count] = everyApp;
			}

		}
	}



	if (count != 0)
	{
		cout << endl << "Potrivire! Indecsii: ";
		while (count != 0)
		{
			cout << saved[count--] << " ";
		}
	}
	else {
		cout << "Nu am gasit potrivire";
	}
	// 
}

void retAllApplications() {
	for (int obj = 0; obj <= newMax; obj++)
	{
		cout << endl << "Index: " << obj << endl;
		executor[obj].execute("retAllSpecifications()");
		cout << endl;
	}
}

int main(int argc, char* argv[]) {
	/////////////
	//simple lul;


	//executor.execute("foo(1234)");
   // executor.execute("bar(hello_world)");
	//executor.execute("lel()");
///////////////


	int socketfd, ret;
	sockaddr_in sAddress;

	//int PORT;

	int newSocket;
	sockaddr_in newAddr;

	socklen_t addr_size;

	char buffer[1024];
	pid_t childpid;

	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketfd < 0) {
		cout << "Error in connection" << endl;
		return errno;
	}
	cout << "sAddress socket is created" << endl;
	/*if(!argv[1]){                              //port checking - randomly closes
		cout<<"You forgot the port!"<<endl;
		cout<<"I'll give you one more chance, enter the port: ";
		int secChance;
		cin>>secChance;
		if(!secChance)
			{cerr<<"No more chances"<<endl;
		exit(1);}
		else PORT=secChance;
	}
	if(argv[1])*/ //bugging
	//PORT = atoi(argv[1]);

	bzero(&sAddress, sizeof(sAddress));
	bzero(&newAddr, sizeof(newAddr));
	memset(&sAddress, 0, sizeof(sAddress));
	sAddress.sin_family = AF_INET;
	sAddress.sin_port = htons(PORT);
	inet_pton(AF_INET, "0.0.0.0", &sAddress.sin_addr);//accept from any address
	//sAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); //deprecated
	int on = 1;
	setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

	ret = bind(socketfd, (sockaddr*)&sAddress, sizeof(sAddress));
	if (ret < 0) {
		cout << "Error in binding" << endl;
		return errno;
	}
	cout << "Bind to port " << PORT << endl;

	if (listen(socketfd, 10) == 0) {
		cout << "Listening" << endl;
	}
	else {
		cout << "error in Listening" << endl;
		return errno;
	}

	bzero(buffer, sizeof(buffer));
	while (1) {
		newSocket = accept(socketfd, (sockaddr*)&newAddr, &addr_size);

		if (newSocket < 0) { // cout<<newSocket<<endl;
			return errno;

		}
		cout << "Connection accepted from " << inet_ntoa(newAddr.sin_addr) << " " << ntohs(newAddr.sin_port) << endl;

		if ((childpid = fork()) == 0) {
			close(socketfd);

			while (1) {
				//bzero(buffer, sizeof(buffer)); // primul mesaj de la client are lungime diferita,
				recv(newSocket, buffer, 1024, 0);
				if (strcmp(buffer, "exit") == 0 || strcmp(buffer, "") == 0) {
					cout << endl << "Disconnected from " << inet_ntoa(newAddr.sin_addr) << " " << ntohs(newAddr.sin_port) << endl;
					break;
				}
				else {

					executor[i].execute(buffer);

					if (strcmp(buffer, "aplicatieNoua()") == 0)
					{
						aplicatieNoua();
					}

					if (strstr(buffer, "jumpToApp"))
					{
						char index[1024];
						memset(index, 0, sizeof(index));
						int indexi = 0;
						for (int j = 10; j < strlen(buffer) - 1; j++) //strlen(jumpToApp)=9, cu paranteza = 10
							index[indexi++] = buffer[j];
						jumpToApp(atoi(index)); //sare catre una dintre aplicatiile curente

					}

					if (strcmp(buffer, "indexes()") == 0)
					{
						indexes();
					}

					if (strcmp(buffer, "saveFile()") == 0)
					{
						saveFile();
					}

					if (strstr(buffer, "readFile"))
					{
						char num[1024];
						memset(num, 0, sizeof(num));
						int numi = 0;
						for (int j = 9; j < strlen(buffer) - 1; j++)
							num[numi++] = buffer[j];
						readFile(num);

					}

					if (strcmp(buffer, "retAllApplications()") == 0) { /// returnarea tuturor aplicatiilor
						retAllApplications();
					}

					if (strstr(buffer, "searchApp")) // cauta in aplicatiile salvate si in memorie !
					{
						char query[1024];
						memset(query, 0, sizeof(query)); /// reinitializare query
						int queryn = 0;
						for (int j = 10; j < strlen(buffer) - 1; j++)
						{
							query[queryn++] = buffer[j];
						}

						if (access(query, F_OK) != -1)
						{
							cout << endl << "Aplicatia a fost gasita si este salvata" << endl;

						}
						else {
							cout << endl << "Aplicatia nu este salvata, caut in memorie.." << endl;
							char queryy[1024];	// queryy va fi comanda, avem deja un query
							memset(queryy, 0, sizeof(queryy));
							strcpy(queryy, "setName(");
							strcat(queryy, query);
							strcat(queryy, ")"); //am alcatuit comanda pentru execute

							compare(queryy, "name");

						}
					}
					//fixeeeed - if client kills the server-> check all brackets!

					if (strstr(buffer, "searchCategory")) {
						char query[1024];
						memset(query, 0, sizeof(query));
						strcpy(query, "setCategory(");
						int queryI = strlen(query);
						for (int j = 15; j < strlen(buffer) - 1; j++)
						{
							query[queryI++] = buffer[j]; // j- index cuvant buffer
						}
						strcat(query, ")"); //am alcatuit comanda pentru execute
						//cout<<endl<<query;
						compare(query, "category");
					}

					if (strstr(buffer, "searchName")) {
						char query[1024];
						memset(query, 0, sizeof(query));
						strcpy(query, "setName(");
						int queryI = strlen(query);
						for (int j = 11; j < strlen(buffer) - 1; j++)
						{
							query[queryI++] = buffer[j]; // j- index cuvant buffer
						}
						strcat(query, ")"); //am alcatuit comanda pentru execute
						//cout<<endl<<query;
						compare(query, "name");
					}

					if (strstr(buffer, "searchWeight")) {
						char query[1024];
						memset(query, 0, sizeof(query));
						strcpy(query, "setWeight(");
						int queryI = strlen(query);
						for (int j = 13; j < strlen(buffer) - 1; j++)
						{
							query[queryI++] = buffer[j]; // j- index cuvant buffer
						}
						strcat(query, ")"); //am alcatuit comanda pentru execute
						//cout<<endl<<query;
						compare(query, "weight");
					}

					if (strstr(buffer, "searchPutere")) {
						char query[1024];
						memset(query, 0, sizeof(query));
						strcpy(query, "setPutere(");
						int queryI = strlen(query);
						for (int j = 13; j < strlen(buffer) - 1; j++)
						{
							query[queryI++] = buffer[j]; // j- index cuvant buffer
						}
						strcat(query, ")"); //am alcatuit comanda pentru execute
						//cout<<endl<<query;
						compare(query, "putere");
					}

					if (strstr(buffer, "searchProcesor")) {
						char query[1024];
						memset(query, 0, sizeof(query));
						strcpy(query, "setProcesor(");
						int queryI = strlen(query);
						for (int j = 15; j < strlen(buffer) - 1; j++)
						{
							query[queryI++] = buffer[j]; // j- index cuvant buffer
						}
						strcat(query, ")"); //am alcatuit comanda pentru execute
						//cout<<endl<<query;
						compare(query, "procesor");
					}

					if (strstr(buffer, "searchSize")) {
						char query[1024];
						memset(query, 0, sizeof(query));
						strcpy(query, "setSize(");
						int queryI = strlen(query);
						for (int j = 11; j < strlen(buffer) - 1; j++)
						{
							query[queryI++] = buffer[j]; // j- index cuvant buffer
						}
						strcat(query, ")"); //am alcatuit comanda pentru execute
						//cout<<endl<<query;
						compare(query, "size");
					}


					if (strstr(buffer, "searchProducator")) {
						char query[1024];
						memset(query, 0, sizeof(query));
						strcpy(query, "setProducator(");
						int queryI = strlen(query);
						for (int j = 17; j < strlen(buffer) - 1; j++)
						{
							query[queryI++] = buffer[j]; // j- index cuvant buffer
						}
						strcat(query, ")"); //am alcatuit comanda pentru execute
						//cout<<endl<<query;
						compare(query, "producator");
					}

					if (strstr(buffer, "searchRam")) {
						char query[1024];
						memset(query, 0, sizeof(query));
						strcpy(query, "setRam(");
						int queryI = strlen(query);
						for (int j = 10; j < strlen(buffer) - 1; j++)
						{
							query[queryI++] = buffer[j]; // j- index cuvant buffer
						}
						strcat(query, ")"); //am alcatuit comanda pentru execute
						//cout<<endl<<query;
						compare(query, "ram");
					}



					if (strstr(buffer, "searchDimensions")) {
						char query[1024];
						memset(query, 0, sizeof(query));
						strcpy(query, "setDimensions(");
						int queryI = strlen(query);
						for (int j = 17; j < strlen(buffer) - 1; j++)
						{
							query[queryI++] = buffer[j]; // j- index cuvant buffer
						}
						strcat(query, ")"); //am alcatuit comanda pentru execute
						//cout<<endl<<query;
						compare(query, "dimensions");
					}

					if (strstr(buffer, "searchStatut")) {
						char query[1024];
						memset(query, 0, sizeof(query));
						strcpy(query, "setStatut(");
						int queryI = strlen(query);
						for (int j = 13; j < strlen(buffer) - 1; j++)
						{
							query[queryI++] = buffer[j]; // j- index cuvant buffer
						}
						strcat(query, ")"); //am alcatuit comanda pentru execute
						//cout<<endl<<query;
						compare(query, "statut");
					}



					if (strstr(buffer, "searchBiblioteci")) {
						char query[1024];
						memset(query, 0, sizeof(query));
						strcpy(query, "setBiblioteci(");
						int queryI = strlen(query);
						for (int j = 17; j < strlen(buffer) - 1; j++)
						{
							query[queryI++] = buffer[j]; // j- index cuvant buffer
						}
						strcat(query, ")"); //cu cele de mai sus, am alcatuit comanda pentru execute
						//cout<<endl<<query;
						compare(query, "biblioteci");
					}

					if (strstr(buffer, "searchPlatform")) {
						char query[1024];
						memset(query, 0, sizeof(query));
						strcpy(query, "setPlatform(");
						int queryI = strlen(query);
						for (int j = 15; j < strlen(buffer) - 1; j++)
						{
							query[queryI++] = buffer[j]; // j- index cuvant buffer
						}
						strcat(query, ")"); //cu cele de mai sus, am alcatuit comanda pentru execute
						//cout<<endl<<query;
						compare(query, "platforma");
					}






					/*if(strcmp(buffer,"save()")==0)
					{
						executor[i].save();
					}*/

					/* if(!(strcmp(buffer,"")==0)||!(strcmp(buffer,"\n")==0))
					 cout<<buffer<<endl;

					 if(strcmp(buffer, "setAllHard")==0){
						 v.setAllHard("bip", 4, 5, 6, 7, "bop", "nop", 8, 8.2);
					 }
					 if(strcmp(buffer, "retAllHard")==0){
						 v.retAllHard();
					 }

					 if(strcmp(buffer, "retAllSpecifications")==0){
						 v.retAllSpecifications();
					 }

					 */

					 ////////////////
					 /*if(strcmp(buffer, funcName)==0)
						 test();*/

						 /*int charsFound=0; // numara caracterele gasite din numele functiei
						 strcpy(funcName,"asdsa");

						 for(int i=0;i<strlen(buffer);i++)
							 if(funcName[i]==buffer[i])
								 charsFound++;
						//buffer mai mare cu 1 pentru client, cu 2 pentru clientul telnet,  primul ok pentru result, al doilea pt buffer
						 if(charsFound==strlen(funcName) && charsFound==strlen(buffer)-1){
							 test();
							 //fflush(stdout); //useless

						 }*/
					//cout << endl << buffer << endl;
					fflush(stdout);

					send(newSocket, buffer, strlen(buffer), 0);

					bzero(buffer, sizeof(buffer));


				}
			}
		}

	}



	close(newSocket);
	/*
	///////////////////////// BUUUUGGGGSSSS SADSADASDSA
	prima conectare ip 0.0.0.0 port 0 ?? totul functioneaza,  /
	cu a doua conectare apare ip-ul si portul normal /
	AMBELE CONECTARI VIZIBILE CU WIRESHARK (normal) /
	cauze (?) (mostly random): functia searchRam(), searchBiblioteci() si searchPlatforma(),
	 searchApp() (functia de cautare in memorie) poate si altele
	Clasele hardware si software pot fi una si aceeasi cu CommandExecutor, dar le-am lasat asa
		Cum sa adaugi o variabila:
		1. o declari oriunde in hardware, software sau CommandExecutor
		2. scrii functii pentru set si ret
		3. register_command pentru acele functii
		4. adaugi la scrierea si citirea din fisier variabila !
		5. scrii functie de cautare
		6. te asiguri ca totul este scris corect si
		ca numarul de aparitii al variabilei este cel putin asemanator cu celelalte
	*/
	return 0;
}