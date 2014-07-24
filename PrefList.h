//
//  refList.h
//  RangeEquilibria
//
//  Created by Omer Lev on 28/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef RangeEquilibria_refList_h
#define RangeEquilibria_refList_h

#include "defs.h"

class PrefList {
public:
    PrefList();
    PrefList (const int candNum, const int newVote[]);
    PrefList (const PrefList &);
    ~PrefList();
    const int* const getVote() const;
    
    int distanceFromPref(PrefList& a) const;
    
    int operator [](const int b) const;
    int& operator[] (const int b);
    bool operator!= (const PrefList&) const;
    const PrefList& operator=(const PrefList &rhs);
    bool operator<(const PrefList &rhs) const;
    
    int getRankForCandidate(int c);
    friend std::ostream& operator<< (std::ostream& stream, PrefList& pref);
    void abstain();
    void rejoin();
    bool isAbstained() const;
    
    int getCandidateNumber() const;
    
protected:
    int candidateNumber;
    int *vote;
    void populateVoteArray(const int * newVote);
    bool abstension=false;
    
};

#endif
