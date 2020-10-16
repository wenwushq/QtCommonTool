#include "QtCommonTool.h"
#include <QtWidgets/QApplication>
#include ".\QtSingleApplication\QtSingleApplication"

int main(int argc, char **argv)
{
	QtSingleApplication a("SingleApp", argc, argv);
	if (a.sendMessage("ActiveWindow!"))
		return 0;

	QtCommonTool w;
	w.show();

	a.setActivationWindow(&w);

	return a.exec();
}
