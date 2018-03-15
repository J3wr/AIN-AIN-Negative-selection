#include "declaration.h"

int main()
{
	vector<Iris *> S;
	vector<Iris *> R;

	try
	{
		init(S, R);
		negativeSelection(S, R);
	}
	catch (const Error &)
	{
		clearMemory(S);
		clearMemory(R);
		exit(EXIT_FAILURE);
	}


	return EXIT_SUCCESS;
}
