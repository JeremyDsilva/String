#include "String.h"
#include "macros.h"
#include <cstring>
#include <exception>

_JD_BEGIN

using size_type = size_t;

/*
	Constructors
*/

String::String() {
	_setCapacity(0);
	_setLength(0);
}

String::String(const String & other)  {
	_append(other._str, other._str_len);
}

String::String(const String & other, size_type pos, size_t len) {
	append(other._str, pos, len);
}

String::String(String && other) {
	*this = std::move(other);
}

String::String(const char * copy) {
	_append(copy);
}

String::String(const char * s, size_t n) {
	append(s, 0, n);
}

String::String(size_t n, char c) {
	append(n, c);
}

String::String(const String::const_iterator first, const String::const_iterator second) {
	append(first, second);
}

/*
	Equality operator overload
*/

String & String::operator= (const String & other) {
	if (this != &other) {
		_setLength(0);
		_append(other._str, other._str_len);
	}
	return *this;
}

String & String::operator = (String && other) {
	if (this != &other) {
		safe_delete(_str);
		_str = other._str;
		_str_len = other._str_len;
		_str_cap = other._str_cap;
		other._str = nullptr;
		other._str_len = 0;
		other._str_cap = 0;
	}
	return *this;
}

/*
	Destructor
*/

String::~String() {
	safe_delete(_str);
	_str_len = 0;
	_str_cap = 0;
	_increaseBy = 0;
}

/*
	Comparision Operators
*/

bool operator == (const String & lhs, const String & rhs) {
	return lhs._compare(rhs) == 0;
}

bool operator != (const String & lhs, const String & rhs) {
	return lhs._compare(rhs) != 0;
}

bool operator < (const String & lhs, const String & rhs) {
	return lhs._compare(rhs) < 0;
}

bool operator > (const String & lhs, const String & rhs) {
	return lhs._compare(rhs) > 0;
}

bool operator <= (const String & lhs, const String & rhs) {
	return lhs._compare(rhs) <= 0;
}

bool operator >= (const String & lhs, const String & rhs) {
	return lhs._compare(rhs) >= 0;
}

// private helper comparision operators functions

int String::_compare(const String & rhs) const {

	if (_str_len < rhs._str_len)
		return 1;
	else if (_str_len > rhs._str_len)
		return -1;

	return strcmp(_str, rhs._str);
}

/*
	Element access
*/

const char & String::operator [] (size_type i) const {
	return *(_str + i);
}

char & String::operator [] (size_type i) {
	return *(_str + i);
}

const char & String::at(size_type i) const {
	if (i < 0 || _str_len <= i)
		throw;
	return operator[](i);
}

char & String::at(size_type i) {
	if (i < 0 || _str_len <= i)
		throw;
	return operator[](i);
}

const char & String::front() const {
	return operator[](0);
}

char & String::front() {
	return operator[](0);
}

const char & String::back() const {
	return operator[](_str_len - 1);
}

char & String::back() {
	return operator[](_str_len - 1);
}

/*
	Modifiers
*/

// operator +=

String & String::operator += (const String & s) {
	_append(s._str, s._str_len);
	return *this;
}

String & String::operator += (const char * s) {
	_append(s);
	return *this;
}

String & String::operator += (char c) {
	_append(&c, 1);
	return *this;
}

// append

String & String::append(const String & other)
{
	_append(other._str, other._str_len);
	return *this;
}

String & String::append(const String & other, size_type subpos, size_t sublen)
{
	sublen = _getLength(other, subpos, sublen);
	char * buffer = nullptr;
	_substr(buffer, other._str, subpos, sublen);
	_append(buffer, sublen);
	safe_delete(buffer);
	return *this;
}

String & String::append(const char * other)
{
	_append(other);
	return *this;
}

String & String::append(const char * s, size_t n)
{
	char * buffer = nullptr;
	_substr(buffer, s, 0, n);
	_append(buffer, n);
	safe_delete(buffer);
	return *this;
}

String & String::append(size_type n, char c)
{
	char * buffer = nullptr;
	_alloc_cstring(buffer, n, c);
	_append(buffer, n);
	safe_delete(buffer);
	return *this;
}

String & String::append(const String::const_iterator first, const String::const_iterator second)
{
	const size_t n = _getLength(first, second);
	if (n != 0) {	// if length is not zero then _append 
		char * buffer = nullptr;
		_alloc_cstring(buffer, n, first, second);
		_append(buffer, n);
		safe_delete(buffer);
	}
	return *this;
}

// push_back

String & String::push_back(char c) {
	_append(&c, 1);
	return *this;
}

// insert

String& String::insert(size_type pos, const String& other) {
	_insert_str(pos, other._str, other._str_len);
	return *this;
}

String & String::insert(size_type pos, const String & other, size_type subpos, size_t sublen)
{
	sublen = _getLength(other, subpos, sublen);
	char * buffer = nullptr;
	_substr(buffer, other._str, subpos, sublen);
	_insert_str(pos, buffer, sublen);
	safe_delete(buffer);
	return *this;
}

String& String::insert(size_type pos, const char* other) {
	_insert_str(pos, other);
	return *this;
}

String & String::insert(size_type pos, const char * s, size_t n)
{
	char * buffer = nullptr;
	_substr(buffer, s, 0, n);
	_insert_str(pos, buffer, n);
	safe_delete(buffer);
	return *this;
}

String & String::insert(size_type pos, size_t n, char c)
{
	char * buffer = nullptr;
	_alloc_cstring(buffer, n, c);
	_insert_str(pos, buffer, n);
	safe_delete(buffer);
	return *this;
}

void String::insert(iterator p, size_t n, char c)
{
	char * buffer = nullptr;
	_alloc_cstring(buffer, n, c);
	_insert_str(p.current.pos, buffer, n);
	safe_delete(buffer);
}

String::iterator String::insert(String::iterator p, char c)
{
	_insert_str(p.current.pos, &c, 1);
	return p;
}

void String::insert(String::iterator p, const String::const_iterator first, const String::const_iterator second)
{
	const size_t n = _getLength(first, second);
	if (n == 0) 	// if length is zero then do nothing
		return;
	char * buffer = nullptr;
	_alloc_cstring(buffer, n, first, second);
	_insert_str(p.current.pos, buffer, n);
	safe_delete(buffer);
}

// erase

String& String::erase(size_type pos, size_t len) { 	// sequence(1)
	_erase(pos, len);
	return *this;
}

String::iterator String::erase(String::const_iterator p) { // character(2)
	_erase(p.current.pos, 1);
	return p.current;
}

String::iterator String::erase(String::const_iterator first, String::const_iterator last) { // range(3)
	_erase(first.current.pos, _getLength(first, last));
	return first.current;
}

// replace

String& String::replace(size_type pos, size_t len, const String& other) {
	_replace(pos, len, other._str, other._str_len);
	return *this;
}

String& String::replace(String::const_iterator i1, String::const_iterator i2, const String& other) {
	replace(i1.current.pos, _getLength(i1, i2), other._str, other._str_len);
	return *this;
}

String& String::replace(size_type pos, size_t len, const String& other, size_type subpos, size_t sublen) {
	sublen = _getLength(other, subpos, sublen);
	char * buffer = nullptr;
	_substr(buffer, other._str, subpos, sublen);
	_replace(pos, len, buffer, strlen(buffer));
	safe_delete(buffer);
	return *this;
}

String& String::replace(size_type pos, size_t len, const char* s) {
	_replace(pos, len, s, strlen(s));
	return *this;
}

String& String::replace(const_iterator i1, const_iterator i2, const char* other) {
	_replace(i1.current.pos, _getLength(i1, i2), other, strlen(other));
	return *this;
}

String& String::replace(size_type pos, size_t len, const char* other, size_t n) {
	_replace(pos, len, other, n);
	return *this;
}

String& String::replace(const_iterator i1, const_iterator i2, const char* other, size_t n) {
	_replace(i1.current.pos, _getLength(i1, i2), other, n);
	return *this;
}

String& String::replace(size_type pos, size_t len, size_t n, char c) {
	char * buffer = nullptr;
	_alloc_cstring(buffer, n, c);
	_replace(pos, len, buffer, n);
	safe_delete(buffer);
	return *this;
}

String& String::replace(const_iterator i1, const_iterator i2, size_type n, char c) {
	char * buffer = nullptr;
	_alloc_cstring(buffer, n, c);
	_replace(i1.current.pos, _getLength(i1, i2), buffer, n);
	safe_delete(buffer);
	return *this;
}

// swap

void String::swap(String & other) {
	String temp = std::move(*this);
	*this = std::move(other);
	other = std::move(temp);
}

// pop_back

String & String::pop_back() {
	_erase((end() - 1).current.pos, 1);
	return *this;
}

String& String::replace(String::const_iterator i1, String::const_iterator i2,
	String::const_iterator first, String::const_iterator second) {

	const size_t n = _getLength(first, second);
	char * buffer = nullptr;
	_alloc_cstring(buffer, n, first, second);
	_replace(i1.current.pos, _getLength(i1, i2), buffer, n);
	safe_delete(buffer);
	return *this;
}

// private helper string modifier functions

inline void String::_append(const char * other) {
	return _append(other, strlen(other));
}

void String::_append(const char * other, size_t n)
{
	if (!other || n == 0) // if other is null or size is 0 do nothing
		return;  
	_increaseCapacity(_str_len + n);
	size_type i = 0;
	for (; i < n; ++i)
		operator[](_str_len + i) = other[i];
	operator[](_str_len + i) = '\0';
	_setLength(_str_len + n);
}

void String::_insert_str(size_type pos, const char * other) {
	if (other != nullptr)
		_insert_str(pos, other, strlen(other));
}

void String::_insert_str(size_type pos, const char * other, size_t n)
{
	if (pos == _str_len) // if pos is _str_len then append
		return _append(other, n);

	if (pos > _str_len) {  // if pos is bigger than size then throw
		throw;

	}

	if (n == 0)	// if other is null or empty then do nothing
		return;

	_increaseCapacity(_str_len + n); // increase capacity to hold new length

	if (_str) {
		char * buffer = nullptr;
		_substr(buffer, _str, pos, _str_len);   // store third part of string
		_clear_str(pos);  // string contains only first part
		_append(other, n); // append second (new) part to string
		_append(buffer, strlen(buffer)); // append thrid part to string
		safe_delete(buffer); // freeMemory used
	}
	else
		_append(other, n); // cat other to _str
}

void String::_substr(char * & buffer, const char * other, size_type pos, size_t len) const
{

	if (other == nullptr) {
		throw;
	}
	_alloc_cstring(buffer, len);
	for (size_type i = 0; i < len; ++i)
		buffer[i] = other[pos + i];
}

void String::_erase(size_type pos, size_t len)
{
	len = _getLength(*this, pos, len);
	for (size_t i = pos+ len; i < _str_len; ++i) 
		operator[](i - len) = operator[](i);
	_clear_str(_str_len - len); // only first part of string
}

void String::_replace(size_type pos, size_t len, const char * other, size_t n)
{
	len = _getLength(*this, pos, len);						  // get length
	char * buffer = nullptr;
	_substr(buffer, _str, pos + len, _str_len);   // store third part of string
	_clear_str(pos);     									  // first part of string
	char * replace_buffer = nullptr;
	_substr(replace_buffer, other, 0, n);				  // store second part of string 
	_append(replace_buffer);									  // append second part of string
	_append(buffer); 									  // append third part of string
	// free memory 
	safe_delete(replace_buffer);
	safe_delete(buffer);
}

size_t String::_getLength(const String & str, size_type pos, size_t len) const {
	if (len == npos)
		len = _str_len - pos;

	if (pos + len > str._str_len) {
		throw;	
	}
	return len;
}

/*
	String Operations
*/

// c_string

const char * String::c_str() const {
	return _str;
}

// copy

size_t String::copy(char* s, size_t len, size_type pos) const {
	if (!s)
		throw;
	len = _getLength(*this, pos, len);
	for (size_type i = 0; i < len; ++i)
		*(s + i) = operator[](pos + i);
	return len;
}

// find

size_t String::find(const String& other, size_type pos) const { //string(1)
	return _find(other._str, other._str_len, pos);
}

size_t String::find(const char* s, size_type pos) const { // c - string(2)
	return _find(s, strlen(s), pos);
}

size_t String::find(const char* s, size_type pos, size_type n) const { // buffer(3)
	return _find(s, n, pos);
}

size_t String::find(char c, size_type pos) const { // character(4)
	return _find(&c, 1, pos);
}

// reverse find

size_t String::rfind(const String& other, size_type pos) const { // string(1)
	return _rfind(other._str, other._str_len, pos);
}

size_t String::rfind(const char* s, size_type pos) const { // c - string(2)
	return  _rfind(s, strlen(s), pos);
}

size_t String::rfind(const char* s, size_type pos, size_t n) const { // buffer(3)
	return _rfind(s, n, pos);
}

size_t String::rfind(char c, size_type pos) const { // character(4)
	return _rfind(&c, 1, pos);
}

// find_first_of 

size_t String::find_first_of(const String& other, size_type pos) const { // string(1)
	return _find_first_of(other._str, other._str_len, pos, true);
}

size_t String::find_first_of(const char* other, size_type pos) const { // c - string(2)
	return _find_first_of(other, strlen(other), pos, true);
}

size_t String::find_first_of(const char* other, size_type pos, size_t n) const { // buffer(3)
	return _find_first_of(other, n, pos, true);
}

size_t String::find_first_of(char c, size_type pos) const { // character(4)
	return _find_first_of(&c, 1, pos, true);
}

// find_last_of

size_t String::find_last_of(const String& other, size_type pos) const { // string(1)
	return _find_last_of(other._str, other._str_len, pos, true);
}

size_t String::find_last_of(const char* other, size_type pos) const { // c - string(2)
	return _find_last_of(other, strlen(other), pos, true);
}

size_t String::find_last_of(const char* other, size_type pos, size_t n) const { // buffer(3)
	return _find_last_of(other, n, pos, true);
}

size_t String::find_last_of(char c, size_type pos) const { // character(4)
	return _find_last_of(&c, 1, pos, true);
}

// find_first_not_of

size_t String::find_first_not_of(const String& other, size_type pos) const { // string(1)
	return _find_first_of(other._str, other._str_len, pos, false);
}

size_t String::find_first_not_of(const char* other, size_type pos) const { // c - string(2)
	return _find_first_of(other, strlen(other), pos, false);
}

size_t String::find_first_not_of(const char* other, size_type pos, size_t n) const { // buffer(3)
	return _find_first_of(other, n, pos, false);
}

size_t String::find_first_not_of(char c, size_type pos) const { // character(4)
	return _find_first_of(&c, 1, pos, false);
}

// find_last_not_of

size_t String::find_last_not_of(const String& other, size_type pos) const { // string(1)
	return _find_last_of(other._str, other._str_len, pos, false);
}

size_t String::find_last_not_of(const char* other, size_type pos) const { // c - string(2)
	return _find_last_of(other, strlen(other), pos, false);
}

size_t String::find_last_not_of(const char* other, size_type pos, size_t n) const { // buffer(3)
	return _find_last_of(other, n, pos, false);
}

size_t String::find_last_not_of(char c, size_type pos) const { // character(4)
	return _find_last_of(&c, 1, pos, false);
}

// substring 

String String::substr(size_type pos, size_t len) const
{
	len = _getLength(*this, pos, len);
	char * buffer = nullptr;
	_substr(buffer, _str, pos, len);
	String toReturn(buffer);
	safe_delete(buffer);
	return toReturn;
}

// private helper String Operations functions

size_t String::_find(const char * other, size_t len, size_type pos) const {
	size_t toReturn = npos;
	if (pos == npos)
		pos = _str_len - 1;
	for (; pos <= _str_len - len; ++pos)
		if (operator[](pos) == *other && _find_compare(other, len, pos)) {
			toReturn = pos;
			break;
		}
	return toReturn;
}

size_t String::_rfind(const char * other, size_t len, size_type pos) const {
	size_t toReturn = npos;
	if (pos == npos || pos + len > _str_len + 1)
		pos = _str_len - len + 1;

	for (int i = pos; 0 <= i; --i)
		if (operator[](i) == *other  && _find_compare(other, len, i)) {
			toReturn = i;
			break;
		}
	return toReturn;
}

bool String::_find_compare(const char * other, size_t len, size_type pos) const {
	for (size_type i = 1; i < len; ++i)
		if (operator[](pos + i) != *(other + i))
			return false;
	return true;
}

size_t String::_find_first_of(const char * other, size_t len, size_type pos, bool isTrue) const {
	size_t toReturn = npos;
	if (pos == npos)
		pos = _str_len - 1;

	for (; pos < _str_len; ++pos)
		if (_find_of_compare(other, len, pos, isTrue)) {
			toReturn = pos;
			break;
		}
	return toReturn;
}

size_t String::_find_last_of(const char * other, size_t len, size_type pos, bool isTrue) const {
	size_t toReturn = npos;
	if (pos == npos)
		pos = _str_len - 1;

	for (int i = pos; 0 <= i; --i)
		if (_find_of_compare(other, len, i, isTrue)) {
			toReturn = i;
			break;
		}
	return toReturn;
}

bool String::_find_of_compare(const char *other, size_t len, size_type pos, bool isTrue) const {
	for (size_type i = 0; i < len; ++i)
		if (operator[](pos) == *(other + i))
			return isTrue;                  // isTrue ? true : false;
	return !isTrue;                              //  isTrue ? false : true;
}

/*
	Data Management
*/

size_t String::length() const {
	return _str_len;
}

inline size_t String::size() const {
	return length();
}

size_t String::max_size() const {
	return String::npos -1;
}

void String::resize(size_t n) {
	if (_str_len == n) return; // length  already allocated
	if (_str_len < n) {
		_setLength(n);
		return;
	}
	_clear_str(n); // clear string from n onwards
}

void String::resize(size_type n, char c) {
	if (_str_len == n) return; // length  already allocated
	if (_str_len < n) {
		size_type pos = _str_len;
		_setLength(n);
		_fill_str(_str, _str_len, pos, c);
		return;
	}
	_clear_str(n); // clear string from n onwards
}

size_t String::capacity() const {
	return _str_cap;
}

void String::reserve(size_t n) {
	if (_str_cap == n) return;
	if (_str_cap < n) {
		_setCapacity(n);
		return;
	}
	// reduce size only if capacity is twice the size of length
	if (_str_cap / 2 > _str_len) {
		_decreaseCapacity(_str_cap / 2);
	}
}

void String::clear() {
	_clear_str(0);
}

bool String::empty() const {
	return _str_len ? false : true;
}

void String::shrink_to_fit() {
	_decreaseCapacity(_str_len);
}

// private data management functions

void String::_setLength(const size_t len) {
	if (_str_len > len)  // space already allocated
		_clear_str(len);
	else if (_str_cap < len)  // length is greater than capacity 
		_increaseCapacity(len); 	    // allocate memory, increase capacity       
	_str_len = len;
}

void String::_setCapacity(const size_t cap) {
	if (_str_cap == cap && _str) // capacity set already
		return;
	if (cap < _str_len) // capacity less than length
		return;
	_str_cap = cap; // set capacity 

	char * buffer = _str;	 // store _str
	_str = nullptr; // set str nullptr
	_alloc_cstring(_str, _str_cap); // allocate memory
	if (buffer) { // if temp_str is not null then strcpy
		for (size_type i = 0; i < _str_len; ++i)
			operator[](i) = buffer[i];
		operator[](_str_len) = '\0';
	}
	safe_delete(buffer);
}

void String::_increaseCapacity(const size_t n) {
	if (_str_cap > n && _str)
		return;
	// Increase Capacity Calculation
	size_t cap = _str_cap;
	while (cap <= n)
		cap += _increaseBy;
	_increaseBy++;

	_setCapacity(cap); // increase Capacity
}

void String::_decreaseCapacity(const size_t cap) {
	if (_str_cap < cap)
		return; // if capacity greater than current capacity then do nothing
	// Algrorith to decrease increase by 
	if (_increaseBy > 15)
		--_increaseBy;
	_setCapacity(cap);
}

void String::_alloc_cstring(char * &buffer,  const size_t n)  const
{
	if (buffer)
		throw;
	buffer = new char[n + 1]();
}

void String::_alloc_cstring(char * &buffer, const size_t n, char c) const
{
	 _alloc_cstring(buffer, n);
	_fill_str(buffer, n, 0, c);
}

void String::_alloc_cstring(char * &buffer, const size_t n, const String::const_iterator i1, const String::const_iterator i2) const {
	_alloc_cstring(buffer, n);
	String::const_iterator begin = i1;
	for (size_type i = 0; i < n; ++i)
		buffer[i] = *begin++;
}

void String::_fill_str(char * other, const size_t len, const size_type pos, char c) const
{
	size_type begin = pos;
	while (begin != len)
		other[begin++] = c;
	other[begin] = '\0';
}

void String::_clear_str(const size_type pos) {
	_fill_str(_str, _str_len, pos, '\0');
	_str_len = pos;
}

/*
	String iterator
*/

String::iterator String::begin() {
	return _ibegin();
}

String::const_iterator String::begin() const {
	return _ibegin();
}

String::iterator String::end() {
	return _end();
}

String::const_iterator String::end() const {
	return _end();
}

String::const_iterator String::cbegin() const {
	return _ibegin();
}

String::const_iterator String::cend() const {
	return _end();
}

// Not tested -> currently private

String::reverse_iterator String::rbegin() {
	return _rbegin();
}
String::const_reverse_iterator String::rbegin() const {
	return _rbegin();
}

String::reverse_iterator String::rend() {
	return _end();
}

String::const_reverse_iterator String::rend() const {
	return _end();
}

String::const_reverse_iterator String::crbegin() const {
	return _rbegin();
}

String::const_reverse_iterator String::crend() const {
	return _end();
}

// private string iterator 

inline String::String_iterator_type String::_ibegin() const {
	return String_iterator_type(_str, &_str_len, 0);
}

inline String::String_iterator_type String::_end() const {
	return String_iterator_type(_str, &_str_len, _str_len);
}

inline String::String_iterator_type String::_rbegin() const {
	return String_iterator_type(_str, &_str_len, _str_len-1);
}

size_t String::_getLength(const String::const_iterator first, const String::const_iterator second) {
	if (first.current.first != second.current.first) {
		throw;
	}
	if (first.current.pos > second.current.pos) {
		throw;
	}
	return second.current.pos - first.current.pos;
}

/*
	const_iterator
*/

String::const_iterator::const_iterator() {}

String::const_iterator::const_iterator(String_iterator_type p) : current(p) {}

const char & String::const_iterator::operator[](int i) const
{
	return _randomAccess(i);
}

const char & String::const_iterator::operator* () const {
	return retrieve();
}

String::const_iterator& String::const_iterator::operator++ () {
	_increment();
	return *this;
}

String::const_iterator String::const_iterator::operator++ (int) {
	const_iterator old = *this;
	_increment();
	return old;
}

String::const_iterator & String::const_iterator::operator-- () {
	_decrement();
	return *this;
}

String::const_iterator String::const_iterator::operator-- (int) {
	const_iterator old = *this;
	_decrement();
	return old;
}

bool String::const_iterator::operator == (const String::const_iterator & rhs) const {
	return current.first == rhs.current.first && current.pos == rhs.current.pos;
}

bool String::const_iterator::operator != (const String::const_iterator & rhs) const {
	return !(*this == rhs);
}

String::const_iterator String::const_iterator::operator+ (size_type i) {
	const_iterator toReturn;
	_add(toReturn, i);
	return toReturn;
}

String::const_iterator String::const_iterator::operator- (size_type i) {
	const_iterator toReturn;
	_subtract(toReturn, i);
	return toReturn;
}

// protected const_iterator function 

char & String::const_iterator::retrieve() const {
	return *(current.first + current.pos);
}

void String::const_iterator::_increment() {
	if (current.pos > *current.size) {
		throw;	
	}
	++current.pos;
}

void String::const_iterator::_decrement() {
	if (current.pos == 0) {
		throw;
	}
	--current.pos;
}

char& String::const_iterator::_randomAccess(size_type i) const
{
	if (i < 0 || i >= *current.size) {
		throw;
	}
	return *(current.first + i);
}

void String::const_iterator::_add(const_iterator & toReturn, size_type i) {
	if (current.pos + i > *current.size) { // beyond end
		throw;
	}
	toReturn = *this;
	toReturn.current.pos += i;
}

void String::const_iterator::_subtract(const_iterator& toReturn, size_type i) {
	if (current.pos < i) { // if pos will be less than zero
		throw;
	}
	toReturn = *this;
	toReturn.current.pos -= i;
}

/*
	iterator
*/

String::iterator::iterator() : _myBase() {}

String::iterator::iterator(String_iterator_type p) : _myBase(p) {}

char & String::iterator::operator[](int i)
{
	return _myBase::_randomAccess(i);
}

const char & String::iterator::operator[](int i) const
{
	return _myBase::operator[](i);
}

char & String::iterator::operator* () {
	return _myBase::retrieve();
}

const char & String::iterator::operator* () const {
	return _myBase::operator*();
}

String::iterator& String::iterator::operator++ () {
	_myBase::_increment();
	return *this;
}

String::iterator String::iterator::operator++ (int) {
	iterator old = *this;
	_myBase::_increment();
	return old;
}

String::iterator & String::iterator::operator-- () {
	_myBase::_decrement();
	return *this;
}

String::iterator String::iterator::operator-- (int) {
	iterator old = *this;
	_myBase::_decrement();
	return old;
}

String::iterator String::iterator::operator+ (size_type i) {
	iterator toReturn;
	_add(toReturn, i);
	return toReturn;
}

String::iterator String::iterator::operator- (size_type i) {
	iterator toReturn;
	_subtract(toReturn, i);
	return toReturn;
}

/*
	const_reverse_iterator Private
*/

String::const_reverse_iterator::const_reverse_iterator() : _myBase() {}

String::const_reverse_iterator::const_reverse_iterator(String_iterator_type p) : _myBase(p) {}

const char & String::const_reverse_iterator::operator[](int i) const
{
	return _myBase::operator[](i);
}

const char & String::const_reverse_iterator::operator* () const {
	return _myBase::operator*();
}

String::const_reverse_iterator& String::const_reverse_iterator::operator++ () {
	_increment();
	return *this;
}

String::const_reverse_iterator String::const_reverse_iterator::operator++ (int) {
	const_reverse_iterator old = *this;
	_increment();
	return old;
}

String::const_reverse_iterator & String::const_reverse_iterator::operator-- () {
	_decrement();
	return *this;
}

String::const_reverse_iterator String::const_reverse_iterator::operator-- (int) {
	const_reverse_iterator old = *this;
	_decrement();
	return old;
}

String::const_reverse_iterator String::const_reverse_iterator::operator+ (size_type i) {
	const_reverse_iterator toReturn;
	_add(toReturn, i);
	return toReturn;
}

String::const_reverse_iterator String::const_reverse_iterator::operator- (size_type i) {
	const_reverse_iterator toReturn;
	_subtract(toReturn, i);
	return toReturn;
}

// protected functions

void String::const_reverse_iterator::_increment() {
	if (_myBase::current.pos == 0) {
		_myBase::current.pos = *_myBase::current.size;
		return;
	}
	else if (current.pos == *current.size) {
		throw;
	}
	_myBase::_decrement();
}

void String::const_reverse_iterator::_decrement() {
	if (current.pos == *_myBase::current.size) {
		_myBase::current.pos = 0;
		return;
	}
	if (current.pos + 1 == *_myBase::current.size) {
		throw;
	}
	_myBase::_increment();
}

void String::const_reverse_iterator::_add(const_reverse_iterator & toReturn, size_type i) {
	if (current.pos == *_myBase::current.size && !i) { // at the end and i not equal to 0
		throw;
	} 
	if (current.pos == i - 1) { // reached end 
		_myBase::current.pos = *_myBase::current.size;
		return;
	}
	else if (current.pos < i -1) // moved past end
		throw;

	toReturn = *this;
	toReturn.current.pos -= i;
}

void String::const_reverse_iterator::_subtract(const_reverse_iterator& toReturn, size_type i) {
	if (*_myBase::current.size <= _myBase::current.pos + i) // moved past reverse first element 
		throw;

	toReturn = *this;
	toReturn.current.pos += i;
}

/*
	Reverse iterator
*/

String::reverse_iterator::reverse_iterator() : _myBase() {}

String::reverse_iterator::reverse_iterator(String_iterator_type p) : _myBase(p) {}

char & String::reverse_iterator::operator[](int i)
{
	return _myBase::_randomAccess(i);
}

const char & String::reverse_iterator::operator[](int i) const
{
	return _myBase::operator[](i);
}

char & String::reverse_iterator::operator* () {
	return _myBase::retrieve();
}

const char & String::reverse_iterator::operator* () const {
	return _myBase::operator*();
}

String::reverse_iterator& String::reverse_iterator::operator++ () {
	_myBase::_increment();
	return *this;
}

String::reverse_iterator String::reverse_iterator::operator++ (int) {
	reverse_iterator old = *this;
	_myBase::_increment();
	return old;
}

String::reverse_iterator & String::reverse_iterator::operator-- () {
	_myBase::_decrement();
	return *this;
}

String::reverse_iterator String::reverse_iterator::operator-- (int) {
	reverse_iterator old = *this;
	_myBase::_decrement();
	return old;
}

String::reverse_iterator String::reverse_iterator::operator+ (size_type i) {
	reverse_iterator toReturn;
	_myBase::_add(toReturn, i);
	return toReturn;
}

String::reverse_iterator String::reverse_iterator::operator- (size_type i) {
	reverse_iterator toReturn;
	_myBase::_subtract(toReturn, i);
	return toReturn;
}

/*
	Non Member Function
*/

void swap(String& x, String& y) {
	x.swap(y);
}

String operator+ (const String& lhs, const String& rhs) {
	String toReturn = lhs;
	toReturn += rhs;
	return toReturn;
}

String operator+ (const String& lhs, const char*   rhs) {
	String toReturn = lhs;
	toReturn += rhs;
	return toReturn;
}

String operator+ (const char*   lhs, const String& rhs) {
	String toReturn = lhs;
	toReturn += rhs;
	return toReturn;
}

String operator+ (const String& lhs, char rhs) {
	String toReturn = lhs;
	toReturn += rhs;
	return toReturn;
}

String operator+ (char lhs, const String& rhs) {
	String toReturn = rhs;
	toReturn += lhs;
	return toReturn;
}

std::ostream& operator<< (std::ostream& os, const _JD String& str) {
	for (size_t i = 0; i < str.length(); ++i)
		os << str[i];
	return os;
}

std::istream& operator>> (std::istream& is, _JD String& str) {
	str.clear();
	char c;
	do {
		c = is.get();
		if (c == '\n' || c == ' ')
			break;
		str.push_back(c);
	} while (true);

	return is;
}

std::istream& getline(std::istream& is, _JD String& str, char delim) {
	str.clear();
	char c;
	do {
		c = is.get();
		if (c == delim)
			break;
		str.push_back(c);
	} while (true);
	return is;
}

std::istream& getline(std::istream& is, _JD String& str) {
	return _JD getline(is, str, '\n');
}

_JD_END
