//
//  Voter.h
//  RangeEquilibria
//
//  Created by Omer Lev on 27/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef RangeEquilibria_Voter_h
#define RangeEquilibria_Voter_h

#include "defs.h"
#include "PrefList.h"

class IterativeGame;

class IterativeVoter {
public:
    IterativeVoter (PrefList * list, IterativeGame * game);
    IterativeVoter (PrefList * list);
    IterativeVoter (const IterativeVoter& v);
    virtual ~IterativeVoter();
    
    void setGame (IterativeGame * theGame);
    const IterativeGame * getGame() const;
    virtual const PrefList* const getVote() const;
    virtual bool makeMove()=0;
    
    virtual double getR() {return -1;}
    virtual double getK() {return -1;}
    virtual void setR (double r) {};
    virtual void setK (double k) {};
    virtual void setR (int r) {};
    virtual void setK (int k) {};
    
    virtual void setPublicVoter(PrefList * list);
    
    virtual void resetVoter();
    virtual void abstainVoter();
    
    virtual bool isAbstained();
    
    virtual int getTrueCandidateRank(int c);
    
    virtual IterativeVoter* copy() const=0;
    
protected:
    int candidateNumber;
    PrefList truePrefs;
    PrefList publicPrefs;
    IterativeGame * game;
    bool abstain;
};


#endif
