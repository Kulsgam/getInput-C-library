# getInput-C-library
A library to get input from the user similar to scanf

Note - this library might have bugs as I am new to programming, this is also horribly optimized.
To install the library in GCC move it to the following:

libinput.a = D:\mingw64\lib\gcc\x86_64-w64-mingw32\8.1.0

input.c and input.h = D:\mingw64\x86_64-w64-mingw32\include

# Usage
`getinput("<format_string>", <pointers to variables>);`

*format_strings*

  s - for strings
  
  c - for characters
  
  f - for floats
  
  i - for integers and shorts
  
  d - for doubles
  
  l - for longs
  
  L - for long longs
  
The format string should be within "{}" and after the format string you can specify how many characters you should read.

After the '}' you can mention the character/string which reading to stop and move to the next pointer to scan, this is called the separator.

Note - you should always use an & before when declaring a pointer, even if it is a string.

  eg - 
  
       getInput("{s4} ", &str); // This will scan 4 characters and stop when encountering a " "(space)
       
       getInput("{s4}", &str); // This will scan until '\n' or '\r' or EOF(if no separator is specified)
       
       getInput("{s} {c}", &str, &c); // This will scan a string first and then a character, stopping at a " :
       
                   // If the number of characters to scan in a string isn't defined, you cannot use arrays
                   
                   // It will dynamically allocate until the separator is reached
                   
                       // char* str = NULL; // CORRECT but NULL is needed
                       
                       // char str[5]; // WRONG
                       
                   // Likewise if you specify the number of characters to read in a string, you have to have an array without the number of elements
                      exceeding the character limit
                       
You can also specify how many characters should be read for other datatypes than strings too!
  
# Problems
This uses variadic arguments so if you get warnings, you can edit the `Input.c` file to have:

   #pragma GCC diagnostic push
   
   #pragma GCC diagnostic ignored "-Wformat-security" 
   
at the beginning and:

   #pragma GCC diagnostic pop
   
at the end of the file.
  
If you have library errors check this you can use `gcc -print-search-dirs` command to see the search directories GCC uses for libraries. You can also use
`-L` for search directories when compiling or linking.
