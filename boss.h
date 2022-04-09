#pragma once
#include<iostream>
#include<string>
#include<iomanip>
#include "worker.h"
class boss : public worker {

public:
	boss(int id, string name, int dept_id);
	void show_info();
	string get_job_name();
};