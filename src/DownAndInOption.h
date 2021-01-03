#include<vector>

class DownAndInOption{
public:

	//constructor
	DownAndInOption(
		int nInt_,
		double strike_,
		double spot_,
		double vol_,
		double r_,
		double expiry_,
		double barrier_
		);

	//destructor
	~DownAndInOption(){};

	//methods
	void generatePath();
	void printPath();
	double getMinValue();
	double getDownAndInCallPrice(int nReps);
	double getDownAndInPutPrice(int nReps);
	double operator()(char char1, int nReps);
	
	//members
	std::vector<double> thisPath;
	int nInt;
	double strike;
	double spot;
	double vol;
	double r;
	double expiry;
	double barrier;

};
