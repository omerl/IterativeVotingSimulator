//
//  defs.cpp
//  RangeEquilibria
//
//  Created by Omer Lev on 23/2/14.
//
//

#include "defs.h"


std::string printRangeType (rangeTypes rT) {
    switch (rT) {
        case basic:
            return "basic";
            break;
        case truthful:
            return "truthful";
            break;
        case lazy:
            return "lazy";
        default:
            break;
    }
    return NULL;
}

std::string printDistributionType(distributionTypes dist) {
    switch (dist) {
        case uniform:
            return "Uniform";
            break;
        case peaked:
            return "Peaked";
            break;
        case curved:
            return "Curved";
            break;
        case urn2:
            return "Urn2";
            break;
        case urn3:
            return "Urn3";
            break;
        case riffle:
            return "Riffle";
            break;
        case luce:
            return "Luce";
            break;
        default:
            break;
    }
    return NULL;
}

std::string printScenarioType (scenarioType sT) {
    switch (sT) {
        case regular:
            return "regular";
            break;
        case scheduler:
            return "schedular";
            break;
            
        default:
            break;
    }
    return NULL;
}

std::string printResults(resultFormat* results) {
    std::ostringstream sStream((std::ostringstream::out));
    
    sStream<<"avgStateNum:\t"<<results->stableStateNumber<<"\t winnerNum:\t"<<results->winnerNumber<<"\t stepNumber:\t"<<results->stepNumber<<"\t winnerRanking:\t"<<results->winnerRanking<<"\t plurality:\t"<<results->pluralityWinner<<"\t Borda:\t"<<results->bordaWinner<<"\t Maximin:\t"<<results->maximinWinner<<"\t Copeland:\t"<<results->copelandWinner<<"\t Condorcet:\t"<<results->condorcetWinner<<"\t noCondorcet:\t"<<results->noCondorcet<<"\t DuvergerGap:\t"<<results->duvergerGap<<"\t DuvergerGap2:\t"<<results->duverger2Gap<<"\t DuvergerGap3:\t"<<results->duverger3Gap<<"\t noDuverger:\t"<<results->noDuverger<<"\t noDuverger2:\t"<<results->noDuverger2<<"\t firstTwo:\t"<<results->firstTwoRatio<<"\t Max winner share:\t"<<results->winnerDifusion<<"\t 2nd Max winner share:\t"<<results->winnerDifusion2<<"\t";
    
    if (results->lucy.luceRank>=0) {
        if (results->lucy.pluralityWinner>0) {
            sStream<<"luce winRank:\t"<<results->lucy.luceRank<<"\tluce plurality:\t"<<results->lucy.pluralityWinner<<"\tluce borda:\t"<<results->lucy.bordaWinner<<"\tluce copeland:\t"<<results->lucy.copelandWinner<<"\tluce maximin:\t"<<results->lucy.maximinWinner<<"\tluce condorcet:\t"<<results->lucy.condorcetWinner<<"\t";
        }
        else {
            sStream<<"peak/curve from median:\t"<<results->lucy.luceRank<<"\t";
        }
    }
    
    if (results->looped>0) {
        sStream<<"loop ratio:\t"<<results->looped<<"\t";
    }
    
    if (results->improvedScore>0) {
        sStream<<"improvedSteps:\t"<<results->improvedScore<<"\t";
    }
    if ((results->extraWinnerDetail).size()>0) {
        sStream<<results->extraWinnerDetail<<"\t";
    }
    sStream<<"\n";
    
    return sStream.str();
}

distributionTypes& operator++(distributionTypes& dt)
{
    int i= (int) dt;
    i++;
    distributionTypes d=(distributionTypes) i;
    return dt=d;
}

distributionTypes operator++(distributionTypes& dt, int)
{
    ++dt;
    return dt;
}