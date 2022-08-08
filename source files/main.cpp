#include "../header files/ui.h"
#include "../header files/tests.h"
#include <fstream>
//int main() {
    //test_everything();
    /*Repo r, w, q;
    Service s = Service(r, w, q);
    UI ui = UI(s);
    ui.start_ui();
    return 0;
     */

#include <QApplication>
#include <QPushButton>
#include "../header files/gui.h"

    int main(int argc, char *argv[]) {
        QApplication a(argc, argv);

        auto repo = Repo();
        auto wl = Repo();
        auto q = Repo();
        auto service = Service(repo, wl, q);

        GUI gui{service};
        gui.show();
        return QApplication::exec();
    }
