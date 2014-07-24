//
//  IterativeLazyBestVoter.h
//  RangeEquilibria
//
//  Created by Omer Lev on 31/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef RangeEquilibria_IterativeLazyBestVoter_h
#define RangeEquilibria_IterativeLazyBestVoter_h

#include "IterativeVoter.h"

class IterativeLazyBestVoter: public IterativeVoter {
public:
    IterativeLazyBestVoter (PrefList * list, IterativeGame * game): IterativeVoter(list,game) {}
    IterativeLazyBestVoter (PrefList * list): IterativeVoter(list){}
    
    virtual IterativeVoter* copy() const;


    virtual bool makeMove();
};


#endif
