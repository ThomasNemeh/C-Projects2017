# Basic building blocks of C++

For this assignment you will code using some of the basic building blocks of C++: vectors, functions, and classes.

Where you are to write functions, ensure you use constness and references where appropriate, to avoid needlessly copying objects, and to help ensure you have written correct code.

Note this coursework has a split deadline: an earlier deadline for "buy low, sell high" and "treasure hunt"; and a later deadline for "circular buffer".

## The PEP vector class -- technical note

To ensure you are using `vector` correctly, for this work you will be using a version specially adapted for this assignment.  It is used by all the skeleton code provided, and involves writing:

`#include "vector.h"`  
`using pep::vector;`  

... instead of the usual:

`#include <vector>`  
`using std::vector;`  

This should not affect your solution, but note that outwith this assignment you should use the regular std vector implementation where appropriate.


# Buy low, sell high [4 marks]

The price of a given commodity, can be represented by a vector of prices.  For instance:

`vector<int> prices {28, 18, 20, 26, 24};`  

To maximise profit, we would want to buy low and sell high -- in this case, buy at time 1 (when the cost is 18), sell at time 3 (when the cost is 26).

In `Trade.h` implement a function `bestBuySellTime` that takes a vector of prices and returns a `Trade' object with the buy and sell time that maximises profit.  This function does not live inside any class -- it is to be defined as a global function.

To perform some basic testing on your code, once you have implemented the function (or at least declared it) `TestTrade.cpp` defines a simple test harness.  To compile this, run:

`g++ -std=c++11 -o TestTrade TestTrade.cpp`  

If it compiles, you can then run:

`./TestTrade`  

If you push your code to your GitHub repository, it will be ran against some additional test cases, and you'll be emailed the results of these.

When your work is marked, a wider range of test cases will be used, including input vectors that contains millions of numbers -- your code should be able to handle these with modest resources (10 seconds of CPU on a desktop machine, and 0.5GB of RAM).  

# Treasure hunt [3 marks]

For this piece of coursework, you will write code to work with data about items that are placed at different places on a map, each of which is available for just 15 minutes starting at a certain number of seconds past the hour.

Items are described by four properties:

- Their latitude (a number in degrees, e.g. 51.75087595155126)
- Their longitude (a number in degrees, e.g. -0.33483137537806396)
- A string ID
- The time at which they become available: an integral number of seconds past the hour

In Item.h, make a class Item that contains these as private member variables.

Give the class an appropriate constructor that initialises these four variables to the arguments passed to the constructor (passed in the above order).

Implement an `operator<<` function for printing out Item objects, so that the following code will work:

`Item strand(51.5115, -0.116, "StrandCampus", 600);`  
`cout << strand << endl;`  

...and will produce output of the form:

`{latitude, longitude, "ID", time}`

...in this case:

`{51.5115, -0.116, "StrandCampus", 600}`  

Once you have done this, create a class function `distanceTo` that will take another Item, and return the distance to it in metres.  To compute this distance, use the [Haversine Formula](http://andrew.hedges.name/experiments/haversine/), which can be implemented using the following pseudo-code:

`dlon = lon2 - lon1`  
`dlat = lat2 - lat1`  
`a = pow((sin(dlat/2)), 2) + cos(lat1) * cos(lat2) * pow((sin(dlon/2)), 2)`  
`c = 2 * atan2( sqrt(a), sqrt(1-a) )`  
`distance = R * c (where R is the radius of the Earth)`  

Note that this pseudo-code assumes the latitude and longitude are in *radians*, whereas your class stores them in degrees, so you will need to convert them to radians first.  `cos`, `sin` and the other trignometric functions can be obtained by putting `#include <cmath>` at the top of Item.h.  You should assume `R`, the radius of the earth in metres, is 6373000.

To test your code, you can use ItemTest.cpp.  To compile to an executable `ItemTest`, run:

`g++ -std=c++11 -o ItemTest ItemTest.cpp`  

Note that this will only work once you have implemented the constructor and functions discussed above.


# A circular buffer [3 marks]

This is the advanced part of this assignment -- note it has a later deadline than the earlier parts.

## What is a circular buffer?

Circular buffers use a fixed-size block of memory to temporary buffer data.  For instance, keypresses on the keyboard put characters in the buffer; and when the operating system is ready to process them, it reads characters from the buffer.

The buffer starts as being empty.  For instance, if we had a buffer of size 5 it would look like:

`[   |   |   |   |   ]`  


If we then write 'a' and 'b' into the buffer it would look like:

`[ a | b |   |   |   ]`  


...and then removing the next item in the buffer would give:

`[   | b |   |   |   ]`  


If we continue to write elements into the buffer, e.g. 'c', 'd', 'e', 'f' then when the end is reached, elements start being written into any spare space at the start:

`[ f | b | c | d | e ]`  


At this point the buffer is full.  We can't write any more data to it -- in the case of keyboard buffers, the computer would start beeping.  We can though remove an element, which always removes the *oldest*, i.e. the letter 'b', which would leave the buffer:

`[ f |   | c | d | e ]`  

We could then remove the next element (c), or as there is now a space again, write another character into the buffer.

## Implement a circular buffer

In the file`CircularBuffer.h` complete the definition of the CircularBuffer class.  Your implementation should be based on a vector of characters.

The constructor of the class should take the capacity of the buffer as an argument.  There should be no default constructor.

It needs to have the functions:  
1. `count()` which returns how many things are in the buffer  
2. `full()` which returns true *iff* the buffer is full  
3. `add()` which takes a character and adds it to the buffer (you can assume the buffer is not full -- you do not need to implement error handling)  
4. `remove()` which removes and returns the next character from the buffer (you can assume the buffer is not empty -- you do not need to implement error handling)  
 
Once you have provided the constructor and functions, you can test your code using `TestCircularBuffer.cpp`.  To compile this, run:

`g++ -std=c++11 -o TestCircularBuffer TestCircularBuffer.cpp`  

If it compiles, you can then run:

`./TestCircularBuffer`  

As well as being confident your solution behaves correctly, and that you have used const appropriately, ensure you use the initialisation syntax with your constructor to appropriately initialise the vector to be the right size.


