#pragma once
#include<iostream>
#include<string>
using namespace std;
class worker {
	public:
		virtual void show_info() = 0;
		virtual string get_job_name() = 0;
		int m_worker_id;
		string m_name;
		int m_dept_id;

};