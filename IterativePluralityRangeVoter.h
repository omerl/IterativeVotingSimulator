//
//  IterativePluralityRangeVoter.h
//  RangeEquilibria
//
//  Created by Omer Lev on 17/12/13.
//
//

#ifndef __RangeEquilibria__IterativePluralityRangeVoter__
#define __RangeEquilibria__IterativePluralityRangeVoter__

#include <iostream>
#include "IterativeVoter.h"
#include "IterativePluralityGame.h"

class IterativePluralityRangeVoter: public IterativeVoter {
public:
    IterativePluralityRangeVoter (PrefList * list, IterativeGame * game): IterativeVoter(list,game) {}
    IterativePluralityRangeVoter (PrefList * list): IterativeVoter(list){}
    IterativePluralityRangeVoter (PrefList * list, IterativeGame * game,int ra, int ka,rangeTypes typeRa):IterativeVoter(list,game),r(ra),k(ka),typeR(typeRa){}
    IterativePluralityRangeVoter (PrefList * list,int ra, int ka,rangeTypes typeRa):IterativeVoter(list),r(ra),k(ka),typeR(typeRa){}
    IterativePluralityRangeVoter (const IterativePluralityRangeVoter& v): IterativeVoter ((IterativeVoter&)v),r(v.r),k(v.k),typeR(v.typeR){}
    virtual IterativeVoter* copy() const;
    
    virtual bool makeMove();
    
    virtual double getR();
    virtual double getK();
    virtual void setR (int ra);
    virtual void setK (int ka);
    virtual void setR (double ra);
    virtual void setK (double ka);
    void setRangeType (rangeTypes typeRa);
    
    
protected:
    int r=0;
    int k=1;
    rangeTypes typeR;
    
};

#endif /* defined(__RangeEquilibria__IterativePluralityRangeVoter__) */
