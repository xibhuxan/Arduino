#include<Vector.h>

class Person {
  char* n;
  char* ssn;
public:

  Person(char* social)
    :ssn(social) {}
  Person();

  char* name() const {
    return n; 
  }
  
  char* social() const {
    return ssn; 
  }

  void set_name(char* name) { 
    n = name; 
  }
  
  void set_ssn(char* social) {
    ssn = social; 
  }
};


void setup() {
  Serial.begin(9600);

  Vector<int> vi;

  int sz = vi.size();
  Serial.print("size of vi is: ");
  Serial.println(sz);

  for(int i=0; i<200; i+=10) {
    vi.push_back(i);
  }

  sz = vi.size();
  Serial.print("size of vi is: ");
  Serial.println(sz);

  Serial.println("Let's have a look at vi: ");
  for(int i = 0; i < vi.size(); ++i) {
    Serial.print("\tthe element at index ");
    Serial.print(i);
    Serial.print(" is: ");
    Serial.println(vi[i]);
  }

  Person* p1 = new Person("123-45-6789"); 
  p1->set_name("Zac");
  Person* p2 = new Person("111-22-3333"); 
  p2->set_name("Elissa");
  Person* p3 = new Person("333-22-4444"); 
  p3->set_name("Parker");


  Vector<Person*> vp;
  vp.push_back(p1);
  vp.push_back(p2);
  vp.push_back(p3);

  Serial.print("size of the person vector is: ");
  Serial.println(vp.size() );
  Serial.print("Capacity of the person vector is: ");
  Serial.println(vp.capacity() );
  for(int i = 0; i < vp.size(); ++i) {
    Serial.print("the person at ");
    Serial.print(i);
    Serial.print(" is: ");
    Serial.println( vp[i]->name() );
  }

	//set size at construction
	Serial.println("-------------------------------");
	Vector<int> v_sized(3);
	Serial.print("size of the space constructed vector is: ");
	Serial.println(v_sized.size() );
	Serial.print("Capacity of the space constructed vector is: ");
	Serial.println(v_sized.capacity() );

}

void loop() {
  //create and destroy a local vector many times to see if the 
  //Arduino crashes...which it does.
  //I believe this crash is from segmentation, but I have not 
  //done any checks to verify this.

  Serial.println("--------------------------");
  Vector<char*> vc;
  vc.push_back("first");
  vc.push_back("second");
  vc.push_back("third");
    for(int i = 0; i < vc.size(); ++i) {
    Serial.print("the data at ");
    Serial.print(i);
    Serial.print(" is: ");
    Serial.println( vc[i] );
  }

}