//
//  data.h
//  urbanDataCanvas
//
//  Created by Johan Bichel Lindegaard on 22/02/14.
//
//

#pragma once

#include "ofMain.h"
#include "ofxCsv.h"

using namespace wng;

class MarketData {
public:
    
    ofxCsv csv;
    
    void import() {
        
        // Load a CSV File.
        csv.loadFile(ofToDataPath("urban_data_v2.csv"));
        
        cout << "Print out a specific CSV value" << endl;
        cout << csv.data[0][1] << endl;
        // also you can write...
        //cout << csv.data[0].at(1) << endl;
        
        cout << "Print out the first value" << endl;
        cout << csv.data[0].front() << endl;
        
        cout << "Maximum Size:";
        cout << csv.data[0].max_size() << endl;
        
    }
    
    
    
};