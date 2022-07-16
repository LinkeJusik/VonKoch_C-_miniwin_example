#include <cmath>
using namespace std;
#include "miniwin.h"
using namespace miniwin;

struct Punto { float x, y; };

Punto intermedio(const Punto& a, const Punto& b, float t){
	Punto p = { a.x * (1-t) + b.x * t, a.y * (1-t) + b.y * t};
	return p;
}

Punto rotar(const Punto& p, const Punto& cen, float da){
	float dx = p.x - cen.x, dy = p.y - cen.y;
	float r = sqrt(dx*dx + dy*dy);
	float a = atan2(dy,dx);
	a -= da;
	Punto q = { cen.x + r * cos(a), cen.y + r * sin(a)};
	return q; 
}

void VonKoch(const Punto& p0, const Punto & p4, int nivel){
	if (nivel==0){
		linea( p0.x, p0.y, p4.x, p4.y );
	}else{
		Punto p[5] = { p0, p0, p0, p0, p4 };
		p[1] = intermedio(p[0], p[4], 1.0/3.0);
		p[3] = intermedio(p[0], p[4], 2.0/3.0);
		p[2] = rotar(p[3], p[1], M_PI / 3.0);
		for (int i=0; i<4; i++){
			VonKoch(p[i], p[i+1], nivel - 1);
		}
	}
}

int main(){
	vredimensiona(1240, 440);
	Punto p0 = { 20, 420}, p4 = { 1220, 420 };
	
	for(int j=0; j<3; j++){
		for(int i=0;i<10;i++){
			borra();
			VonKoch(p0, p4, i);
			refresca();
			espera(400);
		}
	}
	
	vcierra(); 
	return 0;
}
