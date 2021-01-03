#include<iostream>
#include<cmath>
#include <bits/stdc++.h>

#include"getOneGaussianByBoxMueller.h"
#include"DownAndInOption.h"

//definition of constructor
DownAndInOption::DownAndInOption(
	int nInt_,
	double strike_,
	double spot_,
	double vol_,
	double r_,
	double expiry_,
	double barrier_){
		nInt = nInt_;
		strike = strike_;
		spot = spot_;
		vol = vol_;
		r = r_;
		expiry = expiry_;
		barrier = barrier_;
		generatePath();
}

//method definition
void DownAndInOption::generatePath(){
	double thisDrift = (r * expiry - 0.5 * vol * vol * expiry) / double(nInt);
	double cumShocks = 0;
	thisPath.clear();

	for(int i = 0; i < nInt; i++){
		cumShocks += (thisDrift + vol * sqrt(expiry / double(nInt)) * getOneGaussianByBoxMueller());
		thisPath.push_back(spot * exp(cumShocks));
	}
}


void DownAndInOption::printPath(){

	for(int i = 0;  i < nInt; i++){
		std::cout << thisPath[i] << "\n";
	}

}

double DownAndInOption::getDownAndInCallPrice(int nReps){

  double lastSpot;
  double rollingSum = 0.0;
  double thisMin = 0.0;
  
  for(int i = 0; i < nReps; i++){
    generatePath();
    thisMin=getMinValue();
    lastSpot=thisPath[thisPath.size() - 1];
    if(thisMin<barrier)
      rollingSum += (lastSpot > strike) ? (lastSpot - strike) : 0;
  }
  
  return exp(-r*expiry)*rollingSum/double(nReps);

}

double DownAndInOption::getDownAndInPutPrice(int nReps){

  double lastSpot;
	double rollingSum = 0.0;
	double thisMin = 0.0;

	for(int i = 0; i < nReps; i++){
		generatePath();
		thisMin=getMinValue();
		lastSpot=thisPath[thisPath.size() - 1];
		if(thisMin<barrier)
		  rollingSum += (lastSpot < strike) ? (strike - lastSpot) : 0;
	}

	return exp(-r*expiry)*rollingSum/double(nReps);

}

double DownAndInOption::getMinValue(){
  return *std::min_element(thisPath.begin(), thisPath.end());
}

double DownAndInOption::operator()(char char1, int nReps){
	if (char1 == 'C') return getDownAndInCallPrice(nReps);
	else if (char1 == 'P') return getDownAndInPutPrice(nReps);
	else return -99;
}