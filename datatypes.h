#pragma once

using namespace std;

class _Bit8
{
	int value;

public:

	_Bit8() : value(0) {}
	_Bit8(int value) : value(value) {}
	
	void operator+=()
	{
		this->value+=1;
	}

	void operator-=()
	{
		this->value-=1;
	}

	_Bit8 operator+(const _Bit8 &bit8)
	{
		this->value += bit8.value;
		this->value %= 256;
		
		return *this;
	}

	_Bit8 operator- (_Bit8 bit8)
	{
		this->value -= bit8.value;

		if (this->value < 0)
			this->value += 256;
		
		return *this;
	}

	void operator= (_Bit8 bit8)
	{
		this->value = bit8.value;
	}

	bool operator== (_Bit8 bit8)
	{
		if (this->value == bit8.value)
			return true;
		else
			return false;
	}

	bool operator != (_Bit8 bit8)
	{
		if (this->value != bit8.value)
			return true;
		else
			return false;
	}

	bool operator >= (_Bit8 bit8)
	{
		if (this->value >= bit8.value)
			return true;
		else
			return false;
	}
	bool operator <= (_Bit8 bit8)
	{
		if (this->value <= bit8.value)
			return true;
		else
			return false;
	}
	bool operator < (_Bit8 bit8)
	{
		if (this->value < bit8.value)
			return true;
		else
			return false;
	}
	bool operator > (_Bit8 bit8)
	{
		if (this->value > bit8.value)
			return true;
		else
			return false;
	}
	_Bit8 operator+(int value)
	{
		this->value += value;
		this->value %= 256;

		return *this;
	}

	_Bit8 operator- (int value)
	{
		this->value -= value;

		if (this->value < 0)
			this->value += 256;

		return *this;
	}

	void operator= (int value)
	{
		this->value = value;
	}

	bool operator== (int value)
	{
		if (this->value == value)
			return true;
		else
			return false;
	}

	bool operator != (int value)
	{
		if (this->value != value)
			return true;
		else
			return false;
	}

	bool operator >= (int value)
	{
		if (this->value >= value)
			return true;
		else
			return false;
	}
	bool operator <= (int value)
	{
		if (this->value <= value)
			return true;
		else
			return false;
	}
	bool operator < (int value)
	{
		if (this->value < value)
			return true;
		else
			return false;
	}
	bool operator > (int value)
	{
		if (this->value > value)
			return true;
		else
			return false;
	}

	friend ostream& operator<< (ostream &out, const _Bit8 &bit8);

	friend istream& operator>> (istream &in, _Bit8 &bit8);
};

ostream& operator<< (ostream &out, const _Bit8 &bit8)
{
	
	out << bit8.value;
	return out;
}

istream& operator>> (istream &in, _Bit8 &bit8)
{
	in >> bit8.value;
	return in;
}

class _Bit16
{
	int value;

public:

	_Bit16() : value(0) {}
	_Bit16(int value) : value(value) {}

	_Bit16 operator+(const _Bit16 &bit16)
	{
		this->value += bit16.value;
		this->value %= 65536;

		return *this;
	}

	_Bit16 operator- (_Bit16 bit16)
	{
		this->value -= bit16.value;

		if (this->value < 0)
			this->value += 65536;

		return *this;
	}

	void operator= (_Bit16 bit16)
	{
		this->value = bit16.value;
	}

	void operator++()
	{
		++this->value;
	}

	void operator--()
	{
		--this->value;
	}

	bool operator== (_Bit16 bit16)
	{
		if (this->value == bit16.value)
			return true;
		else
			return false;
	}

	bool operator != (_Bit16 bit16)
	{
		if (this->value != bit16.value)
			return true;
		else
			return false;
	}

	bool operator >= (_Bit16 bit16)
	{
		if (this->value >= bit16.value)
			return true;
		else
			return false;
	}
	bool operator <= (_Bit16 bit16)
	{
		if (this->value <= bit16.value)
			return true;
		else
			return false;
	}
	bool operator < (_Bit16 bit16)
	{
		if (this->value < bit16.value)
			return true;
		else
			return false;
	}
	bool operator > (_Bit16 bit16)
	{
		if (this->value > bit16.value)
			return true;
		else
			return false;
	}

	_Bit16 operator+(int value)
	{
		this->value += value;
		this->value %= 65536;

		return *this;
	}

	_Bit16 operator- (int value)
	{
		this->value -= value;

		if (this->value < 0)
			this->value += 65536;

		return *this;
	}
	void operator= (int value)
	{
		this->value = value;
	}

	bool operator== (int value)
	{
		if (this->value == value)
			return true;
		else
			return false;
	}

	bool operator != (int value)
	{
		if (this->value != value)
			return true;
		else
			return false;
	}

	bool operator >= (int value)
	{
		if (this->value >= value)
			return true;
		else
			return false;
	}
	bool operator <= (int value)
	{
		if (this->value <= value)
			return true;
		else
			return false;
	}
	bool operator < (int value)
	{
		if (this->value < value)
			return true;
		else
			return false;
	}
	bool operator > (int value)
	{
		if (this->value > value)
			return true;
		else
			return false;
	}


	friend ostream& operator<< (ostream &out, const _Bit16 &bit16);

	friend istream& operator>> (istream &in, _Bit16 &bit16);
};

ostream& operator<< (ostream &out, const _Bit16 &bit16)
{

	out << bit16.value;
	return out;
}

istream& operator>> (istream &in, _Bit16 &bit16)
{
	in >> bit16.value;
	return in;
}

class _Label
{
	string str;

public:

	_Label() : str("") {}
	_Label(const char *str) : str(str) {}

	_Label operator +(const _Label &label)
	{
		this->str += label.str;
		return *this;
	}

	bool operator == (_Label label)
	{
		if (this->str == label.str)
			return true;
		else
			return false;
	}
	
	bool operator != (_Label label)
	{
		if (this->str != label.str)
			return true;
		else
			return false;
	}

	bool operator <= (_Label label)
	{
		if (this->str.length() <= label.str.length())
			return true;
		else
			return false;
	}

	bool operator >= (_Label label)
	{
		if (this->str.length() >= label.str.length())
			return true;
		else
			return false;
	}

	bool operator < (_Label label)
	{
		if (this->str.length() < label.str.length())
			return true;
		else
			return false;
	}

	bool operator > (_Label label)
	{
		if (this->str.length() > label.str.length())
			return true;
		else
			return false;
	}
	_Label operator +(const char *str)
	{
		this->str += str;
		return *this;
	}

	bool operator == (const char *str)
	{
		if (this->str == str)
			return true;
		else
			return false;
	}

	bool operator != (const char *str)
	{
		if (this->str != str)
			return true;
		else
			return false;
	}

	bool operator <= (const char *str)
	{
		string temp = str;
		if (this->str.length() <= temp.length())
			return true;
		else
			return false;
	}

	bool operator >= (const char *str)
	{
		string temp = str;
		if (this->str.length() >= temp.length())
			return true;
		else
			return false;
	}

	bool operator < (const char *str)
	{
		string temp = str;
		if (this->str.length() < temp.length())
			return true;
		else
			return false;
	}

	bool operator > (const char *str)
	{
		string temp = str;
		if (this->str.length() > temp.length())
			return true;
		else
			return false;
	}

	friend ostream& operator<< (ostream &out, const _Label &label);

	friend istream& operator>> (istream &in, _Label &label);
};

ostream& operator<< (ostream &out, const _Label &label)
{
	out << label.str;
	return out;
}

istream& operator>> (istream &in, _Label &label)
{
	in >> label.str;
	return in;
}