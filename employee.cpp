#include "employee.h"
employee::employee(int id, std::string name, int dept_id) {
	this->m_worker_id = id;
	this->m_name = name;
	this->m_dept_id = dept_id;
}
void employee::show_info() {
	cout << "ְ����ţ�" << setw(10) << setfill(' ') << setiosflags(ios::left) << this->m_worker_id
		<< " ְ��������" << setw(10) << setfill(' ') << setiosflags(ios::left) << this->m_name
		<< " ��λ��" << setw(10) << setfill(' ') << setiosflags(ios::left) << this->get_job_name()
		<< " ��λְ����ɾ�����������" << endl;
}
string employee::get_job_name() {
	return string("��ͨԱ��");
}