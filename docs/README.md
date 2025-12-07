# 📂 STRUCTURE
```
Leetcode/  
├── docs/            # Documentation and scripts  
│   ├── README.md         # This documentation file  
│   ├── PROBLEM_LIST.md           # Markdown file use to list all solved problems 
│   └── update_readme.py  # Script to update README.md automatically  
├── inc/             # C++ header files  
│   ├── listnode.h        # Definition for ListNode (linked list)  
│   ├── solution.h        # Solution class declarations  
│   └── test.h            # Test class declarations  
├── main.cpp         # Main C++ entry point  
├── main.py          # Main Python entry point  
├── Makefile         # Build script for C++  
├── src/             # Source code  
│   ├── cpp/              # C++ solution files  
│   └── py/               # Python solution files  
├── utils/           # Utility code  
│   └── print.h           # Helper functions for printing (C++)
```
# 📝 Note 
File [update_list.md](update_list.py) will help to automatically update file [PROBLEM_LIST.md](PROBLEM_LIST.md):
* Add a new problem that you have just solved. The terminal will request you as follows:
```
Add new problem entry? (y/n): y
Problem name: Reverse Integer
Problem number: 15
Difficulty (easy/medium/hard): medium
Languages (cpp/python/java/all): cpp
Added problem 7 to ## 🟡Medium
Total problem: ...
Updated to file ...
```
* Add new languages if you need to solve a problem again. The terminal will request you as follows:
```
Add new problem entry? (y/n): n
Add new language for a problem? (y/n): y
Problem number: 7 
Language (cpp/python/java): python
Added python link for problem 7
```


