//
//  Game.h
//  RangeEquilibria
//
//  Created by Omer Lev on 28/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef RangeEquilibria_Game_h
#define RangeEquilibria_Game_h

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <math.h>
#include <algorithm>
#include "IterativeVoter.h"
#include "distributions.h"

using namespace std;

class IterativeGame {
public:
    IterativeGame (int voterNum, IterativeVoter** gameVoters);
    virtual ~IterativeGame();
    virtual int getWinner() const;
    virtual int getWinnerSwitch(IterativeVoter * player, PrefList list) const;
    virtual bool playStage();
    bool hasStageHappened() const;
    virtual string printStage() const;
    virtual string printHistory() const;
    virtual string printGame(resultFormat* rs);
    
    virtual void gameEnd();
    virtual void resetGame();
    virtual double getCandidateRank(int c);
    virtual void setWinnerAndCondercet (vector<PrefList> v);
    virtual void setDistributionType(distributionTypes typeLa);
    
    int getPluralityWinnerFromVotes(vector<PrefList> v);
    int getCondorcetWinnerFromVotes(vector<PrefList> v);
    int getBordaWinnerFromVotes(vector<PrefList> v);
    int getMaximinWinnerFromVotes(vector<PrefList> v);
    int getCopelandWinnerFromVotes(vector<PrefList> v);
    double getPluralityDuvergerGapFromVotes(vector<PrefList> v);
    double getPluralityDuvergerGap2FromVotes(vector<PrefList> v);
    double getPluralityDuvergerGap3FromVotes(vector<PrefList> v);
    double getToFirstTwoFromVotes(vector<PrefList> v);
    
    
     virtual int breakTies(vector<int> winners) const =0;
protected:
    int candidateNumber;
    int voterNumber;
    vector< PrefList> votes;
    IterativeVoter** voters;
    vector<vector<PrefList> > history;
    map<int,int> winners;
    map<vector<PrefList>,int> finalStates;
    map<vector<PrefList>,double> avgStepsToFinal;
    map<vector<PrefList>,double> duvergerGap;
    map<vector<PrefList>,double> duvergerGap2;
    map<vector<PrefList>,double> duvergerGap3;
    int truthtfulWinner;
    int condercetWinner;
    int bordaWinner;
    int pluralityWinner;
    int maximinWinner;
    int copelandWinner;
    double pluralityDuvergerGap;
    double pluralityDuvergerGap2;
    double pluralityDuvergerGap3;
    int noDuverger=0;
    int noDuverger2=0;
    distributionTypes disType;
    luceSpecial luceInfo;
    double toFirstTwo;
    int noCondorcet=0;
    
    virtual string printVotes(vector<PrefList >) const;
    virtual int getWinnerFromVotes(vector<PrefList>) const = 0;
   
};


#endif
