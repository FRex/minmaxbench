#include "Tester.hpp"
#include "minmaxes.hpp"
#include "minmaxAvx2.hpp"
#include "sumElements.hpp"

int main()
{
    Tester tester;
    tester.addFunc("minmaxElseMin", &minmaxElseMin);
    tester.addFunc("minmaxBitHax", &minmaxBitHax);
    //tester.addFunc("minmax3Way", &minmax3Way);
    tester.addFunc("minmaxSecret", &minmaxAvx2);
    //tester.addFunc("minmaxAvx2Sep", &minmaxAvx2Separate);
    //tester.addFunc("sumElements1", &sumElements1);
    //tester.addFunc("sumElements4", &sumElements4);
    //tester.addFunc("sumElements8", &sumElements8);
    tester.addFunc("minmaxNormal", &minmaxNormal);
    //tester.addFunc("minmaxSeparate", &minmaxSeparate);

    tester.dotest();
    tester.printResults();
}
