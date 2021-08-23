#pragma once
#include<QString>
#include<QVector>

typedef struct BError{
	//错误名
	QString errorName;
	//错误编号
	int errorNumber;
	//解决方案是否为空
	bool solutionsStatus;
	//解决方案
	QString solutions;
};

class BeanComError {
public:
	BError null;
	BError sendTextError1;
	BError sendTextError2;
public:
	QVector<BError> beanError;
	BeanComError() {
		//设置编号
		null.errorNumber = 0;
		sendTextError1.errorNumber = 1;
		sendTextError2.errorNumber = 2;
		//设置名称
		null.errorName = QString::fromLocal8Bit("错误不存在");
		sendTextError1.errorName = QString::fromLocal8Bit("发送字符串不得为空");
		sendTextError2.errorName = QString::fromLocal8Bit("未连接服务器");
		//加入容器
		beanError.insert(null.errorNumber, null);
		beanError.insert(sendTextError1.errorNumber, sendTextError1);
		beanError.insert(sendTextError2.errorNumber, sendTextError2);
	}
	~BeanComError() {
		
	}
	BError findError(int errorNumber) {
	}
	BError findError(QString errorName) {
	}
};