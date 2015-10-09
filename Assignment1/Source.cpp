#include <stdio.h>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <glut.h>
#include <math.h>
#include <algorithm>

using namespace std;

void Display();

class Point
{
public:
	float x, y, z;
	Point();
	Point(float, float, float);

};
class Vec
{
public:
	float a, b, c, d;
	Vec(float, float, float);
	Vec(float, float, float, float);
	Vec();

private:

};
Point vertex[8];
Point intersectionPoints[6];
Vec faces[6];
Point p0Fin;
Point p1Fin;
Point cuboidA;
Point cuboidB;
float maxX, maxY, maxZ, minX, minY, minZ;
int numPoints;
Point::Point()
{
	x = 0;
	y = 0;
	z = 0;
}

Point::Point(float a, float b, float c)
{
	x = a;
	y = b;
	z = c;
}

Vec::Vec(float x,float y, float z)
{
	a = x;
	b = y;
	c = z;
}

Vec::Vec(float x, float y, float z, float w)
{
	a = x;
	b = y;
	c = z;
	d = w;
}
Vec::Vec()
{
	a = 0;
	b = 0;
	c = 0;
	d = 0;
}
float dotProduct(Vec v, Vec u)
{
	return (v.a * u.a + v.b * u.b + v.c * u.c);
}

float dotProductPoint(Vec v, Point p)
{
	return (v.a * p.x + v.b * p.y + v.c * p.z);
}

Vec crossProduct(Vec v, Vec u)
{
	float a, b, c;
	a = v.a * u.c - v.c * u.b;
	b = v.c * u.a - v.a * u.c;
	c = v.a * u.b - v.b * u.a;
	Vec r(a,b,c);
	//cout << v.a;
	//cout << v.b;
	//cout << v.c;
	return r;
}

Vec planeEquation(Vec v, Vec u, Point p)
{
	Vec n = crossProduct(v, u);
	float d = n.a * p.x + n.b * p.y + n.c * p.z;
	return Vec(n.a, n.b, n.c, d);
}

Point rayPlaneIntersection(Vec pln, Point p0, Point p1)
{
	Vec v(p1.x - p0.x, p1.y - p0.y, p1.z - p0.z);
	Vec n(pln.a, pln.b, pln.c);
	float t = (-(dotProductPoint(n, p0)) + pln.d) / dotProduct(v, n);
	return Point(p0.x + t*v.a, p0.y + t*v.b, p0.z + t*v.c);
}

void cuboidVertex(Point a, Point b)
{
	vertex[0] = Point(a.x, b.y, b.z);
	vertex[1] = Point(a.x, a.y, b.z);
	vertex[2] = Point(b.x, a.y, b.z);
	vertex[3] = Point(b.x, b.y, a.z);
	vertex[4] = Point(b.x, a.y, a.z);
	vertex[5] = Point(a.x, b.y, a.z);
	vertex[6] = Point(a.x, a.y, a.z);
	vertex[7] = Point(b.x, b.y, b.z);
	cout << "Vertex of cuboid: \n";
	cout << "(" << vertex[0].x << "," << vertex[0].y << "," << vertex[0].z << ")\n";
	cout << "(" << vertex[1].x << "," << vertex[1].y << "," << vertex[1].z << ")\n";
	cout << "(" << vertex[2].x << "," << vertex[2].y << "," << vertex[2].z << ")\n";
	cout << "(" << vertex[3].x << "," << vertex[3].y << "," << vertex[3].z << ")\n";
	cout << "(" << vertex[4].x << "," << vertex[4].y << "," << vertex[4].z << ")\n";
	cout << "(" << vertex[5].x << "," << vertex[5].y << "," << vertex[5].z << ")\n";
	cout << "(" << vertex[6].x << "," << vertex[6].y << "," << vertex[6].z << ")\n";
	cout << "(" << vertex[7].x << "," << vertex[7].y << "," << vertex[7].z << ")\n";
}

void cuboidFaces()
{
	Vec u;
	Vec v;
	cout << "6 Plane Equations: \n";

	u.a = vertex[0].x - vertex[7].x;
	u.b = vertex[0].y - vertex[7].y;
	u.c = vertex[0].z - vertex[7].z;
	v.a = vertex[2].x - vertex[7].x;
	v.b = vertex[2].y - vertex[7].y;
	v.c = vertex[2].z - vertex[7].z;
	faces[0] = planeEquation(u, v, vertex[7]);
	cout << "<" << faces[0].a << "," << faces[0].b << "," << faces[0].c << "," << faces[0].d << ">\n";

	u.a = vertex[1].x - vertex[2].x;
	u.b = vertex[1].y - vertex[2].y;
	u.c = vertex[1].z - vertex[2].z;
	v.a = vertex[4].x - vertex[2].x;
	v.b = vertex[4].y - vertex[2].y;
	v.c = vertex[4].z - vertex[2].z;
	faces[1] = planeEquation(u, v, vertex[2]);
	cout << "<" << faces[1].a << "," << faces[1].b << "," << faces[1].c << "," << faces[1].d << ">\n";

	u.a = vertex[4].x - vertex[7].x;
	u.b = vertex[4].y - vertex[7].y;
	u.c = vertex[4].z - vertex[7].z;
	v.a = vertex[3].x - vertex[7].x;
	v.b = vertex[3].y - vertex[7].y;
	v.c = vertex[3].z - vertex[7].z;
	faces[2] = planeEquation(u, v, vertex[7]);
	cout << "<" << faces[2].a << "," << faces[2].b << "," << faces[2].c << "," << faces[2].d << ">\n";

	u.a = vertex[0].x - vertex[7].x;
	u.b = vertex[0].y - vertex[7].y;
	u.c = vertex[0].z - vertex[7].z;
	v.a = vertex[3].x - vertex[7].x;
	v.b = vertex[3].y - vertex[7].y;
	v.c = vertex[3].z - vertex[7].z;
	faces[3] = planeEquation(u, v, vertex[7]);
	cout << "<" << faces[3].a << "," << faces[3].b << "," << faces[3].c << "," << faces[3].d << ">\n";

	u.a = vertex[5].x - vertex[0].x;
	u.b = vertex[5].y - vertex[0].y;
	u.c = vertex[5].z - vertex[0].z;
	v.a = vertex[1].x - vertex[0].x;
	v.b = vertex[1].y - vertex[0].y;
	v.c = vertex[1].z - vertex[0].z;
	faces[4] = planeEquation(u, v, vertex[0]);
	cout << "<" << faces[4].a << "," << faces[4].b << "," << faces[4].c << "," << faces[4].d << ">\n";

	u.a = vertex[1].x - vertex[6].x;
	u.b = vertex[1].y - vertex[6].y;
	u.c = vertex[1].z - vertex[6].z;
	v.a = vertex[4].x - vertex[6].x;
	v.b = vertex[4].y - vertex[6].y;
	v.c = vertex[4].z - vertex[6].z;
	faces[5] = planeEquation(u, v, vertex[6]);
	cout << "<" << faces[5].a << "," << faces[5].b << "," << faces[5].c << "," << faces[5].d << ">\n";

}

void cuboidIntersectionPoints(Point a, Point b)
{
	int j = 0;
	for (int i = 0; i < 6; i++)
	{
		Point p = rayPlaneIntersection(faces[i], a, b);
		if (p.x <= maxX && p.y <= maxY && p.z <= maxZ &&p.x >= minX && p.y >= minY && p.z >= minZ)
		{
			intersectionPoints[j];
			j++;
		}
	}
	numPoints = j;
	cout << "Intersection Points are: \n";
	for (int i = 0; i < numPoints; i++)
	{
		cout << "(" << intersectionPoints[i].x << "," << intersectionPoints[i].y << "," << intersectionPoints[i].z << ")\n";
	}
}

int main(int argc, char** argr)
{
	float x, y, z, x1, y1, z1;
	cout << "Enter x,y and z cordinates of P0 \n";
	cin >> x;
	cin >> y;
	cin >> z;
	p0Fin = Point(x, y, z);
	cout << "Enter x,y and z cordinates of P1 \n";
	cin >> x;
	cin >> y;
	cin >> z;
	p1Fin = Point(x, y, z);
	cout << "Enter x,y and z cordinates of Cuboid's Point 'a' \n";
	cin >> x;
	cin >> y;
	cin >> z;
	cuboidA = Point(x, y, z);
	cout << "Enter x,y and z cordinates of Cuboid's Point 'b' \n";
	cin >> x1;
	cin >> y1;
	cin >> z1;
	maxX = max(x1, x);
	maxY = max(y1, y);
	maxZ = max(z1, z);
	minX = min(x1, x);
	minY = min(y1, y);
	minZ = min(z1, z);
	cuboidB = Point(x1, y1, z1);
	cuboidVertex(cuboidA, cuboidB);
	cuboidFaces();
	cuboidIntersectionPoints(p0Fin, p1Fin);
	
	//-------------------------------------------//
	glutInit(&argc, argr);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Line Cuboid Intersection");
	glutDisplayFunc(Display);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glPointSize(5.0);
	glLineWidth(2.0);
	gluOrtho2D(0.0, 1000.0, 0.0, 600.0);
	glutMainLoop();

	return 0;
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glFlush();
}
