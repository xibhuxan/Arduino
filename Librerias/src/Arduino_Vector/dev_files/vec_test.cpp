#include "Vector.h"
#include <iostream>
#include <stdexcept>
#include <sstream>

using namespace std;

class Person {
	string n;
	string ssn;
public:
	
	Person(string social)
		:ssn(social) {}
	Person();
	
	string name() const {return n; }
	string social() const {return ssn; }
	
	void set_name(string name) { n = name; }
	void set_ssn(string social) {ssn = social; }
};

ostream& operator<<(ostream& os, const Person& p) {
	os<<"Name: "<<p.name()<<"\tSocial: "<<p.social();
	return os;
}

// error() disguises throws:
inline void error(const string& s){ throw runtime_error(s);}

inline void error(const string& s, const string& s2) { error(s+s2); }

inline void error(const string& s, int i){
	ostringstream os;
	os << s <<": " << i;
	error(os.str());
}

int main ()
{
	try{
		Vector<int> zv;
		cout<<"size is: "<<zv.size()<<endl;
		cout<<"space is: "<<zv.capacity()<<endl;
		zv.push_back(3);
		cout<<"size is: "<<zv.size()<<endl;
		cout<<"space is: "<<zv.capacity()<<endl;
		cout<<"item in position 0 is: "<<zv[0]<<endl;
		
		Vector<string> zvs;
		zvs.push_back("Elissa");
		zvs.push_back("is");
		zvs.push_back("an imp...with a great rack!");
		
		for(int i = 0; i < zvs.size(); ++i) {
			cout<<"the item at "<< i<< " is: "<<zvs[i]<<endl;
		}
		
		Person* p1 = new Person("123-45-6789"); p1->set_name("Zac");
		Person* p2 = new Person("111-22-3333"); p2->set_name("Elissa");
		Person* p3 = new Person("333-22-4444"); p3->set_name("Parker");
		
		Vector<Person*> vp;
		vp.push_back(p1);
		vp.push_back(p2);
		vp.push_back(p3);

		cout<<"size is: "<<vp.size()<<endl;
		cout<<"space is: "<<vp.capacity()<<endl;
		for(int i = 0; i < vp.size(); ++i) {
			cout<<"the item at "<< i<< " is: "<<*vp[i]<<endl;
		}

		Vector<string> vs2;
		vs2 = zvs;
		cout<<"let's have a look inside vs2: "<<endl;
		for(int i = 0; i < vs2.size(); ++i) {
			cout<<"the item at "<< i<< " is: "<<vs2[i]<<endl;
		}
		
		return 0;
	}
	catch(runtime_error& e){
		cerr<<"runtime error: "<<e.what()<<endl;
		return 1;
	}
	catch(...){
		cerr<<"caught unknown error\n";
		return 2;
	}
}