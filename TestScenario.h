//
//  TestScenario.h
//  RangeEquilibria
//
//  Created by Omer Lev on 23/2/14.
//
//

#ifndef __RangeEquilibria__TestScenario__
#define __RangeEquilibria__TestScenario__

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

#include "defs.h"
#include "IterativePluralityRangeVoter.h"
#include "IterativePluralityRangeMultVoter.h"
#include "IterativePluralityScheduledFalseStartGame.h"
#include "IterativePluralityFalseStartGame.h"

using namespace std;

class TestScenario {
public:
    TestScenario (int gRound,int mStep, scenarioType sT):maxStep(mStep),gameRounds(gRound),scenType(sT){};
    
    virtual void setHeader(string head);
    
    virtual void setFilePath(string path);

    virtual void setFalseStart(bool fs);
    
    virtual void setDistributionType(distributionTypes dT);
    
    virtual void setTruePrefs(vector<vector<PrefList> > prefs,voterRType rT, rangeTypes ranT);
    
    virtual void setTypes(voterRType rT, rangeTypes ranT);
    
    virtual void setVoters (vector<vector<IterativeVoter*> > vot);
    
    virtual void setRK(vector<pair<double,double> >);
    
    virtual string go();
    
    
    
    
protected:
    int maxStep;
    int gameRounds;
    scenarioType scenType;
    string scenHeader;
    string filePath;
    
    distributionTypes dType;
    voterRType rType;
    rangeTypes ranType=basic;
    vector<vector<PrefList> > truePrefs;
    vector<vector<IterativeVoter *> > voters;
    vector<pair<double, double> > RKs;
    
    bool falseStart=false;
    bool distGiven=false;
    
    void createVotersFromPrefs(double r, double k);
    void updateVoters(double r, double k);
    string getFileName(double r,double k,int voterNum, int candNum);
    string getStartString(double r,double k,int voterNum, int candNum);
    
    void integrateRS (int gameNumber, resultFormat* master, resultFormat* newGame);
    
    virtual string goRK(double r, double k);
    virtual resultFormat* goScenario(double r, double k, vector<IterativeVoter*> vot);

};
#endif /* defined(__RangeEquilibria__TestScenario__) */
