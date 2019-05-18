#pragma once

using namespace std;

class _Bit8
{
	int value;
	int modify(int value)
	{
		if (value >= 0)
			return (value % 256);
		
		else
			return value + 256;
	}

public:

	_Bit8()
		: value(0)
	{
	}

	_Bit8(int value)
		: value(modify(value))
	{
	}

	_Bit8(const _Bit8& bit8)
		: value(bit8.value % 256)
	{
	}

	int toInt() const { return this->value; }

	void operator+=(const _Bit8 bit8)
	{
		this->value += bit8.value;
		this->value %= 256;
	}

	void operator-=(const _Bit8 bit8)
	{
		this->value -= bit8.value;
		if (this->value < 0)
			this->value += 256;
	}

	void operator+=(const int value)
	{
		this->value += value;
		this->value %= 256;
	}

	void operator-=(const int value)
	{
		this->value -= value;
		if (this->value < 0)
			this->value += 256;
	}

	void operator &=(const _Bit8 bit8)
	{
		this->value &= bit8.value;
		this->value %= 256;
	}

	void operator |=(const _Bit8 bit8)
	{
		this->value |= bit8.value;
		this->value %= 256;
	}

	void operator ^=(const _Bit8 bit8)
	{
		this->value ^= bit8.value;
		this->value %= 256;
	}

	void operator &=(const int value)
	{
		this->value &= value;
		this->value %= 256;
	}

	void operator |=(const int value)
	{
		this->value |= value;
		this->value %= 256;
	}

	void operator ^=(const int value)
	{
		this->value ^= value;
		this->value %= 256;
	}


	friend ostream& operator<<(ostream& out, const _Bit8 bit8);

	friend istream& operator>>(istream& in, _Bit8 bit8);

	friend _Bit8 operator+(const int value, const _Bit8 bit8);

	friend _Bit8 operator-(const int value, _Bit8 bit8);

	friend bool operator==(const int value, const _Bit8 bit8);

	friend bool operator !=(const int value, const _Bit8 bit8);

	friend bool operator >=(const int value, const _Bit8 bit8);

	friend bool operator <=(const int value, const _Bit8 bit8);

	friend bool operator <(const int value, const _Bit8 bit8);

	friend bool operator >(const int value, const _Bit8 bit8);

	friend _Bit8 operator+(_Bit8 bit8, const int value);

	friend _Bit8 operator-(_Bit8 bit8, const int value);

	friend bool operator==(const _Bit8 bit8, const int value);

	friend bool operator !=(const _Bit8 bit8, const int value);

	friend bool operator >=(const _Bit8 bit8, const int value);

	friend bool operator <=(const _Bit8 bit8, const int value);

	friend bool operator <(const _Bit8 bit8, const int value);

	friend bool operator >(const _Bit8 bit8, const int value);

	friend _Bit8 operator+(_Bit8 b1, const _Bit8 b2);

	friend _Bit8 operator-(_Bit8 b1, const _Bit8 b2);

	friend bool operator==(const _Bit8 b1, const _Bit8 b2);

	friend bool operator !=(const _Bit8 b1, const _Bit8 b2);

	friend bool operator >=(const _Bit8 b1, const _Bit8 b2);

	friend bool operator <=(const _Bit8 b1, const _Bit8 b2);

	friend bool operator <(const _Bit8 b1, const _Bit8 b2);

	friend bool operator >(const _Bit8 b1, const _Bit8 b2);
};

inline ostream& operator<<(ostream& out, const _Bit8 bit8)
{
	out << bit8.value;
	return out;
}

inline istream& operator>>(istream& in, _Bit8 bit8)
{
	in >> bit8.value;
	return in;
}

inline _Bit8 operator+(const int value, _Bit8 bit8)
{
	_Bit8 temp = value;
	temp.value += bit8.value;
	temp.value %= 256;

	return temp;
}

inline _Bit8 operator-(const int value, _Bit8 bit8)
{
	_Bit8 temp = value;
	temp.value -= bit8.value;

	if (temp.value < 0)
		temp.value += 256;

	return temp;
}

inline bool operator==(const int value, const _Bit8 bit8) { return value == bit8.value; }

inline bool operator !=(const int value, const _Bit8 bit8) { return value != bit8.value; }

inline bool operator >=(const int value, const _Bit8 bit8) { return value >= bit8.value; }

inline bool operator <=(const int value, const _Bit8 bit8) { return value <= bit8.value; }

inline bool operator <(const int value, const _Bit8 bit8) { return value < bit8.value; }

inline bool operator >(const int value, const _Bit8 bit8) { return value > bit8.value; }

inline _Bit8 operator+(_Bit8 bit8, const int value)
{
	bit8.value += value;
	bit8.value %= 256;
	return bit8;
}

inline _Bit8 operator-(_Bit8 bit8, const int value)
{
	bit8.value -= value;

	if (bit8.value < 0)
		bit8.value += 256;

	return bit8;
}

inline bool operator==(const _Bit8 bit8, const int value) { return bit8.value == value; }

inline bool operator !=(const _Bit8 bit8, const int value) { return bit8.value != value; }

inline bool operator >=(const _Bit8 bit8, const int value) { return bit8.value >= value; }

inline bool operator <=(const _Bit8 bit8, const int value) { return bit8.value <= value; }

inline bool operator <(const _Bit8 bit8, const int value) { return bit8.value < value; }

inline bool operator >(const _Bit8 bit8, const int value) { return bit8.value > value; }


inline _Bit8 operator+(_Bit8 b1, const _Bit8 b2)
{
	b1.value += b2.value;
	b1.value %= 256;

	return b1;
}

inline _Bit8 operator-(_Bit8 b1, const _Bit8 b2)
{
	b1.value -= b2.value;

	if (b1.value < 0)
		b1.value += 256;

	return b1;
}

inline bool operator==(const _Bit8 b1, const _Bit8 b2) { return b1.value == b2.value; }

inline bool operator !=(const _Bit8 b1, const _Bit8 b2) { return b1.value != b2.value; }

inline bool operator >=(const _Bit8 b1, const _Bit8 b2) { return b1.value >= b2.value; }

inline bool operator <=(const _Bit8 b1, const _Bit8 b2) { return b1.value <= b2.value; }

inline bool operator <(const _Bit8 b1, const _Bit8 b2) { return b1.value < b2.value; }

inline bool operator >(const _Bit8 b1, const _Bit8 b2) { return b1.value > b2.value; }

class _Bit16
{
	int value;

public:

	_Bit16()
		: value(0)
	{
	}

	_Bit16(int value)
		: value(value % 65536)
	{
	}

	_Bit16(const _Bit16& bit16)
		: value(bit16.value % 65536)
	{
	}

	int toInt() { return this->value; }

	void operator+=(const _Bit16 bit16)
	{
		this->value += bit16.value;
		this->value %= 65536;
	}

	void operator-=(const _Bit16 bit16)
	{
		this->value -= bit16.value;
		if (this->value < 0)
			this->value += 65536;
	}

	void operator+=(const int value)
	{
		this->value += value;
		this->value %= 65536;
	}

	void operator-=(const int value)
	{
		this->value -= value;
		if (this->value < 0)
			this->value += 65536;
	}

	friend ostream& operator<<(ostream& out, const _Bit16 bit16);

	friend istream& operator>>(istream& in, _Bit16 bit16);

	friend _Bit16 operator+(const int value, const _Bit16 bit16);

	friend _Bit16 operator-(const int value, const _Bit16 bit16);

	friend bool operator==(const int value, const _Bit16 bit16);

	friend bool operator !=(const int value, const _Bit16 bit16);

	friend bool operator >=(const int value, const _Bit16 bit16);

	friend bool operator <=(const int value, const _Bit16 bit16);

	friend bool operator <(const int value, const _Bit16 bit16);

	friend bool operator >(const int value, const _Bit16 bit16);

	friend _Bit16 operator+(_Bit16 bit16, const int value);

	friend _Bit16 operator-(_Bit16 bit16, const int value);

	friend bool operator==(const _Bit16 bit16, const int value);

	friend bool operator !=(const _Bit16 bit16, const int value);

	friend bool operator >=(const _Bit16 bit16, const int value);

	friend bool operator <=(const _Bit16 bit16, const int value);

	friend bool operator <(const _Bit16 bit16, const int value);

	friend bool operator >(const _Bit16 bit16, const int value);

	friend _Bit16 operator+(_Bit16 b1, const _Bit16 b2);

	friend _Bit16 operator-(_Bit16 b1, const _Bit16 b2);

	friend bool operator==(const _Bit16 b1, const _Bit16 b2);

	friend bool operator !=(const _Bit16 b1, const _Bit16 b2);

	friend bool operator >=(const _Bit16 b1, const _Bit16 b2);

	friend bool operator <=(const _Bit16 b1, const _Bit16 b2);

	friend bool operator <(const _Bit16 b1, const _Bit16 b2);

	friend bool operator >(const _Bit16 b1, const _Bit16 b2);
};

inline ostream& operator<<(ostream& out, const _Bit16 bit16)
{
	out << bit16.value;
	return out;
}

inline istream& operator>>(istream& in, _Bit16 bit16)
{
	in >> bit16.value;
	return in;
}

inline _Bit16 operator+(const int value, const _Bit16 bit16)
{
	_Bit16 temp = value;
	temp.value += bit16.value;
	temp.value %= 65536;

	return temp;
}

inline _Bit16 operator-(const int value, const _Bit16 bit16)
{
	_Bit16 temp = value;
	temp.value -= bit16.value;

	if (temp.value < 0)
		temp.value += 65536;

	return temp;
}

inline bool operator==(const int value, const _Bit16 bit16) { return value == bit16.value; }

inline bool operator !=(const int value, const _Bit16 bit16) { return value != bit16.value; }

inline bool operator >=(const int value, const _Bit16 bit16) { return value >= bit16.value; }

inline bool operator <=(const int value, const _Bit16 bit16) { return value <= bit16.value; }

inline bool operator <(const int value, const _Bit16 bit16) { return value < bit16.value; }

inline bool operator >(const int value, const _Bit16 bit16) { return value > bit16.value; }

inline _Bit16 operator+(_Bit16 bit16, const int value)
{
	bit16.value += value;
	bit16.value %= 65536;
	return bit16;
}

inline _Bit16 operator-(_Bit16 bit16, const int value)
{
	bit16.value -= value;

	if (bit16.value < 0)
		bit16.value += 65536;

	return bit16;
}

inline bool operator==(const _Bit16 bit16, const int value) { return bit16.value == value; }

inline bool operator !=(const _Bit16 bit16, const int value) { return bit16.value != value; }

inline bool operator >=(const _Bit16 bit16, const int value) { return bit16.value >= value; }

inline bool operator <=(const _Bit16 bit16, const int value) { return bit16.value <= value; }

inline bool operator <(const _Bit16 bit16, const int value) { return bit16.value < value; }

inline bool operator >(const _Bit16 bit16, const int value) { return bit16.value > value; }

inline _Bit16 operator+(_Bit16 b1, const _Bit16 b2)
{
	b1.value += b2.value;
	b1.value %= 65536;

	return b1;
}

inline _Bit16 operator-(_Bit16 b1, const _Bit16 b2)
{
	b1.value -= b2.value;

	if (b1.value < 0)
		b1.value += 65536;

	return b1;
}

inline bool operator==(const _Bit16 b1, const _Bit16 b2) { return b1.value == b2.value; }

inline bool operator !=(const _Bit16 b1, const _Bit16 b2) { return b1.value != b2.value; }

inline bool operator >=(const _Bit16 b1, const _Bit16 b2) { return b1.value >= b2.value; }

inline bool operator <=(const _Bit16 b1, const _Bit16 b2) { return b1.value <= b2.value; }

inline bool operator <(const _Bit16 b1, const _Bit16 b2) { return b1.value < b2.value; }

inline bool operator >(const _Bit16 b1, const _Bit16 b2) { return b1.value > b2.value; }

class _Label
{
	string str;

public:

	_Label()
		: str("")
	{
	}

	_Label(const char* str)
		: str(str)
	{
	}

	_Label(const _Label& label)
		: str(label.str)
	{
	}

	_Label(const string str)
		: str(str)
	{
	}

	string toString() { return this->str; }

	void operator+=(const _Label label) { this->str += label.str; }

	void operator+=(const char* str) { this->str += str; }

	friend ostream& operator<<(ostream& out, const _Label& label);

	friend istream& operator>>(istream& in, _Label& label);

	friend _Label operator +(const char* str, const _Label label);

	friend bool operator ==(const char* str, const _Label label);

	friend bool operator !=(const char* str, const _Label label);

	friend bool operator <=(const char* str, const _Label label);

	friend bool operator >=(const char* str, const _Label label);

	friend bool operator >(const char* str, const _Label label);

	friend bool operator <(const char* str, const _Label label);

	friend _Label operator +(_Label label, const char* str);

	friend bool operator ==(const _Label label, const char* str);

	friend bool operator !=(const _Label label, const char* str);

	friend bool operator <=(const _Label label, const char* str);

	friend bool operator >=(const _Label label, const char* str);

	friend bool operator <(const _Label label, const char* str);

	friend bool operator >(const _Label label, const char* str);

	friend _Label operator +(_Label l1, const _Label l2);

	friend bool operator ==(const _Label l1, const _Label l2);

	friend bool operator !=(const _Label l1, const _Label l2);

	friend bool operator <=(const _Label l1, const _Label l2);

	friend bool operator >=(const _Label l1, const _Label l2);

	friend bool operator <(const _Label l1, const _Label l2);

	friend bool operator >(const _Label l1, const _Label l2);
};

inline ostream& operator<<(ostream& out, const _Label& label)
{
	out << label.str;
	return out;
}

inline istream& operator>>(istream& in, _Label& label)
{
	in >> label.str;
	return in;
}

inline _Label operator +(const char* str, const _Label label)
{
	_Label temp = str;
	temp.str += label.str;
	return temp;
}

inline bool operator ==(const char* str, const _Label label) { return label.str == str; }

inline bool operator !=(const char* str, const _Label label) { return label.str != str; }

inline bool operator <=(const char* str, const _Label label)
{
	string temp = str;
	return temp.length() <= label.str.length();
}

inline bool operator >=(const char* str, const _Label label)
{
	string temp = str;
	return temp.length() >= label.str.length();
}

inline bool operator >(const char* str, const _Label label)
{
	string temp = str;
	return temp.length() > label.str.length();
}

inline bool operator <(const char* str, const _Label label)
{
	string temp = str;
	return temp.length() < label.str.length();
}

inline _Label operator +(_Label label, const char* str)
{
	label.str += str;
	return label;
}

inline bool operator ==(const _Label label, const char* str) { return label.str == str; }

inline bool operator !=(const _Label label, const char* str) { return label.str != str; }

inline bool operator <=(const _Label label, const char* str)
{
	string temp = str;
	return label.str.length() <= temp.length();
}

inline bool operator >=(const _Label label, const char* str)
{
	string temp = str;
	return label.str.length() >= temp.length();
}

inline bool operator <(const _Label label, const char* str)
{
	string temp = str;
	return label.str.length() < temp.length();
}

inline bool operator >(const _Label label, const char* str)
{
	string temp = str;
	return label.str.length() > temp.length();
}

inline _Label operator +(_Label l1, const _Label l2)
{
	l1.str += l2.str;
	return l1;
}

inline bool operator ==(const _Label l1, const _Label l2) { return l1.str == l2.str; }

inline bool operator !=(const _Label l1, const _Label l2) { return l1.str != l2.str; }

inline bool operator <=(const _Label l1, const _Label l2) { return l1.str.length() <= l2.str.length(); }

inline bool operator >=(const _Label l1, const _Label l2) { return l1.str.length() >= l2.str.length(); }

inline bool operator <(const _Label l1, const _Label l2) { return l1.str.length() < l2.str.length(); }

inline bool operator >(const _Label l1, const _Label l2) { return l1.str.length() > l2.str.length(); }
