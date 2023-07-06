#include<string>
#include<iostream>
#include<vector>
using namespace std;
class Path {
private:
	int vertix;
	int distance;
	vector<int> trace;
public:
	Path();
	void concatTrace(int);
	void setVertix(int);
	void setDistance(int);
	void setTrace(int);
	int getVertix();
	double getDistance();
	vector<int> getTrace();
	int getNeighbour();


};
Path::Path() {
	vertix = -1;
	distance = -1;
}
void Path::concatTrace(int t) {
	trace.push_back(t);
}
void Path::setVertix(int v) {
	vertix = v;
}
void Path::setDistance(int d) {
	distance = d;
}
void Path::setTrace(int t) {
	trace.push_back(t);
}
int Path::getVertix() {
	return vertix;
}
double Path::getDistance() {
	return distance;
}
vector<int> Path::getTrace() {
	return trace;
}
int Path::getNeighbour() {
	if (trace.size() >= 2)
		return trace[1];
	else return -1;
}
