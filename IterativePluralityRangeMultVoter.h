//
//  IterativePluralityRangeMultVoter.h
//  RangeEquilibria
//
//  Created by Omer Lev on 6/2/14.
//
//

#ifndef __RangeEquilibria__IterativePluralityRangeMultVoter__
#define __RangeEquilibria__IterativePluralityRangeMultVoter__

#include <iostream>
#include "IterativeVoter.h"
#include "IterativePluralityGame.h"

class IterativePluralityRangeMultVoter: public IterativeVoter {
public:
    IterativePluralityRangeMultVoter (PrefList * list, IterativeGame * game): IterativeVoter(list,game) {}
    IterativePluralityRangeMultVoter (PrefList * list): IterativeVoter(list){}
    IterativePluralityRangeMultVoter (PrefList * list, IterativeGame * game,double ra, double ka,rangeTypes typeRa):IterativeVoter(list,game),r(ra),k(ka),typeR(typeRa){}
    IterativePluralityRangeMultVoter (PrefList * list,double ra, double ka,rangeTypes typeRa):IterativeVoter(list),r(ra),k(ka),typeR(typeRa){}
    IterativePluralityRangeMultVoter (const IterativePluralityRangeMultVoter& v):IterativeVoter ((IterativeVoter&)v),r(v.r),k(v.k),typeR(v.typeR){}
    virtual IterativeVoter* copy() const;

    virtual bool makeMove();
    virtual double getR();
    virtual double getK();
    
    virtual void setR (double ra);
    virtual void setK (double ka);
    void setRangeType (rangeTypes typeRa);
    
    
protected:
    double r=0;
    double k=1;
    rangeTypes typeR;
    
};

#endif /* defined(__RangeEquilibria__IterativePluralityRangeMultVoter__) */
