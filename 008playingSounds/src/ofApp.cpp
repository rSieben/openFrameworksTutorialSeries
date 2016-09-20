#include "ofApp.h"

string game_state;

struct Bullet {
	ofVec2f posicao;
	float velX = 0;
	float velY = 20;
	float radius = 3;
};

struct Enemy {
	ofVec2f posicao;
	float radius = 30;
	float speed = 110;
	int tipo;
	int imagem;
	std::vector<Bullet> aBullet;
};

struct Player {
	ofVec2f posicao;
	float velX, velY;
	float radius = 20;
	float speed = 5;

	int life = 3;

	float updateGunVelX = 0;
	float updateGunVelY = 0;

	bool onScreen = true;
	bool keyLeft, keyRight, keyUp, keyDown;
	std::vector<Bullet> aBullet;
};

struct Object {
	ofVec2f posicao;
	float width;
	float height;
};

struct Level {
	int status; // 0 - nao iniciado , 1 - iniciado , 2 finalizado
	float speed = 100;
	float song;
	ofVec2f posicao;
	ofImage background;
	std::vector<Object> aObject;
	std::vector<Enemy> aEnemy;
};

Player p1;
Bullet bullet;
Object object;

Level level1;
Level level2;
Level level3;
Level levelAtual;

ofSoundPlayer musica;
ofImage background;

void ofApp::setup() {
	
	// inicializa posicao do player
	p1.posicao.x = 400;
	p1.posicao.y = 400;

	level1.status = 0;
	level2.status = 0;
	level3.status = 0;

	game_state = "menu";
	background.loadImage("/imagens/prometheusBoundBranco.jpg");
	musica.load("/sons/SevenNationArmy.mp3");
	musica.play();
	musica.setVolume(0.5);
	musica.setLoop(true);
	musica.setSpeed(1.3);

}

void ofApp::nextLevel() {

	if (level1.status == 0 )
	{
		game_state = "game";
		level1.status = 1;
		
		levelAtual = level1;
		levelAtual.background.loadImage("/imagens/bg1.jpg");
		levelAtual.posicao.x = 0;
		levelAtual.posicao.y = ofGetHeight();

		musica.load("/sons/SystemOfaDown.mp3");
		musica.setSpeed(1);
		musica.play();
	}
	else if (level2.status == 0 && level1.status == 2) {
		game_state == "game";
		level2.status = 1;
		
		levelAtual = level1;
		levelAtual.background.loadImage("/imagens/bg2.jpg");
		levelAtual.posicao.x = 0;
		levelAtual.posicao.y = ofGetHeight();

		musica.load("/sons/SystemOfaDown.mp3");
		musica.setSpeed(1);
		musica.play();
	}
	else if (level3.status == 0 && level2.status == 2) {
		game_state == "game";
		level3.status = 1;
		
		levelAtual = level1;
		levelAtual.background.loadImage("/imagens/bg3.jpg");
		levelAtual.posicao.x = 0;
		levelAtual.posicao.y = ofGetHeight();

		musica.load("/sons/SystemOfaDown.mp3");
		musica.setSpeed(1);
		musica.play();
	}
}

void ofApp::update() {
	if (game_state == "game")
	{
		////////////////////////////////////////////////////
		// atualiza movimentacao
		// de todos (movimentacao do mapa)
		levelAtual.posicao.y += levelAtual.speed*ofGetLastFrameTime();
		p1.posicao.y += levelAtual.speed*ofGetLastFrameTime();
		for (size_t i = 0; i < levelAtual.aEnemy.size(); i++) {
			levelAtual.aEnemy[i].posicao.y += levelAtual.speed*ofGetLastFrameTime();
		}

		// player
		if ((p1.posicao.x + p1.velX) <= ofGetWindowWidth() && (p1.posicao.x + p1.velX >= 0))
			p1.posicao.x += p1.velX;

		if ((p1.posicao.y + p1.velY) >= 0)
			p1.posicao.y += p1.velY;
		////////////////////////////////////////////////////


		////////////////////////////////////////////////////
		// update player velocidade
		// X
		if (p1.keyRight)
			p1.velX = +p1.speed + (ofGetLastFrameTime() * 100);
		else if (p1.keyLeft)
			p1.velX = -p1.speed - (ofGetLastFrameTime() * 100);
		else
			p1.velX = 0;

		// Y
		if (p1.keyDown)
			p1.velY = +p1.speed + (ofGetLastFrameTime() * 100);
		else if (p1.keyUp)
			p1.velY = -p1.speed - (ofGetLastFrameTime() * 100);
		else
			p1.velY = 0;
		////////////////////////////////////////////////////


		////////////////////////////////////////////////////
		// update enemy velocidade


		////////////////////////////////////////////////////

		////////////////////////////////////////////////////
		// update every bullet on game
		for (size_t i = 0; i < p1.aBullet.size(); i++)
		{
			if (p1.aBullet[i].posicao.x == 0 && p1.aBullet[i].posicao.y == 0)
			{
				p1.aBullet[i].posicao.x = p1.posicao.x;
				p1.aBullet[i].posicao.y = p1.posicao.y;
			}
			p1.aBullet[i].posicao.x += p1.aBullet[i].velX + p1.updateGunVelX;
			p1.aBullet[i].posicao.y += (p1.aBullet[i].velY + p1.updateGunVelY)*-1;
		}
		////////////////////////////////////////////////////


		////////////////////////////////////////////////////
		// update every object on level
		for (size_t i = 0; i < levelAtual.aObject.size(); i++) {
			levelAtual.aObject[i].posicao.y += levelAtual.speed;
		}
		////////////////////////////////////////////////////
	}
	else if (game_state == "menu") {
		
	}

}

//--------------------------------------------------------------
void ofApp::draw() {

	if (game_state == "game")
	{

		levelAtual.background.draw(levelAtual.posicao.x, levelAtual.posicao.y, ofGetWidth(), levelAtual.background.getHeight()*-1);

		////////////////////////////////////////////////////
		// desenha player
		ofDrawCircle(p1.posicao.x, p1.posicao.y, p1.radius);
		////////////////////////////////////////////////////

		////////////////////////////////////////////////////
		// desenha inimigos
		for (size_t i = 0; i < levelAtual.aEnemy.size(); i++)
			ofDrawCircle(levelAtual.aEnemy[i].posicao.x, levelAtual.aEnemy[i].posicao.y, levelAtual.aEnemy[i].radius);
		////////////////////////////////////////////////////

		////////////////////////////////////////////////////
		// desenha objetos
		for (size_t i = 0; i < levelAtual.aObject.size(); i++)
			ofRectangle(levelAtual.aObject[i].posicao.x, levelAtual.aObject[i].posicao.y, levelAtual.aObject[i].width, levelAtual.aObject[i].height);
		////////////////////////////////////////////////////

		////////////////////////////////////////////////////
		// desenha bullet
		for (size_t i = 0; i < p1.aBullet.size(); i++)
			ofDrawCircle(p1.aBullet[i].posicao.x, p1.aBullet[i].posicao.y, 5);
		////////////////////////////////////////////////////
	}
	else if (game_state == "menu") {
		background.draw(0, ofGetHeight(), ofGetWidth(), levelAtual.background.getHeight()*-1);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (game_state == "game") {

		////////////////////////////////////////////////////
		// teclas de movimentacao
		if (key == OF_KEY_F1)
			ofSetFullscreen(true);
		if (key == OF_KEY_F2)
			ofSetFullscreen(false);
		////////////////////////////////////////////////////

		////////////////////////////////////////////////////
		// teclas de movimentacao
		if (key == OF_KEY_LEFT || key == 'a')
			p1.keyLeft = true;
		if (key == OF_KEY_RIGHT || key == 'd')
			p1.keyRight = true;
		if (key == OF_KEY_UP || key == 'w')
			p1.keyUp = true;
		if (key == OF_KEY_DOWN || key == 's')
			p1.keyDown = true;
		////////////////////////////////////////////////////

		////////////////////////////////////////////////////
		// atirar
		if (key == GLFW_KEY_SPACE)
			p1.aBullet.push_back(bullet);
		////////////////////////////////////////////////////
	}
	else if (game_state == "menu") {
		if (key)
			nextLevel();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	if (game_state == "game") {

		////////////////////////////////////////////////////
		// teclas de movimentacao
		if (key == OF_KEY_LEFT || key == 'a')
			p1.keyLeft = false;
		if (key == OF_KEY_RIGHT || key == 'd')
			p1.keyRight = false;
		if (key == OF_KEY_UP || key == 'w')
			p1.keyUp = false;
		if (key == OF_KEY_DOWN || key == 's')
			p1.keyDown = false;
		////////////////////////////////////////////////////

	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
