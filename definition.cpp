#include "declaration.h"
#include <fstream>
#include <random>
#include <boost/algorithm/string.hpp>

Iris *Iris::make(float _sepalsLength, float _sepalWidth,
	float _petalLength, float _petalWidth,
	const std::string &_irisCultivar)
{
	if (_sepalsLength <= 0)
		throw Error("Length of sepals must be bigger than null.\n");
	else if (_sepalWidth <= 0)
		throw Error("Width of sepals must be bigger than null.\n");
	else if (_petalLength <= 0)
		throw Error("Length of petal must be bigger than null.\n");
	else if (_petalWidth <= 0)
		throw Error("Width of petal must be bigger than null.\n");
	else if (_irisCultivar.empty())
		throw Error("Name of cultivar must be bigger than null.\n");
	else
		return new Iris(_sepalsLength, _sepalWidth,
		_petalLength, _petalWidth,
		_irisCultivar);
}

//bool Iris::operator ==(const Iris &elem) const
//{
//    return _mSepalsLength == elem._mSepalsLength &&
//            _mSepalsWidth == elem._mSepalsWidth &&
//            _mPetalLength == elem._mPetalLength &&
//            _mPetalWidth == elem._mPetalWidth;
//    return abs(_mSepalsLength - elem._mSepalsLength) < 0.3 &&
//            abs(_mSepalsWidth - elem._mPetalWidth) < 0.3 &&
//            abs(_mPetalLength - elem._mPetalLength) < 0.3 &&
//            abs(_mPetalWidth - elem._mPetalWidth) < 0.3;
//}

//bool Iris::operator !=(const Iris &elem) const
//{
//    return !(*this == elem);
//}

Iris::Iris(float _sepalsLength, float _sepalWidth,
	float _petalLength, float _petalWidth,
	const std::string &_irisCultivar) : _mSepalsLength(_sepalsLength),
	_mSepalsWidth(_sepalWidth), _mPetalLength(_petalLength),
	_mPetalWidth(_petalWidth), _mIrisCultivar(_irisCultivar)
{}

Error::Error(const std::string &message) :
_mErrMessage(message)
{
	printErr();
}

void Error::printErr() const
{
	std::cerr << _mErrMessage << std::endl;
}

void init(vector<Iris *> &S, vector<Iris *> &R)
{
	std::fstream fin;
	fin.open("../MIOS_Laba3/training_set.txt", std::ios::in);
	if (fin.is_open())
	{
		S.reserve(50);
		string readed;
		while (std::getline(fin, readed))
		{
			vector<string> vec_str;
			boost::split(vec_str, readed, boost::is_any_of(" "));
			Iris *ptr;
			//try
			//{
			ptr = Iris::make(std::stof(vec_str[0]),
				std::stof(vec_str[1]),
				std::stof(vec_str[2]),
				std::stof(vec_str[3]));

			//}
			//catch(const Error &)
			//{
			//break;
			//}
			S.push_back(ptr);
		}
	}
	else
		throw Error("Can't read training file.\n");

	//Generated detectors
	R.reserve(S.size());
	//R.push_back(Iris::make(2.3,2.3,2.3,2.3));
	for (size_t i = 0; i < S.size() * 2; ++i)
	{
		Iris *ptr = generationDetector();
		if (ptr)
			R.push_back(ptr);
		else
			--i;
	}
}

void print(const std::string &str)
{
	std::cout << str;
}

void detecting(vector<Iris *> &S, vector<Iris *> &R)
{
	for (size_t i = 0; i < S.size(); ++i)
		for (size_t j = 0; j < R.size(); ++j)
		{
		if (compare(S.at(i), R.at(j), 0.3))
		{
			Iris *ptr = R.at(j);
			delete ptr;
			ptr = generationDetector();
			if (!ptr)
				throw Error("Can't generated new detector.\n");
			else
				--j;
		}
		}
}

Iris *generationDetector()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> disSepLen(4, 7.5);
	std::uniform_real_distribution<float> disSepWidth(2, 4.5);
	std::uniform_real_distribution<float> disPetLen(1, 7);
	std::uniform_real_distribution<float> disPetWidth(0.1, 2.5);

	Iris *ptr;
	try
	{
		ptr = Iris::make(disSepLen(gen), disSepWidth(gen),
			disPetLen(gen), disPetWidth(gen));
	}
	catch (const Error &)
	{
		return nullptr;
	}

	return ptr;
}

bool compare(const Iris *S, const Iris *R,
	const float eps)
{

	//if(*S == *R)
	//    return true;
	//else
	//    return false;
	return abs(S->getSepaLength() - R->getSepaLength()) < eps &&
		abs(S->getSepaWidth() - R->getSepaWidth()) < eps &&
		abs(S->getPetaLength() - R->getPetaLength()) < eps &&
		abs(S->getPetaWidth() - R->getPetaWidth()) < eps;
}

void negativeSelection(vector<Iris *> &S,
	vector<Iris *> &R)
{
	detecting(S, R);

	print("Enter sepals length: ");
	float sepalsLen;
	std::cin >> sepalsLen;
	print("\nEnter sepals width: ");
	float sepalsWid;
	std::cin >> sepalsWid;
	print("\nEnter petal length: ");
	float petalLen;
	std::cin >> petalLen;
	print("\nEnter petal width: ");
	float petalWid;
	std::cin >> petalWid;
	//print("Enter iris culticar(optional): ");
	//string irisCul;
	//std::getline(std::cin, irisCul);
	//std::cin >> irisCul;

	Iris *ptr;
	//try
	//{
	ptr = Iris::make(sepalsLen, sepalsWid,
		petalLen, petalWid);//, irisCul);
	//}
	//catch(const Error &err)
	//{
	//    err.printErr();
	//    exit(EXIT_FAILURE);
	//}

	bool comp;
	for (size_t i = 0; i < R.size(); ++i)
	{
		comp = compare(ptr, R[i], 0.3);
		if (comp)
			break;
	}
	if (comp)
		print("Someone else.\n");
	else
		print("Own.\n");
}

void clearMemory(vector<Iris *> &vec)
{
	for (size_t i = 0; i < vec.size(); ++i)
	{
		delete vec[i];
	}
}
