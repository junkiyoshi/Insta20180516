#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofBackground(239);
	ofSetWindowTitle("Insta");

	ofNoFill();
	ofSetColor(39);
	ofSetLineWidth(2);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(3939);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	for (int x = -1; x < 2; x++) {

		for (int y = -1; y < 2; y++) {

			this->draw_twist_circle(ofPoint(x * 230, y * 230), 20, 100, 10);
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
void ofApp::draw_twist_circle(ofPoint point, int radius_base, int radius_max, int radius_span) {

	float noise_deg_x = ofMap(ofNoise((ofRandom(1000) + ofGetFrameNum()) * 0.01), 0, 1, -180, 180);
	float noise_deg_y = ofMap(ofNoise((ofRandom(1000) + ofGetFrameNum()) * 0.01), 0, 1, -180, 180);
	for (int radius = radius_base; radius <= radius_max; radius += radius_span) {

		ofPushMatrix();
		ofTranslate(point);

		if (radius < radius_max * 0.65) {

			ofRotateX(noise_deg_x * ofMap(radius, radius_base, radius_max * 0.65, 3, 0.8));
			ofRotateY(noise_deg_y * ofMap(radius, radius_base, radius_max * 0.65, 3, 0.8));
		}
		else {

			ofRotateX(noise_deg_x * ofMap(radius, radius_max * 0.65, radius_max, 0.8, 0));
			ofRotateY(noise_deg_y * ofMap(radius, radius_max * 0.65, radius_max, 0.8, 0));
		}

		ofBeginShape();
		for (int deg = 0; deg <= 360; deg++) {

			ofVertex(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
		}
		ofEndShape(true);

		ofPopMatrix();
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}