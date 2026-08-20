import sys ,subprocess

from PyQt5.QtWidgets import QMainWindow, QApplication
from PyQt5.QtCore import QTime, QTimer

GUI_FILE_NAME = 'gui'
subprocess.run([
    sys.executable,          
    '-m', 'PyQt5.uic.pyuic', 
    '-x', f'{GUI_FILE_NAME}.ui', 
    '-o', f'{GUI_FILE_NAME}.py'
])
from gui import Ui_MainWindow


class Form(QMainWindow, Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.tick = 0
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.timeTick)
        self.timer.start(1000)

        self.lblRed.setStyleSheet("background-color:red")
        self.lblGreen.setStyleSheet("background-color:black")
        
        timestr = QTime.currentTime().toString("HH:mm:ss")
        self.lcdNumber.display(timestr)        
        
    def timeTick(self):
        self.tick += 1
        timestr = QTime.currentTime().toString("HH:mm:ss")
        self.lcdNumber.display(timestr) 
        
        if self.tick % 2 == 0:
            self.lblRed.setStyleSheet("background-color:red")
            self.lblGreen.setStyleSheet("background-color:black")
        else:
            self.lblRed.setStyleSheet("background-color:black")
            self.lblGreen.setStyleSheet("background-color:green")
        

if __name__ == '__main__':
    app = QApplication(sys.argv)
    w = Form()
    w.show()
    sys.exit(app.exec_())
