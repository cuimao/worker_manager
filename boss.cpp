#include "boss.h"
boss::boss(int id, string name, int dept_id) {
	this->m_worker_id = id;
	this->m_name = name;
	this->m_dept_id = dept_id;
}
void boss::show_info() {
	cout << "职工编号："  << setw(10)  <<setfill(' ')<<setiosflags(ios::left) << this->m_worker_id
		 << " 职工姓名：" << setw(10) << setfill(' ') << setiosflags(ios::left)<<this->m_name
		 << " 岗位："     << setw(10) << setfill(' ') << setiosflags(ios::left) << this->get_job_name()
		 << " 岗位职责：管理公司" << endl;
}
string boss::get_job_name() {
	return string("老板");
}