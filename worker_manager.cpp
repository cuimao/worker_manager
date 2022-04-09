
#include "worker_manager.h"
#include <iostream>
using namespace std;
int main()
{
	work_manager wm;
	choice_process(wm);
	system("pause");
	return 0;
}
void choice_process(work_manager& wm ) {
	int choice = 0;	
	while (true){
		//展示菜单
		wm.show_menu();
		cout << "请输入您的选择:";
		cin >> choice;
		switch (choice){
			case 0: //退出系统
				wm.exit_system();
				break;
			case 1: //添加职工
				wm.add_worker();
				break;
			case 2: //显示职工
				wm.show_worker();
				break;
			case 3: //删除职工
				wm.delete_worker();
				break;
			case 4: //修改职工
				wm.modify_worker();
				break;
			case 5: //查找职工
				wm.search_worker();
				break;
			case 6: //排序职工
				wm.sort_worker();
				break;
			case 7: //清空文件
				break;
			default:
				break;
		}
	}
}
work_manager::work_manager() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	if (!ifs.is_open()) {
		this->m_worker_num = 0;
		this->m_wr_arr_pt = NULL;
		this->m_file_isempty = true;
		ifs.close();
		return;
	}
	char h;
	ifs >> h;
	if (ifs.eof()) {
		std::cout << "empty" << endl;
		this->m_worker_num = 0;
		this->m_wr_arr_pt = NULL;
		this->m_file_isempty = true;
		ifs.close();
		return;
	}
	ifs.close();
	this->init_worker();
}
work_manager::~work_manager() {
	if (this->m_wr_arr_pt != NULL) {
		delete[] this->m_wr_arr_pt;
	}
}
void work_manager::show_menu() {
	cout << "********************************************" << endl;
	cout << "*********   欢迎使用职工管理系统！ *********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职职工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}
int  work_manager::get_worker_num() {
	return this->m_worker_num;
}
int  work_manager::get_record_worker_num() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dept_id;
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dept_id)
	{
		num++;
	}
	ifs.close();
	return num;	
}
void work_manager::init_worker() {
	ifstream ifs;
	this->m_worker_num = this->get_record_worker_num();
	if (this->m_worker_num) {
		worker* wr_pt;
		ifs.open(FILENAME, ios::in);
		int id;
		string name;
		int dept_id;
		int num = 0;
		this->m_wr_arr_pt = new worker * [this->m_worker_num];
		while (ifs >> id && ifs >> name && ifs >> dept_id)
		{
			if (dept_id == 1) {
				wr_pt = new employee(id, name, dept_id);
			}
			else if (dept_id == 2) {
				wr_pt = new manager(id, name, dept_id);
			}
			else {
				wr_pt = new boss(id, name, dept_id);
			}
			if (num>0) {
				if (is_exist(id)) {
					continue;
				}
			}			
			this->m_wr_arr_pt[num] = wr_pt;
			num++;
			this->m_worker_num = num;
		}
	}
	else {
		this->m_worker_num = 0;
		this->m_wr_arr_pt = NULL;
		this->m_file_isempty = true;
	}
	ifs.close();
}
int  work_manager::is_exist(int id) {
	int exist=0;
	for (int i = 0; i < this->m_worker_num; i++) {
		if (this->m_wr_arr_pt[i]->m_worker_id == id) {
			exist = 1;
			break;
		}
	}
	return exist;
}
void work_manager::add_worker() {
	cout << "输入增加员工的数量：" << endl;
	int add_num = 0;
	int origin_num = 0;
	cin >> add_num;
	if (add_num > 0) {
		origin_num = this->m_worker_num;
		int new_size = add_num + origin_num;
		worker** new_space = new worker * [new_size];
		if (this->m_wr_arr_pt != NULL) {
			for (int i = 0; i < this->m_worker_num; i++ ) {
				new_space[i] = this->m_wr_arr_pt[i];
			}
		}
		for (int i = 0; i < add_num ; i++) {
			int id;
			string name;
			int sel;
			cout << "请输入第 " << i + 1 << " 个新职工编号：";
			cin >> id;
			if (is_exist(id)) {
				cout << "此员工编号已被使用,请检查后，重新输入" << endl;
				i--;
				continue;
			}
			cout << "请输入第 " << i + 1 << " 个新职工姓名：";
			cin >> name;
			cout << "请选择该职工的岗位："<< endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> sel;
			worker* worker_pt = NULL;
			switch (sel) {
			case 1:
				worker_pt = new employee(id, name, 1);
				break;
			case 2:
				worker_pt = new manager(id, name, 2);
				break;
			case 3:
				worker_pt = new boss(id, name, 3);
				break;
			default:
				break;
			}
			new_space[origin_num + i] = worker_pt;
			//delete[] this->m_wr_arr_pt;//bug???????
			this->m_worker_num++;
			this->m_wr_arr_pt = new_space;			
			this->m_file_isempty = false;
			this->show_worker();
		}
		
		cout << "成功添加" << add_num << "名新职工！" << endl;
		this->save_worker();
	}
	else {
		cout << "输入有误" << endl;
	}	
	system("pause");
	system("cls");
}
void work_manager::show_worker() {
	if (this->m_file_isempty == true) {
		cout << "员工数量为0" << endl;
	}
	else {
		if (this->m_worker_num > 0) {
			for (int i = 0; i < this->m_worker_num; i++) {
				this->m_wr_arr_pt[i]->show_info();
			}
			cout  << endl;
		}
		else {
			cout << "员工数量为0" << endl;
		}
	}
}
void work_manager::delete_worker() {
	int id=0;
	int id_index=0;
	if (this->m_file_isempty == true) {
		cout << "员工数量为0,无法删除" << endl;
	}
	else {
		cout << "请输入想要删除的员工编号：" << endl;
		cin >> id;
		if (is_exist(id)) {
			for (int i = 0; i < this->m_worker_num ; i++) {
				if (m_wr_arr_pt[i]->m_worker_id == id) {
					id_index = i;
					break;// TODO
				}
			}
			
			for (int i = id_index; i < this->m_worker_num - 1; i++) {
				this->m_wr_arr_pt[i] = this->m_wr_arr_pt[i + 1];						
			}
			this->m_worker_num--;
			this->save_worker();			
		}
		else {
			cout << "找不到此员工，删除失败" << endl;
		}
	}
}
void work_manager::modify_worker() {
	int id;
	int sel;
	cout << "请输入要修改员工编号:" << endl;
	cin >> id;
	for (int i = 0; i < this->m_worker_num; i++) {
		if (this->m_wr_arr_pt[i]->m_worker_id == id) {
			cout << "此员工的信息如下:" << endl;
			this->m_wr_arr_pt[i]->show_info();
			cout << "将此员工的职位调整为:" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> sel;
			worker* worker_pt = NULL;
			switch (sel) {
			case 1:
				worker_pt = new employee(id, m_wr_arr_pt[i]->m_name, 1);
				break;
			case 2:
				worker_pt = new manager(id, m_wr_arr_pt[i]->m_name, 2);
				break;
			case 3:
				worker_pt = new boss(id, m_wr_arr_pt[i]->m_name, 3);
				break;
			default:
				break;
			}
			m_wr_arr_pt[i]=worker_pt;
			return;
		}
	}
	cout << "没有编号为" << id << "的员工" << endl;
}
void work_manager::search_worker() {
	int id;
	if (this->m_worker_num<=0) {
		cout << "没有员工，请先添加员工" << endl;
		return;
	}
	cout << "请输入要查找的员工编号:";
	cin >> id;
	for (int i = 0; i < this->m_worker_num; i++) {
		if (this->m_wr_arr_pt[i]->m_worker_id == id) {
			this->m_wr_arr_pt[i]->show_info();
			return;
		}
	}
	cout << "没有编号为" << id << "的员工" << endl;
}
void work_manager::sort_worker() {
	int sort_sel;	
	if (this->m_worker_num <= 0) {
		cout << "没有员工，请先添加员工" << endl;
		return;
	}
	//cout << "请输入要排序的方式:\n"
	 cout<< "按工号升序：0\n"
		 << "按工号降序：1\n"
		 << "按职位排序：2"
		 << endl;
		 cout << "请输入要排序的方式:";
	cin >> sort_sel;
	for (int i = 0; i < this->m_worker_num; i++) {
		for (int j=i+1;j< this->m_worker_num;j++){
			if (sort_sel == 0) {
				if (this->m_wr_arr_pt[j]->m_worker_id <= this->m_wr_arr_pt[i]->m_worker_id) {
					worker* worker_pt= m_wr_arr_pt[j];
					m_wr_arr_pt[j] = m_wr_arr_pt[i];
					m_wr_arr_pt[i] = worker_pt;
				}
			}
			else if(sort_sel==1) {
				if (this->m_wr_arr_pt[j]->m_worker_id >= this->m_wr_arr_pt[i]->m_worker_id) {
					worker* worker_pt= m_wr_arr_pt[j];
					m_wr_arr_pt[j] = m_wr_arr_pt[i];
					m_wr_arr_pt[i] = worker_pt;
				}
			}
			else {
				if (this->m_wr_arr_pt[j]->m_dept_id > this->m_wr_arr_pt[i]->m_dept_id) {
					worker* worker_pt = m_wr_arr_pt[j];
					m_wr_arr_pt[j] = m_wr_arr_pt[i];
					m_wr_arr_pt[i] = worker_pt;
				}
			}
		}
	}
	this->show_worker();
	this->save_worker();
}
void work_manager::save_worker() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (int i = 0; i < this->m_worker_num; i++) {
		ofs << m_wr_arr_pt[i]->m_worker_id << "       "
			<< m_wr_arr_pt[i]->m_name << "        "
			<< m_wr_arr_pt[i]->m_dept_id << "        " << endl;
	}
	ofs.close();
}
void work_manager::exit_system() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(1);
}