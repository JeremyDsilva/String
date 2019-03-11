# String Class

My implementation of a String class that mimics functanility of STL string. 

## Constructor 
<pre><code>String(); // default constructor  
String(const String &); // copy constructor  
String(const String& other, size_type pos, size_t len = npos); // substring constructor  
String(String &&); // move constructor  
String(const char *); // from c-string  
String(const char* s, size_t n); // from buffer  
String(size_t n, char c);// fill constructor  
String(const const_iterator first, const const_iterator second); // range constructor 
</code></pre>


## Equality operator
<pre><code>String & operator= (const String &); // copy assignment   
String & operator = (String &&); // move assignment
</code></pre>

## Destructor
<pre><code>~String();</code></pre>

## Iterators  
return iterator/const_iterator to the first character
<pre><code>iterator begin(); 
const_iterator begin() const;   
</code></pre>  
return iterator/const_iterator pointing to past-the-end character of the string  
<pre><code>iterator end();  
const_iterator end() const; 
</code></pre>  
returns const_iterator pointing to the first character / past-the-end character of the string
<pre><code>const_iterator cbegin() const;  
const_iterator cend() const; 
</code></pre>  
return reverse_iterator/const_reverse_iterator to the last character   
<pre><code>reverse_iterator rbegin();  
const_reverse_iterator rbegin() const; // return const_reverse_iterator to the last character
</code></pre>  
return reverse_iterator/const_reverse_iterator pointing to reverse past-the-end character of the string
<pre><code>reverse_iterator rend(); 
const_reverse_iterator rend() const; 
</code></pre>  
return const_reverse_iterator pointing to the last character / reverse past-the-end character of the string 
<pre><code>const_reverse_iterator crbegin() const; 
const_reverse_iterator crend() const; 
</code></pre>

## Comparision Operators
How its Comparision
<code><pre>
friend bool operator == (const String &, const String &);   
friend bool operator != (const String &, const String &);   
friend bool operator < (const String &, const String &);  
friend bool operator > (const String &, const String &);  
friend bool operator <= (const String &, const String &);  
friend bool operator >= (const String &, const String &);
</code></pre>

## Element access
Get character of string
<code><pre>const char & operator [] (size_type) const;
char & operator [] (size_type);
</code></pre>
Get character in string
<code><pre>const char & at(size_type) const;
char & at(size_type);
</code></pre>
Access first character
<code><pre>const char & front() const;
char & front();
</code></pre>
Access last character 
<code><pre>const char & back() const;
char & back();
</code></pre>

## Modifiers
Append to string
<code><pre>String & operator += (const String &); // string (1)
String & operator += (const char *); // c - string (2)
String & operator += (char); // char (3)
</code></pre>
Append to string 
<code><pre>String& append(const String& str); // string (1)
String& append(const String& str, size_type subpos, size_t sublen = npos); // substring (2)
String& append(const char* s); // c - string (3)
String& append(const char* s, size_t n); // buffer(4)
String& append(size_type n, char c); // fill(5)
String& append(const const_iterator first, const const_iterator second); // range(6)
</code></pre>
Append character to string
<code><pre>String & push_back(char);
</code></pre>
Insert into string
</code></pre>
<code><pre>String& insert(size_type pos, const String& other); 	// string(1)
String& insert(size_type pos, const String& other, size_type subpos, size_t sublen = npos); 	// substring(2)
String& insert(size_type pos, const char* other); // c - string(3)
String& insert(size_type pos, const char* s, size_t n); 	// buffer(4)
String& insert(size_type pos, size_t n, char c); 	// fill(5)
void insert(iterator p, size_t n, char c); 	// fill(6)
iterator insert(iterator p, char c); 	// single character(7)
void insert(iterator p, const const_iterator first, const const_iterator last); 	// range(8)  
</code></pre>
Erase characters from string 
<code><pre>String& erase(size_type pos = 0, size_t len = npos); 	// sequence(1)
iterator erase(const_iterator p); // character(2)
iterator erase(const_iterator first, const_iterator last); // range(3)  
</code></pre>
Replace portion of string
<code><pre>String& replace(size_type pos, size_t len, const String& other); // string(1)
String& replace(const_iterator i1, const_iterator i2, const String& other); // string(2)
String& replace(size_type pos, size_t len, const String& other, size_type subpos, size_t sublen = npos); // substring(3)
String& replace(size_type pos, size_t len, const char* s); // c - string(4)
String& replace(const_iterator i1, const_iterator i2, const char* other);  // c - string(5)
String& replace(size_type pos, size_t len, const char* other, size_t n); // buffer(6)
String& replace(const_iterator i1, const_iterator i2, const char* other, size_t n); // buffer(7)	
String& replace(size_type pos, size_t len, size_t n, char c); // fill(8)
String& replace(const_iterator i1, const_iterator i2, size_type n, char c); // fill(9)
String& replace(const_iterator i1, const_iterator i2, const_iterator first, const_iterator second); // range(10)  
</code></pre>
Swap string values
<code><pre>void swap(String &);
</code></pre>
Delete last character
<code><pre> String & pop_back();  
</code></pre>

## String Operation 
Get C string equivalent 
<code><pre>const char * c_str() const;
</code></pre>

<code><pre>size_t copy(char* s, size_t len, size_type pos = 0) const;
</code></pre>
Find content in string
<code><pre>size_type find(const String& other, size_type pos = 0) const; //string(1)
size_type find(const char* s, size_type pos = 0) const; // c - string(2)
size_type find(const char* s, size_type pos, size_type n) const; // buffer(3)
size_type find(char c, size_type pos = 0) const; // character(4)
 </code></pre>
Find last occurrence of content in string
<code><pre>size_type rfind(const String& other, size_type pos = npos) const; // string(1)
size_type rfind(const char* s, size_type pos = npos) const; // c - string(2)
size_type rfind(const char* s, size_type pos, size_t n) const; // buffer(3)
size_type rfind(char c, size_type pos = npos) const; // character(4)
</code></pre>
Find character in string 
<code><pre>size_type find_first_of(const String& other, size_type pos = 0) const; // string(1)
size_type find_first_of(const char* other, size_type pos = 0) const; 	// c - string(2)
size_type find_first_of(const char* other, size_type pos, size_t n) const; 	// buffer(3)
size_type find_first_of(char c, size_type pos = 0) const; // character(4)
</code></pre>
Find character in string from the end
<code><pre>size_type find_last_of(const String& other, size_type pos = String::npos) const; // string(1)
size_type find_last_of(const char* other, size_type pos = String::npos) const; // c - string(2)
size_type find_last_of(const char* other, size_type pos, size_t n) const; // buffer(3)
size_type find_last_of(char c, size_type pos = String::npos) const; 	// character(4)
</code></pre>
Find absence of character in string
<code><pre>size_type find_first_not_of(const String& other, size_type pos = 0) const; // string(1)
size_type find_first_not_of(const char* other, size_type pos = 0) const; 	// c - string(2)
size_type find_first_not_of(const char* other, size_type pos, size_t n) const; // buffer(3)
size_type find_first_not_of(char c, size_type pos = 0) const; // character(4)
</code></pre>
Find non-matching character in string from the end
<code><pre>size_type find_last_not_of(const String& other, size_type pos = String::npos) const; // string(1)
size_type find_last_not_of(const char* other, size_type pos = String::npos) const; // c - string(2)
size_type find_last_not_of(const char* other, size_type pos, size_t n) const; // buffer(3)
size_type find_last_not_of(char c, size_type pos = String::npos) const; // character(4)
</code></pre>
Generate substring
<code><pre>String substr(size_type pos = 0, size_t len = npos) const;
</code></pre>




