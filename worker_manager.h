#pragma once
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include <fstream>
#include <iostream>
#define  FILENAME "worker.txt"
using namespace std;
class work_manager {
	private:
		int m_worker_num;
		bool m_file_isempty;
		worker ** m_wr_arr_pt;
	public:
		work_manager();
		~work_manager();
		void show_menu();
		void exit_system();
		int  get_worker_num();
		int  get_record_worker_num();
		int  is_exist(int id);
		void init_worker();
		void save_worker();
		void add_worker();
		void show_worker();
		void delete_worker();
		void modify_worker();
		void search_worker();
		void sort_worker();
		void clear_workers();
};
void choice_process(work_manager& wm);
