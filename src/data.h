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
#include "ofxTimeline.h"

using namespace wng;

struct Location {
    string name;
    int buses [1440];
    int cars [1440];
    int trucks [1440];
    int pedestrians [1440];
};

class MarketData {
public:
    
    ofxCsv csv;
    
    int locationNum = 4;
    Location locations [4];
        
    ofxTimeline timeline;
    
    int simulationSeconds = 20;
    int realSeconds = 86400; // 1440 minutes
    
    int getRealCurrentMinute() {
        return round( (timeline.getCurrentTime()/simulationSeconds*realSeconds) / 60);
    };
    
    void setup(){
    
        ofxTimeline::removeCocoaMenusFromGlut("AllTracksExample");
        timeline.setup();
        timeline.setLoopType(OF_LOOP_NORMAL);
        timeline.setDurationInSeconds(simulationSeconds);
        
        ofAddListener(timeline.events().bangFired, this, &MarketData::bangFired);

        locations[0].name = "Embarcadero";
        locations[1].name = "Montgomery";
        locations[2].name = "Powell";
        locations[3].name = "Civic Center";
    
    };
    
    void update(){
        
    };
    
    void draw(){
        
        ofSetColor(0);
        timeline.draw();
        
        ofPushMatrix();
        ofTranslate(10,20);
        
        ofDrawBitmapString("Day: " + date + ". Minute of day: " + ofToString(getRealCurrentMinute()), 10,400);
        
        for(int l=0;l<locationNum;l++) {
            
            ofPushMatrix();
            
            ofTranslate(20,100*l);
            ofSetColor(0);
            ofDrawBitmapString(locations[l].name, 0,0);
            
            ofSetColor(0);
            ofCircle(0, 20,   locations[l].cars[getRealCurrentMinute()]*10);
            ofSetColor(255,20,20);
            ofCircle(100, 20, locations[l].buses[getRealCurrentMinute()]*10);
            ofSetColor(20,255,20);
            ofCircle(200, 20, locations[l].pedestrians[getRealCurrentMinute()]*10);
            ofSetColor(20,20,255);
            ofCircle(300, 20, locations[l].trucks[getRealCurrentMinute()]*10);
            
            ofPopMatrix();
            
            
        }
        
        ofPopMatrix();
        
        
    };
    
    void importDay(string _date="2014-01-20") { // importDay(day)
        
        ofLogNotice("Data", "Loading from CSV ...");
        
        // Load a CSV File.
        csv.loadFile(ofToDataPath("urban_data_v2.csv"));
        
        for(int i=1;i<csv.data.size(); i++) {
            
            // Data looks like this:
            // Timestamp,Station,Object,Count
            // 2014-01-20 00:00:00-08:00,Embarcadero,Buses,0
            
            string timestamp = csv.data[i][0];
            date = ofSplitString(timestamp, " ")[0];
            
            // sort out 1 day
            if(_date == date) {
                
                vector<string> timedata;
                timedata = ofSplitString(ofSplitString(ofSplitString(timestamp, " ")[1],"-")[0],":"); // 00 00 00
            
                // make time one value - minute of day 0 to 1440
            
                int hours   = ofToInt(timedata[0]);
                int minutes = ofToInt(timedata[1]);
                int seconds = ofToInt(timedata[2]);
                
                int minute = (hours*60) + minutes;
                
                string station = csv.data[i][1];
                string object  = csv.data[i][2];
                int count   = ofToInt(csv.data[i][3]);
                
                int stationId;
                
                for(int l=0;l<locationNum;l++) {
                    if(locations[l].name == station) {
                        if(object == "Buses") {
                            locations[l].buses[minute] = count;
                        } else if (object == "Pedestrians") {
                            locations[l].pedestrians[minute] = count;
                        } else if (object == "Trucks") {
                            locations[l].trucks[minute] = count;
                        } else if (object == "Cars") {
                            locations[l].cars[minute] = count;
                        }
                    }
                }
                
            }
        
        }
        
        ofLogNotice("Data", "loaded.");
        
        
    }
    
    //--------------------------------------------------------------
    void bangFired(ofxTLBangEventArgs& args){
        cout << "bang fired!" << args.flag << endl;
    };
    
    string getDate() {
        return date;
    }
    
private:
    string date;
    
    
};