#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include <regex>
#include <algorithm>

using namespace std;

void pridedameISarasa(const string& zodis, map<string, vector<int>>& sarasas, int eilutesNumeris);
bool ArAtsidaro(const string& failoPasirinkimas);
void rasymas(map<string, vector<int>>& sarasas, const vector<string>& urls);
void failoSkaitymas(const string& failoPasirinkimas, map<string, vector<int>>& sarasas, vector<string>& urls);
string sutvarkomeZodi(const string& zodis);
bool TikrinameArUrl(const string& zodis);
