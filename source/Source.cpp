/*
OOPBasic
(c) 2016
original authors : David I.Schwartz
Written under the supervision of David I.Schwartz, Ph.D., and
supported by a professional development seed grant from the B.Thomas
Golisano College of Computing & Information Sciences
(https ://www.rit.edu/gccis) at the Rochester Institute of Technology.
	This program is free software : you can redistribute it and / or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or (at
		your option) any later version.
	This program is distributed in the hope that it will be useful, but
	WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the GNU
	General Public License for more details.
	You should have received a copy of the GNU General Public License
	along with this program.If not, see <http://www.gnu.org/licenses/>.

*	This tutorial demonstrates the ways to define a struct type, initialize structures,
	assign values to members,  and define enum type.
*	It covers issues the concepts of Aggregates, POD, Member Access Operators, 
	the Precedence of C++ Built-in Operators, New Operator, Pointers and Arrays.
*/



#include <iostream>
using namespace std;

#pragma region Stuff called by main
enum OutsideColor { BLUE, GREEN, GRUE };	// define enum type OutsideColor, enumerate the constants member "BLUE", "GREEN", "GRUE"

// why don't I need to use a "typedef" for this struct?
// reason: (adapted from: http://stackoverflow.com/questions/612328/difference-between-struct-and-typedef-struct-in-c)
// In C++, all struct class delacration act like they are implicitly typedef.

struct Point {	// declare Point struct type
	int x;		// are these "fields" public or private by default? Ans: public
	int y;		// struct Point gets two int type members x and y.
};

void test1(Point p) {     // is this p an alias or copy? Ans: a copy
	p.x = 10;             // if copy, where is it allocated? Ans: It is allocated in the stack.
	p.y = 20;
	cout << &p << endl;
}

void test2(Point* p) {    // is this p an alias or copy?	Ans: a alias
	p->x = 10;            // why use "->" instead of "."?	Ans: beacause p is a pointer to the struct
	p->y = 20;
}

#pragma endregion

int main() {

#pragma region Enums
	//see http://msdn.microsoft.com/en-us/library/2dzy4k6e.aspx
	//and http://msdn.microsoft.com/en-us/library/bd77ckhw.aspx
	//and http://msdn.microsoft.com/en-us/library/whbyts4t.aspx
	//cout << "testing basic enums" << endl;                // output: testing basic enums
	//enum InsideColor { RED, ORANGE, YELLOW };             // define enum type InsideColor, assign an integral value correponds to the enumeration's place
	                                                        // by default, RED gets 0, ORANGE gets 1, YELLOW gets 2
	//InsideColor e1 = RED;                                 // e1 gets 0
	//OutsideColor e2 = BLUE;                               // e2 gets 0
	//cout << BLUE << endl;                                 // output: 0
	//cout << OutsideColor.GRUE << endl;                    // error: OutsideColor is not class or struct or union. use "OutsideColor::GRUE" or "GRUE"
	//cout << static_cast<OutsideColor>(e1 + 1) << endl;    // output: 1	convert (e1 + 1) to the OutsideColor type
	//cout << OutsideColor(YELLOW);                         // output: 2	what am I doing in this statement? Ans: converts 2 to 2
#pragma endregion

#pragma region Allocating structs
	//see http://msdn.microsoft.com/en-us/library/64973255.aspx
	//cout << "testing basic structs" << endl;         // output: testing basic structs
	//Point p1;                                        // P1 is a POD (what's that?) Ans: Plain Old Data see: http://stackoverflow.com/questions/146452/what-are-pod-types-in-c
	//cout << p1 << endl;                              // since p1 is a POD, do we get default value? Ans: No.
	//p1.x=1;                                          // assign 1 to member x of p1
	//p1.y=2;                                          // assign 2 to member y of p1
	//cout << p1.x << endl;                            // output: 1
	//cout << p1.y << endl;                            // output: 2
	//Point p2 = {3, 4};                               // initialize Point struct p2 whose member x gets 3, y gets 4
	//cout << p2.y << endl;                            // output: 4
	//Point p3 = {5};                                  // initialize Point struct p3 whose member x gets 5, y gets default value (0)
	//cout << p3.y << endl;                            // output: 0
	//Point p4 = { };                                  // initialize Point struct p4 whose members get default values (0)
	//cout << p4.y << endl;                            // output: 0
#pragma endregion

#pragma region Copy or reference?
	//Point p5 = {1, 2};        // need another point to mess with
	//Point p6 = p5;            // did I make an alias or copy?	Ans: copy
	//cout << p6.y << endl;     // output: 2 | are we REFERRING or just accessing a COPY?	Ans: we are accessing a COPY.
	//p6.x = 3;                 // see if we're referring...
	//cout << p5.x << endl;     // output: 1 | what happens? why?		
	//                          // Ans: the value of member x of p5 did not change, because we only changed the value of the copy of p5
	//test1(p5);                // output: 000000EF5688F8B0 | do we pass a copy or reference?  Ans: We pass a copy.
	//cout << p5.x << endl;     // output: 1 | did p5 change DURING the function call? Ans: No.
	
#pragma endregion

#pragma region Stack or heap allocation?
	// see new: http://msdn.microsoft.com/en-us/library/kewsb8ba.aspx
	Point p7 = {1,2};            // need a "fresh" point object
	// cout << p7[0] << endl;       // p7 is not an array????? ******
	// Point p8 = new Point();      // does "new" put on stack or heap? but does this assignment actually work? Ans: heap. No, it does not work.
	Point* p8 = new Point();     // how about this one? is "new" kind of like "malloc" in regard to returning a pointer? Ans1: This line works. 
	                             // Ans2: new calls the constructor and destructor, while malloc allocate and release raw memory .
	(*p8).x = 1;                 // what happens if you remove the ()? (covered more in next section) compile time error. It means a pointer to a struct can not point to the members
	cout << &p7 << endl;         // output: 00000020F6CAF9C8
	cout << &(p7.x) << endl;     // output: 00000020F6CAF9C8
	cout << &p8 << endl;         // output: 00000020F6CAF9E8
	cout << &((*p8).x) << endl;  // output: 00000020F6E12D20 | is p1's location different from p1.x? Ans: Yes.
	test1(*p8);                  // output: 00000020F6CAF9A0 | pass the copy struct into test1
	cout << (*p8).x << endl;     // output: 1 | did I manage to change p8's records? Ans: No, only change the copy's value.
	delete p8;                   // see https://msdn.microsoft.com/en-us/library/h6227113.aspx
	cout << p8 << endl;          // output: 0000000000008123 | The memory is still there. (better not use it even though it is deleted)
#pragma endregion

#pragma region struct pointers and members
	//operator precedence:      http://msdn.microsoft.com/en-us/library/126fe14k.aspx
	//struct and union members: http://msdn.microsoft.com/en-us/library/99xt54aa.aspx
	//. and ->:                 http://msdn.microsoft.com/en-us/library/b930c881.aspx
	//Point* p9 = new Point();  // initialize the pointer p9 (heap allocated)
	//p9.x = 1;                 // compile time error: p9 is a pointer not class type
	//*p9.x = 1;                // compile time error. 
	                            // In this case, "." is in the group 2 precedence and "*" is in the group 3 precedence; 
	                            // the LFS should be read as "assign 1 to the dereference of p9's member x " which is illegal.
	//(*p9).x = 3;              // see above links | dereference of p9 which is a struct, assign 3 to its member x.
	//cout << (*p9).x << endl;  // output: 3
	//p9->y = 4;                // p9's member y gets 4
	//cout << p9->y << endl;    // output: 4
	//test2(p9);                // pass POINTER to a struct; what's the state of p9 after the call? Ans: The values of p9's members are changed.
	//cout << p9->y << endl;    // output: 20
	//delete p9;                // invokes destructor prior to deallocating memory
#pragma endregion

#pragma region Array of structs
	//struct Person {                   // can you "inline" a struct?  Ans: Yes
	//	char* name;                   // is this a string? Ans: Yes.
	//	int id;                       // declare a int type member
	//} people[2];                      // do we end up with an array of structs?
	//people[0].name = "pat";           // assign "pat" to people[0]
	//printf("%s%\n",people[0].name);   // ouput: pat
	//Person p10[] = {                  // initialize an struct type array p10
	//	{ "pat", 123},                  // assign values to p10[0] struct members
	//	{ "sam", 456}                   // assign values to p10[1] struct members
	//};                                //
	//cout << p10[1].name << endl;      // output: sam
	//int* p11 = new int[3];            // arrays: http://msdn.microsoft.com/en-us/library/7wkxxx2e.aspx
	//Person* p12 = new Person[2];      // stack or heap? Ans: heap
	//p12[1].id = 321;                  // why do we need "." and not "->"? Ans: because p12[1] is a value of struct not a pointer.
	//cout << p12[1].id << endl;        // output: 321
	//delete[] p12;                     // see http://msdn.microsoft.com/en-us/library/h6227113.aspx
#pragma endregion

#pragma region Nested structs
	//struct Pixel {                    // declare a struct type
	//	Point p;                        // declare struct member which is also a struct type
	//	OutsideColor color;             // declare struct member which is a enum type
	//};                                //
	//Pixel p13 = { {1,2}, BLUE };      // initialize Pixel type variable p13
	//cout << p13.p.x << endl;          // output: 1
	//
	//Exercise: Make another Pixel type. But this time, make everything a pointer
	//          inside your pixel type, include an array of colors, and a 
	//          Boolean field for indicating if the pixel is on/off.
	//          Make an array of your pixels with randomly chosen colors, 
	//          and display all the colors. Feel free to add more functions.
#pragma endregion

	system("pause");
}
