import sys

from PyQt5 import QtCore, QtWidgets, QtGui


class MainWindows(QtWidgets.QWidget):

    def __init__(self):
        super(MainWindows, self).__init__()
        self.setWindowTitle("Qt 绘制图形")
        self.setGeometry(100, 100, 800, 600)

    def paintEvent(self, QPaintEvent):
        painter = QtGui.QPainter(self)
        painter.begin(self)
        painter.setPen(QtCore.Qt.blue)
        # draw
        painter.drawLine(QtCore.QLineF(100, 100, 200, 200))
        painter.end()


if __name__ == '__main__':
    app = QtWidgets.QApplication(sys.argv)
    win = MainWindows()
    win.show()
    sys.exit(app.exec_())
