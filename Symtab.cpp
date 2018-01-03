#include "Symtab.h"
using namespace std;
class Symtab
{

Symtab::Symtab(){
	level = -1;
	procnr = 0;
}

void Symtab::level_up(){
	cout << "Symtab-level-up\n";
	level++;
}


void Symtab::level_down(){
	cout << "Symtab-level-down\n";
	content[level--].clear();
}

int Symtab::insert(const string name , const int typ, const int var)
	{

	int n= content[level].size(), r =1;
	 
	if(content[level].find(name)== content[level].end()){
		content[level][name] =
			symtab_entry(typ, n, (typ == st_proc)? ++procnr: val)

	cout<<"Symtab-insert"<< name << " :"<<content[level][name]<<"/"<<content[level][name].nr
		<<" procnr: "<<procnr;
	r=0;
 	}
	return r;
}


int Symtab::lookup(string name, int type, int &l, int &o, int value){
	int i =  level +1, rc;
	cout<<"Symtab-lookup"<<name<<"(Typ"<<type<<")";
	l=o=-1;
	while(--i>=0&& content[i].find(name)== content[i].end()){
		if(i>=0){
			if(content[i][name].type & type){//keine und Verknüpfung? oder soll das Bitweise sein?
				l= level -i, o = content[i][name].nr, value = content;

			}else rc=-1;//Falscher Typ
		}else rc= -2;//Nicht gefunden
	}
	return rc;
}


int Symtab::print(){

	map<string, symtab_entry> ::iterator pos;
	cout<<"Akt.Level:"<<level<<endl;
	for(int i=0; i<=level; i++){ 
		cout<<"Level "<<i<<"Hoehe "<<content[i].size();
		pos = content[i].begin();
		for(pos = content[i].begin(); pos!=content[i].end(); ++i)
			cout<<"Key: "<<(*pos).first<<(*pos).second.nr;
	}
}

}