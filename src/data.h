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

struct DataPoint {
    
    int second;
    string object; //can be Buses,Cars,Trucks,Pedestrians
    string timestamp;
    string station;
    string count;
};

class MarketData {
public:
    
    ofxCsv csv;
    vector<DataPoint> data;
    
    void importDay(string _date="2014-01-20") { // importDay(day)
        
        data.clear();
        
        ofLogNotice("Data", "Loading from CSV ...");
        
        // Load a CSV File.
        csv.loadFile(ofToDataPath("urban_data_v2.csv"));
        
        for(int i=1;i<csv.data.size(); i++) {
            
            // Data looks like this:
            // Timestamp,Station,Object,Count
            // 2014-01-20 00:00:00-08:00,Embarcadero,Buses,0
            
            string timestamp = csv.data[i][0];
            
            string date = ofSplitString(timestamp, " ")[0];
            
            // sort out 1 day
            if(_date == date) {
                
                DataPoint dP;
                
                vector<string> timedata;
                timedata = ofSplitString(ofSplitString(ofSplitString(timestamp, " ")[1],"-")[0],":"); // 00 00 00
            
                // make time one value - second of day 0 to 86400
            
                int hours   = ofToInt(timedata[0]);
                int minutes = ofToInt(timedata[1]);
                int seconds = ofToInt(timedata[2]);
                
                dP.second = (hours*60*60) + (minutes*60) + seconds;
                dP.timestamp = timestamp;
                dP.station = csv.data[i][1];
                dP.object  = csv.data[i][2];
                dP.count   = csv.data[i][3];
                
                data.push_back(dP);
                
            }
        
        }
        
        ofLogNotice("Data",ofToString(data.size()) + " data entries loaded.");
        
    }
    
    
    
};