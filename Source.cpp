#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <math.h>
//Day10 Part 1
//Given a list of adapter ratings, we can plug them in to our outlet which has a rating of 0 in order where the difference between adapters can be from 1 to
//3, so if given the list:
//16
//10
//15
//5
//1
//11
//7
//19
//6
//12
//4
//we can connect them as follows
//0 - starting outlet
//1 - 1 difference
//4 - 3 differnece
//5 - 1 difference
//6 - 1 difference
//7 - 1 difference
//10 - 3 difference
//11 - 1 difference
//12 - 1 difference
//15 - 3 difference
//16 - 1 difference
//19 - 3 difference
//22 - 3 difference this adapter is the computer adapter and it is always 3 higher than the last adapter
//so here there are 7 1 differences and 5 3 differences. 
//To get our answer we need to multiply 1 differences by 3 differences
//So the answer for these adapters is 35.

//So if we sort the list of adapters and then check the difference between n and n + 1, depending on the answer we increment a count for each of the 
//differences, 1, 2, and 3, then once done we increment the 3 count one more because the computer adapter is always a difference of 3

//Day10 Part 2
//Find the number of unique permutations of adapters that follow the rules above.

//So through much research I was made aware that the values of the fibbinocci sequence can be used here, corosponding to the patterns of skippable adapter
//differences, skippable adapters are ones with a difference of 1. Depending on the number of skippable values in a row determines how many permutations
//it adds, for the pattern 1,1 we can have two permutations, for the pattern 1,1,1 we can have 4 permutations, and for the pattern 1,1,1,1 we can have
//7 permutations, so if we get a list of the differences, and count these patterns then take those counts, which are defined by x for 1,1 y for 1,1,1 and 
//z for 1,1,1,1, we can get the total number for permutations with this equation, 2^x * 4^y * 7^z

std::vector<int> test = { 16, 10, 15, 5, 1, 11, 7, 19, 6, 12, 4 };

std::vector<int> getPuzzleInput()
{
	std::vector<int> input;

	std::ifstream file;
	std::string line;
	file.open("puzzle-input.txt");
	while (std::getline(file, line))
	{
		int x = std::stoi(line);
		input.push_back(x);
	}

	return input;
}

int findAnswerPart1(std::vector<int> input)
{
	int oneCount = 0;
	int twoCount = 0;
	int threeCount = 0;
	int compare = 0;

	for (int i = 0; i < input.size(); i++)
	{
		if (compare + 1 == input[i])
			oneCount++;
		else if (compare + 2 == input[i])
			twoCount++;
		else if (compare + 3 == input[i])
			threeCount++;

		compare = input[i];
	}
	threeCount++;

	return oneCount * threeCount;
}

std::vector<int> createSeq(std::vector<int> test)
{
	std::vector<int> seq;
	int compare = 0;

	for (int i = 0; i < test.size(); i++)
	{
		if (compare + 1 == test[i])
			seq.push_back(1);
		else if (compare + 2 == test[i])
			seq.push_back(2);
		else if (compare + 3 == test[i])
			seq.push_back(3);

		compare = test[i];
	}
	seq.push_back(3);

	return seq;
}

void findAnswerPart2(std::vector<int> seq)
{
	//x is the count of 1,1 pattern
	int x = 0;
	//y is the count of 1,1,1 pattern
	int y = 0;
	//z is the count of 1,1,1,1 patterns
	int z = 0;
	int oneCount = 0;

	for (int i = 0; i < seq.size(); i++)
	{
		if (seq[i] == 1)
			oneCount++;
		else if (seq[i] == 3)
		{
			switch (oneCount)
			{
			case 2:
				x++;
				break;
			case 3:
				y++;
				break;
			case 4:
				z++;
				break;
			}

			oneCount = 0;
			
		}
	}

	long long answer = pow(2, x) * pow(4, y) * pow(7, z);

	std::cout << "Answer: " << answer << '\n';
}

int main()
{
	std::vector<int> input = getPuzzleInput();

	std::sort(input.begin(), input.end());

	std::sort(test.begin(), test.end());

	std::vector<int> seq = createSeq(input);

	findAnswerPart2(seq);

	//for (auto t : test)
	//{
	//	std::cout << t << " ";
	//}

	//std::cout << '\n';

	//for (auto s : seq)
	//{
	//	std::cout << s << " ";
	//}

	//std::cout << findAnswerPart1(input) << '\n';

	return 0;
}