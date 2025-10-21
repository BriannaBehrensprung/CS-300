# CS-300
projects/pseudocode for hash tables/ vectors/ binary search tree 


What was the problem you were solving in the projects for this course?
The problem I was solving during the projects was evaluting and implementing different data structures. In this case, Vectors, Hash Tables and Binary Search Trees to determine which one was the most effective for handling course data. 

How did you approach the problem? Consider why data structures are important to understand.
While creating pseudocode and other codes not shown in the project itself, I was able to gain an understanding of how the choice of structure directly impacts the runtime and memory usage. How quickly can a new course be added to the data structure, how quickly can a user find course details, and how quickly can courses be listed in an aplhanumeric order. Creating the table showed the runtimes of each, which compared different sections and then the overall runtime. There are trade offs to some of these tables, but each one has their pros and cons which is important to understand dependent on the system being made. Based on the runtime efficiency for quick course retrieval (the most frequent advisory query), the Hash Table was recommended and subsequently implemented in the C++ project. The Hash Table implementation used separate chaining with an ASCII-based hash function.

How did you overcome any roadblocks you encountered while going through the activities or project?
A key roadblock was making the inherently unordered Hash Table still provide a required alphanumeric sorted list of all courses5. This was overcome by extracting all courses from the hash table and then using a standard sorting algorithm, accepting the necessary O(n log n) runtime for that specific operation.

How has your work on this project expanded your approach to designing software and developing programs?
The work expanded my approach by emphasizing runtime efficiency and trade-offs as primary design constraints, forcing me to optimize the choice of data structure for the most frequent operation (quick course lookup). This taught me that performance analysis is a mandatory initial step in software design, not a later optimization.

How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?
My program writing evolved by adopting modular design, separating the core HashTable logic (like hashing, insertion, and searching) from the application's file loading and user interface logic. This separation of concerns makes the code more maintainable and adaptable, as changes to one area (like the hash function) do not break others (like the menu).
