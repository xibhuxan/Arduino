
Created by Xibhu - Carlos MR - https://github.com/xibhu  
Made in Canary islands, Spain

# XibDebounceEdge Library

This library allows you to "watch" any bool variable and execute stuff in typical button cases and avoid the debounce effect. Can be used with buttons, sensors or any kind of bool variable you want to use with usual buttons functions.

You should use this library because it allows you to manage buttons in a easy way. Also it's a lightweight library.

- whenActive: While the input it's on (true), the function "whenActive" do the function forever, until change to false
- whenDeactive: While the input it's off (false), the function "whenDeactive" do the function forever, until change to true
- whenRisingEdge: Only in the rising edge the function works (one time per rising edge)
- whenFallingEdge: Only in the falling edge the function works (one time per falling edge)
 
It's supposed to use one function per object. For instance:

Allowed:
```
XibDebounceEdge myButtonOne(20);
myButtonOne.whenActive(myRead, myFunction);
```

Not allowed:
```
XibDebounceEdge myButtonOne(20);
myButtonOne.whenActive(myRead, myFunction);
myButtonOne.whenRisingEdge(myOtherRead, myOtherFunction);
```

Solution:
```
XibDebounceEdge myButtonOne(20);
XibDebounceEdge myButtonTwo(20);

myButtonOne.whenActive(myRead, myFunction);
myButtonTwo.whenRisingEdge(myOtherRead, myOtherFunction);
```
You can use the var "myRead" or "myOtherRead" in multiples objects if needed with no problem.

It's made by this way because it's x4 times lighter than allows the four functions works at the same time. The usual "use case" is only use one function per button.