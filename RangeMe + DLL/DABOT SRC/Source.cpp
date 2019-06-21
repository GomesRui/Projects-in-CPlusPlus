/******************************************************************************

Project: Range
Customer: Miniclip
Made by: Rui Gomes

*******************************************************************************/


#include "srcDaBotHeader.h"

int fin = 0;

void errorMessage() {

	cout << "The command you've put does not belong to any of the options that i've told you." << endl;
	cout << "Put your glasses on and try again :3" << endl;

}


class Range {

private:

	vector<int> classRange{};
	int sortIterator = 0;
	string stringRange;

public:

	void constructorInterval(int first, int last) {

		classRange = { first, last };
	}

	void constructor() {

		classRange = { 0, 0 };
		stringRange = "";
	}

	void buildRange(int first, int last) {

		classRange.push_back(first);
		classRange.push_back(last);

		sort(classRange.begin() + sortIterator, classRange.end());
		sortIterator = sortIterator + 2;

	}

	string presentRange() {
		stringRange = "[";
		for (int unsigned i = 0; i < classRange.size(); i++) {

			stringRange += to_string(classRange[i]);
			if (i == classRange.size() - 1)
				stringRange += "]";
			else if (i % 2 != 0)
				stringRange += "] [";
			else
				stringRange += " ";

		}

		return stringRange;

	}

	vector<int> getVector() {

		return classRange;

	}


	void setVector(vector<int> newVector) {

		classRange = { newVector[0], newVector[1] };

	}

	char findRange(double numberToFind, vector<int> v_tofind) { //look for a number inside the requested range

		for (int unsigned i = 0; i < v_tofind.size(); i = i + 2) {
			if (numberToFind >= v_tofind[i] && numberToFind <= v_tofind[i + 1]) {

				return 't';

			}

		}

		return 'f';

	}

	char findRange(double numberToFind) { //look for a number inside the class range

		for (int unsigned i = 0; i < classRange.size(); i = i + 2) {
			if (numberToFind >= classRange[i] && numberToFind <= classRange[i + 1]) {

				return 't';

			}

		}

		return 'f';

	}

	void Intersection(vector<int> first_vector, vector<int> second_vector) { //do the intersection


		if (findRange(first_vector[0], second_vector) == 't' || findRange(second_vector[0], first_vector) == 't') {

			classRange = { max(first_vector[0],second_vector[0]), min(first_vector[1],second_vector[1]) };

		}
		else
			constructor(); //[0 0]

	}

	void Union(vector<int> first_vector, vector<int> second_vector) { //do the union


		if (findRange(first_vector[0], second_vector) == 't' || findRange(second_vector[0], first_vector) == 't') {

			classRange = { min(first_vector[0],second_vector[0]), max(first_vector[1],second_vector[1]) };

		}
		else
			constructor(); //[0 0]

	}
	};



	int range_me_withDaBot()
	{
		Range mainRange;
		Range workedRange_1;
		Range workedRange_2;
		Range workedRange_Res;

		char answer;
		int first, last;
		double finder = 0.0;
		int nRangeIntersection_first = 0;
		int nRangeIntersection_second = 0;
		char found = 'f';


		cout << "Hi! My name is DaBot" << endl;

		try {

			while (fin == 0) {

				cout << "I would like to test this application with you! Do you need my assistance ? ";
				cout << "Press [Y]es or [N]o" << endl;
				cin >> answer;

				if (answer == 'Y' || answer == 'y') {

					cout << "I'm glad to hear that! Let's begin, shall we?" << endl;


					while (answer == 'Y' || answer == 'y') {
						cout << "Please tell me the first number and the last number of your range (between a space): ";
						cin >> first >> last;

						mainRange.buildRange(first, last);

						cout << "Do you want to add more ranges?" << endl;
						cout << "Press [Y]es or [N]o" << endl;
						cin >> answer;
					}

					cout << "Great job! Now it's time for some MAGIC!" << endl;
					do {
						cout << "What do you want to do?" << endl;
						cout << "a - Intersection" << endl;
						cout << "b - Union" << endl;
						cout << "c - Find number" << endl;
						cout << "e - Exit" << endl;
						cin >> answer;

						switch (answer) {

						case 'a':

							cout << "This is your range: " << mainRange.presentRange() << endl;
							cout << "Select the intervals you want to intersect (between a space): " << endl;
							cin >> nRangeIntersection_first >> nRangeIntersection_second;

							//Building the two new intervals;

							workedRange_1.constructorInterval(mainRange.getVector()[(nRangeIntersection_first * 2) - 2], mainRange.getVector()[(nRangeIntersection_first * 2) - 1]);
							workedRange_2.constructorInterval(mainRange.getVector()[(nRangeIntersection_second * 2) - 2], mainRange.getVector()[(nRangeIntersection_second * 2) - 1]);
							workedRange_Res.Intersection(workedRange_1.getVector(), workedRange_2.getVector());

							cout << "Your Intersection result is the following: " << workedRange_Res.presentRange() << endl;
							break;
						case 'b':

							cout << "This is your range: " << mainRange.presentRange() << endl;
							cout << "Select the intervals you want to unify (between a space): " << endl;
							cin >> nRangeIntersection_first >> nRangeIntersection_second;

							//Building the two new intervals;

							workedRange_1.constructorInterval(mainRange.getVector()[(nRangeIntersection_first * 2) - 2], mainRange.getVector()[(nRangeIntersection_first * 2) - 1]);
							workedRange_2.constructorInterval(mainRange.getVector()[(nRangeIntersection_second * 2) - 2], mainRange.getVector()[(nRangeIntersection_second * 2) - 1]);
							workedRange_Res.Union(workedRange_1.getVector(), workedRange_2.getVector());

							cout << "Your Intersection result is the following: " << workedRange_Res.presentRange() << endl;
							break;
						case 'c':

							cout << "This is your range: " << mainRange.presentRange() << endl;
							cout << "Give me a number and i will tell you if it's inside your range of intervals: ";
							cin >> finder;

							found = mainRange.findRange(finder);

							if (found == 't') {

								cout << "Good news! Your number is indeed part of your range!" << endl;

							}

							else {

								cout << "Sorry... your number doesn't belong to your range." << endl;

							}
							break;

						case 'e':

							cout << "Exiting..." << endl;
							cout << "Byeee! See you next time :)" << endl;

							return 0;

						default:

							errorMessage();
							break;
						}

					} while (answer != 'e');
				}
				else if (answer == 'N' || answer == 'n') {

					fin = 1;
				}

				else {

					errorMessage();

				}

			}

		}
		catch (exception& e)
		{
			cout << "Exception was thrown: " << e.what() << endl;
		}

		cout << "Byeee! See you next time :)" << endl;

		return 0;
	}


