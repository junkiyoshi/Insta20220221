#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255);
	ofSetCircleResolution(30);

	// 配色デザイン ビビッドレッド P038
	this->color_palette.push_back(ofColor(197, 0, 24));
	this->color_palette.push_back(ofColor(184, 12, 65));
	this->color_palette.push_back(ofColor(206, 97, 110));
	this->color_palette.push_back(ofColor(204, 85, 68));
	this->color_palette.push_back(ofColor(190, 145, 176));
	this->color_palette.push_back(ofColor(215, 130, 63));
	this->color_palette.push_back(ofColor(255, 241, 51));
	this->color_palette.push_back(ofColor(107, 182, 187));

	float span = 40;
	for (float x = span * 1.5; x <= ofGetWidth() - span + 1.5; x += span) {

		for (float y = span * 1.5; y <= ofGetHeight() - span * 1.5; y += span) {

			this->location_list.push_back(glm::vec2(x, y));
			this->deg_list.push_back(0);
			this->param_list.push_back(0);
			int base_color_index = ofRandom(this->color_palette.size());
			int color_index = (base_color_index + (int)ofRandom(this->color_palette.size() - 1)) % this->color_palette.size();
			this->base_color_index_list.push_back(base_color_index);
			this->color_list.push_back(this->color_palette[color_index]);
		}
	}
}


//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	int radius = 14;
	for (int i = 0; i < this->location_list.size(); i++) {

		this->param_list[i] = (this->param_list[i] + 12) % 360;

		if (this->param_list[i] == 0) {

			this->deg_list[i] = ofMap(ofNoise(glm::vec3(this->location_list[i] * 0.001, ofGetFrameNum() * 0.005)), 0, 1, 0, 360);

			int color_index = (this->base_color_index_list[i] + (int)ofRandom(this->color_palette.size() - 1)) % this->color_palette.size();
			this->color_list[i] = this->color_palette[color_index];
		}

		vector<glm::vec2> vertices;
		if (this->param_list[i] > 0 && this->param_list[i] < 180) {

			for (int deg = 0; deg < this->param_list[i]; deg += 1) {

				vertices.push_back(glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD)));
			}

			for (int deg = 360 - this->param_list[i]; deg < 360; deg += 1) {

				vertices.push_back(glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD)));
			}
		}

		if (this->param_list[i] >= 180 && this->param_list[i] < 360) {

			auto tmp_param = this->param_list[i] - 180;
			for (int deg = tmp_param; deg < 180; deg += 1) {

				vertices.push_back(glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD)));
			}

			for (int deg = 180; deg < 360 - tmp_param; deg += 1) {

				vertices.push_back(glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD)));
			}
		}

		ofPushMatrix();
		ofTranslate(this->location_list[i]);
		ofRotate(this->deg_list[i]);

		ofSetColor(this->color_palette[this->base_color_index_list[i]]);
		ofDrawCircle(glm::vec2(), 17);

		ofSetColor(this->color_list[i]);
		ofBeginShape();
		ofVertices(vertices);
		ofEndShape(true);

		ofPopMatrix();
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}