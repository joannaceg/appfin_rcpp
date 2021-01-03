#include<Rcpp.h>
#include<vector>
#include<ctime>
#include<cstdlib>
#include"DownAndInOption.h"

using namespace Rcpp;
using std::vector;

// [[Rcpp::export]]
double getDownAndInPutOption(
  int nInt,
  double Strike,
  double Spot,
  double Vol,
  double Rfr,
  double Expiry,
  double Barrier,
  int nReps = 1000){

	srand( time(NULL) );

	DownAndInOption myOption(nInt, Strike, Spot, Vol, Rfr, Expiry, Barrier);

	double price = myOption.getDownAndInPutPrice(nReps);
	
	return price;
}
