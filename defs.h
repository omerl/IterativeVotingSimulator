//
//  defs.h
//  RangeEquilibria
//
//  Created by Omer Lev on 28/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef RangeEquilibria_defs_h
#define RangeEquilibria_defs_h

#include <string>
#include <sstream>

//const int candidateNumber=3;
//const int voterNumber=10;
//const int maxStep=1000;
//const int gameNumber=200;
//const int gameRounds=100;
//const char* voterFileName="voters.txt";

class illegalPreferenceList{};
enum rangeTypes {basic,truthful,lazy};
enum distributionTypes {uniform,peaked,curved,urn2,urn3,riffle,luce, distFirst=uniform,distLast=luce};
enum scenarioType {regular, scheduler};
enum voterRType {additive,mult};
//enum distributionTypes {peaked,curved,luce,uniform,urn2,urn3,riffle, distFirst=peaked,distLast=luce};


struct luceSpecial {
    double pluralityWinner=0;
    double bordaWinner=0;
    double maximinWinner=0;
    double copelandWinner=0;
    double condorcetWinner=-1;
    double luceRank=-1;
};

struct resultFormat {
    double stableStateNumber=0;
    double winnerNumber=0;
    double stepNumber=0;
    double winnerRanking=0;
    double pluralityWinner=0;
    double bordaWinner=0;
    double maximinWinner=0;
    double copelandWinner=0;
    double condorcetWinner=-1;
    double duvergerGap=0;
    double duverger2Gap=0;
    double duverger3Gap=0;
    double noDuverger=0;
    double noDuverger2=0;
    luceSpecial lucy;
    std::string description;
    double looped=0;
    double improvedScore=0;
    double firstTwoRatio=0;
    double noCondorcet=0;
    double winnerDifusion=0;
    double winnerDifusion2=0;
    std::string extraWinnerDetail;
    /*
     vector<double> duvergerMedian;
     vector<double> duverger2Median;
     vector<double> duverger3Median;
     */
};

std::string printRangeType (rangeTypes rT);
std::string printDistributionType(distributionTypes dist);
std::string printScenarioType (scenarioType sT);

std::string printResults (resultFormat* rs);
distributionTypes& operator++(distributionTypes& dt);
distributionTypes operator++(distributionTypes& dt, int);

#endif
