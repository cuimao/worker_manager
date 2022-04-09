#pragma once
#include<iostream>
#include<string>
#include<iomanip>
#include "worker.h"
using namespace std;
class manager : public worker {

public:
	manager(int id, string name, int dept_id);
	void show_info();
	string get_job_name();
};