#ifndef DEFINITION_H
#define DEFINITION_H

#include <string>
#include <iostream>
#include <vector>

using std::string;
using std::vector;

struct Iris
{
public:
	static Iris *make(float _sepalsLength, float _sepalWidth,
		float _petalLength, float _petalWidth,
		const string &_irisCultivar = "setosa");
	//bool operator ==(const Iris &elem) const;
	//bool operator !=(const Iris &elem) const;

	float getSepaLength() const;
	float getSepaWidth() const;
	float getPetaLength() const;
	float getPetaWidth() const;
	const string &getIrisCultivar() const;
private:
	Iris(float _sepalsLength, float _sepalWidth,
		float _petalLength, float _petalWidth,
		const string &_irisCultivar = "setosa");

	Iris(const Iris &) = delete;
	Iris &operator = (const Iris &) = delete;
private:
	float _mSepalsLength;
	float _mSepalsWidth;
	float _mPetalLength;
	float _mPetalWidth;
	string _mIrisCultivar;
};

inline float Iris::getSepaLength() const
{
	return _mSepalsLength;
}

inline float Iris::getSepaWidth() const
{
	return _mSepalsWidth;
}

inline float Iris::getPetaLength() const
{
	return _mPetalLength;
}

inline float Iris::getPetaWidth() const
{
	return _mPetalWidth;
}

inline const string &Iris::getIrisCultivar() const
{
	return _mIrisCultivar;
}

struct Error
{
public:
	Error(const string &message);
private:
	void printErr() const;
	string _mErrMessage;
};

//S - исходные данные
//R - детекторы
void init(vector<Iris *> &S,
	vector<Iris *> &R);
void print(const string &str);
void detecting(vector<Iris *> &S,
	vector<Iris *> &R);
Iris *generationDetector();
bool compare(const Iris *S,
	const Iris *R, const float eps);
void negativeSelection(vector<Iris *> &S,
	vector<Iris *> &R);
void clearMemory(vector<Iris *> &vec);

#endif // DEFINITION_H
