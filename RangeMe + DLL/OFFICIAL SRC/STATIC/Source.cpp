/******************************************************************************

Project: Range
Customer: Miniclip
Made by: Rui Gomes

NOTE: This code is intended to act as an API for the real scenario

*******************************************************************************/

#include "srcHeader.h" //including header file

// -------------- GLOBAL OBJECTS ---------------

bool find(string string_to_find, char character_to_check) {

	int i = 0;

	do {

		if (string_to_find[i] == character_to_check && character_to_check != 'f')
			return true;

		else if (isdigit(string_to_find[i + 1]) && character_to_check == 'f')
			return true;

		i++;

	} while (i < string_to_find.size());

	return false;
}

string buildResult(vector <int> to_convert) { //transforming int vectors to string result

	string converted;
	for (int unsigned i = 0; i < to_convert.size(); i++) {

		converted += to_string(to_convert[i]);

		if (i == 0)
			converted += " ";

	}
	return converted;
}

double buildStringOfInts(string str) { //get the number out of the string input

	string stringOfInts;
	double res;
	for (int unsigned i = 0; i < str.size(); i++) {

		if (isdigit(str[i]) || str[i] == '.') {
			stringOfInts += str[i];

		}

	}

	res = stod(stringOfInts);
	return res; //returning a int value after converting from a string

}


// -------------- GLOBAL CLASS RANGE ---------------

class Range {

private:

	vector<int> classRange;
	string stringRange;


public:

	void constructor() {

		classRange = { 0, 0 };
		stringRange = "";
	}

	void constructorInterval(int first, int last) {

		classRange = { first, last };
	}

	void noConstructor() {

		classRange = { -1, -1 };
	}

	/*string presentRange() {
	stringRange = "[";
	for (int i = 0; i < classRange.size(); i++) {

	stringRange += to_string(classRange[i]);
	if (i == classRange.size() - 1)
	stringRange += "]";
	else if (i % 2 != 0)
	stringRange += "] [";
	else
	stringRange += " ";

	}

	return stringRange;

	}*/

	vector<int> getVector() {

		return classRange;

	}


	void setVector(vector<int> newVector) {

		classRange = { newVector[0], newVector[1] };

	}

	void buildRange(vector<int> vector_to_build) {

		for (unsigned int i = 0; i<vector_to_build.size(); i++)
			classRange.push_back(vector_to_build[i]);

	}

	//MAIN CLASS FUNCTIONS

	char findRange(double numberToFind, vector<int> v_tofind) { //look for a number inside the desired range

		for (int unsigned i = 0; i<v_tofind.size(); i = i + 2) {
			if (numberToFind >= v_tofind[i] && numberToFind <= v_tofind[i + 1]) {

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

// -------------------------------------------- MAIN FUNCTION -----------------------------------------------------------

string range_me(vector<int> startingVector, string op) {

	vector <int> nothing = { -1 , -1 };
	string resultIntersection, resultUnion, result = ""; //final result to send out from the API

	char checkInput, checkIntersection, checkUnion = 'f'; //simulate true and false when finding the value

	double valueToFind; //variable to get the number to find out of OP Object

						//Range classes
						//Building Ranges with default contructor
	Range startingRange; //Input Range
	startingRange.buildRange(startingVector);
	Range workedRange; //Range that will be worked to create union/intersection ranges
	workedRange.constructor();
	Range workedRange_Res_Union; // Union Range
	workedRange_Res_Union.noConstructor();
	Range workedRange_Res_Intersection; //Intersection Range
	workedRange_Res_Intersection.noConstructor();


	try {

		if (find(op, 'i')) {
			workedRange_Res_Intersection.constructorInterval(startingRange.getVector()[0], startingRange.getVector()[1]); //initializing the intersecter as the first interval
			for (int unsigned i = 2; i < startingRange.getVector().size(); i = i + 2) { // defined to intersect more than 2 intervals

				workedRange.constructorInterval(startingRange.getVector()[i], startingRange.getVector()[i + 1]); //Pick up only one interval at a time
				workedRange_Res_Intersection.Intersection(workedRange.getVector(), workedRange_Res_Intersection.getVector()); //Intersection

			}

			//cout << "Intersection: " << workedRange_Res_Intersection.presentRange() << endl;
			result += buildResult(workedRange_Res_Intersection.getVector());
			result += ",";

		}

		if (find(op, 'u')) {

			workedRange_Res_Union.constructorInterval(startingRange.getVector()[0], startingRange.getVector()[1]); //initializing the unifier as the first interval

			for (int unsigned i = 2; i < startingRange.getVector().size(); i = i + 2) {

				workedRange.constructorInterval(startingRange.getVector()[i], startingRange.getVector()[i + 1]); //Pick up only one interval at a time
				workedRange_Res_Union.Union(workedRange.getVector(), workedRange_Res_Union.getVector()); //Union

			}

			//cout << "Union: " << workedRange_Res_Union.presentRange() << endl;
			result += buildResult(workedRange_Res_Union.getVector());
			result += ",";

		}

		if (find(op, 'f')) {


			valueToFind = buildStringOfInts(op);

			checkInput = startingRange.findRange(valueToFind, startingRange.getVector()); //find the value on the initial Range;
			if (workedRange_Res_Union.getVector() != nothing) //in case the intersection wasn't called
				checkUnion = workedRange_Res_Union.findRange(valueToFind, workedRange_Res_Union.getVector()); //find the value on the unified Range;
			else
				checkUnion = 'n';

			if (workedRange_Res_Intersection.getVector() != nothing) //in case the intersection wasn't called
				checkIntersection = workedRange_Res_Union.findRange(valueToFind, workedRange_Res_Intersection.getVector()); //find the value on the intersected Range;
			else
				checkIntersection = 'n';

			//cout << "Value found in initial range: " << checkInput << endl;
			//cout << "Value found in Intersection: " << checkIntersection << endl;
			//cout << "Value found in Union: " << checkUnion << endl;

			result += checkInput;
			result += ",";
			result += checkIntersection;
			result += ",";
			result += checkUnion;
		}

		if (result[result.size() - 1] == ',')
			result.pop_back(); //remove the extra ',' in case intersection and union are not called in the same function request

	}
	catch (exception& e)
	{
		cout << "Exception was thrown: " << e.what() << endl;
	}

	cout << "Final Result: " << result << endl;


	return result;

}
