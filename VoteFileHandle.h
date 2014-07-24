//
//  VoteFileHandle.h
//  RangeEquilibria
//
//  Created by Omer Lev on 2/3/14.
//
//

#ifndef __RangeEquilibria__VoteFileHandle__
#define __RangeEquilibria__VoteFileHandle__

#include <iostream>
#include "TestScenario.h"

using namespace std;

class VoteFileHandle {
public:
    VoteFileHandle (const char* fileName);
    VoteFileHandle (string fileName);
    ~VoteFileHandle();
    
    string runIt(string directory);
    
protected:
    void handleFile(const char* fileName);
    void handlePrefLibFile (const char* fileName);
    void handleVoterList (ifstream* str);
    void setPrefArrayFromString(string str, int* prefs,map<string,int>* candNames,string prefsDelimiter);
    
    string trim(string s);
    string distString="";
    int candNum=-1;
    scenarioType sType=regular;
    rangeTypes rt=basic;
    voterRType vRType=additive;
    string sHeader="";
    bool falseStart=false;
    double r=-1;
    double k=-1;
    vector<double> rs;
    vector<double> ks;
    vector<pair<double,double> > rks;
    int roundNum=100;
    int maxStep=1000;
    int gameNumber=200;
    int voterNum=-1;
    
    vector<IterativeVoter*> allVoters;
};

#endif /* defined(__RangeEquilibria__VoteFileHandle__) */
