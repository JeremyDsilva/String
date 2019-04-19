#ifndef __JD_STRING__
#define __JD_STRING__

#include "macros.h"
#include <iostream>

_JD_BEGIN

class String {

public:
	using size_type = size_t; // size_type for positions
	static const size_t npos = -1;

private:

	char * _str = nullptr;   // c-string
	size_t _str_len = 0;     // length
	size_t _str_cap = 0;     // capacity

	size_t _increaseBy = 15;


// iterators

	struct String_iterator_type {
		char * first;
		const size_t * size;
		size_type pos;

		String_iterator_type
		(char* f = nullptr, const size_t * s = nullptr, size_type p = 0)
			: first(f), size(s), pos(p) {};
	};

public:

	class const_iterator {
	public:
		const_iterator();
		const_iterator(String_iterator_type p);

		const char & operator* () const;
		const char & operator[] (int) const;

		const_iterator& operator++ ();
		const_iterator operator++ (int);
		const_iterator & operator-- ();
		const_iterator operator-- (int);

		bool operator == (const const_iterator & rhs) const;
		bool operator != (const const_iterator & rhs) const;

		const_iterator operator+ (size_type i);
		const_iterator operator- (size_type i);

	protected:
		String_iterator_type current;

		char & retrieve() const;
		void _increment();
		void _decrement();
		char& _randomAccess(size_type i) const;
		void _add(const_iterator & toReturn, size_type i);
		void _subtract(const_iterator& toReturn, size_type i);

		friend class _JD String;
	};
	class iterator : public const_iterator {
		using _myBase = const_iterator;
		friend class _JD String;
	public:
		iterator();
		iterator(String_iterator_type p);

		char & operator* ();
		const char & operator* () const;
		char & operator[] (int);
		const char & operator[] (int) const;

		iterator& operator++ ();
		iterator operator++ (int);
		iterator & operator-- ();
		iterator operator-- (int);
		iterator operator+ (size_type i);
		iterator operator- (size_type i);

	};

	using const_pointer = const_iterator;
	using pointer = iterator;
	
	class const_reverse_iterator: public const_iterator {
		using _myBase = const_iterator;
		friend class _JD String;
	public:
		const_reverse_iterator();
		const_reverse_iterator(String_iterator_type p);

		const char & operator* () const;
		const char & operator[] (int) const;

		const_reverse_iterator& operator++ ();
		const_reverse_iterator operator++ (int);
		const_reverse_iterator & operator-- ();
		const_reverse_iterator operator-- (int);

		const_reverse_iterator operator+ (size_type i);
		const_reverse_iterator operator- (size_type i);

	protected:
		void _increment();
		void _decrement();
		void _add(const_reverse_iterator & toReturn, size_type i);
		void _subtract(const_reverse_iterator& toReturn, size_type i);

	};
	class reverse_iterator : public const_reverse_iterator {
		using _myBase = const_reverse_iterator;
		friend class _JD String;
	public:
		reverse_iterator();
		reverse_iterator(String_iterator_type p);

		char & operator* ();
		const char & operator* () const;
		char & operator[] (int);
		const char & operator[] (int) const;

		reverse_iterator& operator++ ();
		reverse_iterator operator++ (int);
		reverse_iterator & operator-- ();
		reverse_iterator operator-- (int);
		reverse_iterator operator+ (size_type i);
		reverse_iterator operator- (size_type i);

	};

	using const_reverse_pointer = const_reverse_iterator;
        using reverse_pointer = reverse_iterator;

	//	Constructor
public:
	String();
	String(const String &);
	String(const String& other, size_type pos, size_t len = npos);
	String(String &&);
	String(const char *);
	String(const char* s, size_t n);
	String(size_t n, char c);
	String(const const_iterator first, const const_iterator second);

	// Iterators
public:
	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;
	const_iterator cbegin() const;
	const_iterator cend() const;

	reverse_iterator rbegin();
	const_reverse_iterator rbegin() const;
	reverse_iterator rend();
	const_reverse_iterator rend() const;
	const_reverse_iterator crbegin() const;
	const_reverse_iterator crend() const;

private:
	inline String_iterator_type _ibegin() const;
	inline String::String_iterator_type _rbegin() const;
	inline String_iterator_type _end() const;
	size_t _getLength(const const_iterator first, const const_iterator second);
	
	//	Equality operator overload
public:
	String & operator= (const String &);
	String & operator = (String &&);

	//	Destructor
public:
	~String();


	//	Comparision Operators
public:
	friend bool operator == (const String &, const String &);
	friend bool operator != (const String &, const String &);
	friend bool operator < (const String &, const String &);
	friend bool operator > (const String &, const String &);
	friend bool operator <= (const String &, const String &);
	friend bool operator >= (const String &, const String &);

private:
	int _compare(const String & rhs) const;

	//	Element access
public:
	const char & operator [] (size_type) const;
	char & operator [] (size_type);
	const char & at(size_type) const;
	char & at(size_type);
	const char & front() const;
	char & front();
	const char & back() const;
	char & back();

	//	Modifiers
public:
	String & operator += (const String &); // string (1)
	String & operator += (const char *); // c - string (2)
	String & operator += (char); // char (3)

	String& append(const String& str); // string (1)
	String& append(const String& str, size_type subpos, size_t sublen = npos); // substring (2)
	String& append(const char* s); // c - string (3)
	String& append(const char* s, size_t n); // buffer(4)
	String& append(size_type n, char c); // fill(5)
	String& append(const const_iterator first, const const_iterator second); // range(6)

	String & push_back(char);

	String& insert(size_type pos, const String& other); 	// string(1)
	String& insert(size_type pos, const String& other, size_type subpos, size_t sublen = npos); 	// substring(2)
	String& insert(size_type pos, const char* other); // c - string(3)
	String& insert(size_type pos, const char* s, size_t n); 	// buffer(4)
	String& insert(size_type pos, size_t n, char c); 	// fill(5)
	void insert(iterator p, size_t n, char c); 	// fill(6)
	iterator insert(iterator p, char c); 	// single character(7)
	void insert(iterator p, const const_iterator first, const const_iterator last); 	// range(8)

	String& erase(size_type pos = 0, size_t len = npos); 	// sequence(1)
	iterator erase(const_iterator p); // character(2)
	iterator erase(const_iterator first, const_iterator last); // range(3)

	String& replace(size_type pos, size_t len, const String& other); // string(1)
	String& replace(const_iterator i1, const_iterator i2, const String& other); // string(2)
	String& replace(size_type pos, size_t len, const String& other, size_type subpos, size_t sublen = npos); // substring(3)
	String& replace(size_type pos, size_t len, const char* s); // c - string(4)
	String& replace(const_iterator i1, const_iterator i2, const char* other);  // c - string(5)
	String& replace(size_type pos, size_t len, const char* other, size_t n); // buffer(6)
	String& replace(const_iterator i1, const_iterator i2, const char* other, size_t n); // buffer(7)	
	String& replace(size_type pos, size_t len, size_t n, char c); // fill(8)
	String& replace(const_iterator i1, const_iterator i2, size_type n, char c); // fill(9)
	String& replace(const_iterator i1, const_iterator i2, const_iterator first, const_iterator second); // range(10)

	void swap(String &);

	String & pop_back();

private:
	inline void _append(const char *);
	void _append(const char *, size_t n);
	void _insert_str(size_type pos, const char * other);
	void _insert_str(size_type pos, const char * other, size_t n);
	void _substr(char * & buffer, const char * other, size_type pos = 0, size_t len = npos) const;
	void _erase(size_type pos, size_t size);
	void _replace(size_type pos, size_t len, const char * other, size_t n);
	size_t _getLength(const String & str, size_type pos, size_t len = npos) const;

	// String Operations
public:
	const char * c_str() const;

	size_t copy(char* s, size_t len, size_type pos = 0) const;

	size_type find(const String& other, size_type pos = 0) const; //string(1)
	size_type find(const char* s, size_type pos = 0) const; // c - string(2)
	size_type find(const char* s, size_type pos, size_type n) const; // buffer(3)
	size_type find(char c, size_type pos = 0) const; // character(4)

	size_type rfind(const String& other, size_type pos = npos) const; // string(1)
	size_type rfind(const char* s, size_type pos = npos) const; // c - string(2)
	size_type rfind(const char* s, size_type pos, size_t n) const; // buffer(3)
	size_type rfind(char c, size_type pos = npos) const; // character(4)

	size_type find_first_of(const String& other, size_type pos = 0) const; // string(1)
	size_type find_first_of(const char* other, size_type pos = 0) const; 	// c - string(2)
	size_type find_first_of(const char* other, size_type pos, size_t n) const; 	// buffer(3)
	size_type find_first_of(char c, size_type pos = 0) const; // character(4)

	size_type find_last_of(const String& other, size_type pos = String::npos) const; // string(1)
	size_type find_last_of(const char* other, size_type pos = String::npos) const; // c - string(2)
	size_type find_last_of(const char* other, size_type pos, size_t n) const; // buffer(3)
	size_type find_last_of(char c, size_type pos = String::npos) const; 	// character(4)

	size_type find_first_not_of(const String& other, size_type pos = 0) const; // string(1)
	size_type find_first_not_of(const char* other, size_type pos = 0) const; 	// c - string(2)
	size_type find_first_not_of(const char* other, size_type pos, size_t n) const; // buffer(3)
	size_type find_first_not_of(char c, size_type pos = 0) const; // character(4)

	size_type find_last_not_of(const String& other, size_type pos = String::npos) const; // string(1)
	size_type find_last_not_of(const char* other, size_type pos = String::npos) const; // c - string(2)
	size_type find_last_not_of(const char* other, size_type pos, size_t n) const; // buffer(3)
	size_type find_last_not_of(char c, size_type pos = String::npos) const; // character(4)

	String substr(size_type pos = 0, size_t len = npos) const;
private:
	size_type _find(const char * other, size_t len, size_type pos) const;
	size_type _rfind(const char * other, size_t len, size_type pos) const;
	bool _find_compare(const char * other, size_t len, size_type pos) const;
	size_type _find_first_of(const char * other, size_t len, size_type pos, bool isTrue) const;
	size_type _find_last_of(const char * other, size_t len, size_type pos, bool isTrue) const;
	bool _find_of_compare(const char *other, size_t len, size_type pos, bool isTrue) const;

	// Data Management
public:
	size_t length() const;
	inline size_t size() const;
	size_t max_size() const;
	void resize(size_t n);
	void resize(size_type n, char c);
	size_t capacity() const;
	void reserve(size_t n = 0);
	void clear();
	bool empty() const;
	void shrink_to_fit();

private:
	void _setLength(const size_t len);
	void _setCapacity(const size_t cap);
	void _increaseCapacity(const size_t cap);
	void _decreaseCapacity(const size_t cap);
	void _alloc_cstring(char * &buffer,const size_t n) const;
	void _alloc_cstring(char * &buffer,const size_t n, char c) const;
	void _alloc_cstring(char * &buffer,const size_t n, const const_iterator i1, const const_iterator i2) const;
	void _fill_str(char * other, const size_t len, size_type pos, char c) const;
	void _clear_str(const size_type pos);

};

void swap(String& x, String& y);

String operator+ (const String& lhs, const String& rhs);
String operator+ (const String& lhs, const char*   rhs);
String operator+ (const char*   lhs, const String& rhs);
String operator+ (const String& lhs, char rhs);
String operator+ (char lhs, const String& rhs);


std::ostream& operator<< (std::ostream& os, const _JD String& str);

std::istream& operator>> (std::istream& is, _JD String& str);

std::istream& getline(std::istream& is, _JD String& str, char delim);

std::istream& getline(std::istream& is, _JD String& str);

_JD_END


#endif // !_JD_STRING
