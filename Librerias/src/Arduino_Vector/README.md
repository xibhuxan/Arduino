Arduino_Vector
==============

Lightweight implementation of the STL vector for Arduino

Dynamic memory management on a microcontroller can lead to overflows if not managed carefully.

### But...

I've wanted to use a vector to store a limited number of objects like pointers to different sensors
on my robot or a list of 10 control options to manuever based off the sonar's data.  Instead of using
an array I decided to implement the C++ STL vector with limited functionality to keep the code size 
small and the operations focused on the basics.

This first verion on my Vector has the basics you expect.

  a. No penatly for construction

`Vector<foo> vf;   //sizof(vf) == 0 until you push_back into it.`

  b. Normal C++ push_back for appending data to the end of the vector

`vf.push_back(foo);`

  c. Normal access operator

`vf[0] = foo2;`

  d. Normal .size() method for traversing the vector

````
    for(int i=0; i<vf.size(); ++i) {
      Serial.print("foo is: ");
      Serial.println(vf[i]);
    }
````    
Behind the scenes vector acquires free store memory and releases it using the same mechanisms as the
STL container.

Installation
==============

1. From the command line 'cd' into the Arduino/libraries folder.
2. Enter 'git clone http://github.com/zacsketches/Arduino_Vector.git'
3. This will clone the library into your Arduino libraries.
4. Restart the Arduino IDE.  Click on examples and you will see the Vector library and the Vector_use example.
