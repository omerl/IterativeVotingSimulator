//
//  IterativeBestResponseVoter.h
//  RangeEquilibria
//
//  Created by Omer Lev on 4/11/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef RangeEquilibria_IterativeBestResponseVoter_h
#define RangeEquilibria_IterativeBestResponseVoter_h


#include "IterativeVoter.h"
#include <vector>

using namespace std;

class IterativeBestResponseVoter: public IterativeVoter {
public:
    IterativeBestResponseVoter (PrefList * list, IterativeGame * game): IterativeVoter(list,game) {}
    IterativeBestResponseVoter (PrefList * list): IterativeVoter(list){}
    IterativeBestResponseVoter (const IterativeBestResponseVoter& v):IterativeVoter((IterativeVoter&)v) {
        currentBestWinner=v.currentBestWinner;
        bestPrefs=vector<PrefList>(v.bestPrefs);
    }
    
    
    virtual bool makeMove();
    virtual IterativeVoter* copy() const;
    
protected:
    void makeEveryOptionMove(int placesLeft, PrefList& tempPref);
    vector<PrefList> bestPrefs;
    int currentBestWinner;
};


#endif
