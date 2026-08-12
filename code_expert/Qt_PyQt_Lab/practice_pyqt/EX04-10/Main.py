import sys ,subprocess

from PyQt5.QtWidgets import QMainWindow, QApplication

GUI_FILE_NAME = 'gui'
subprocess.run([
    sys.executable,          
    '-m', 'PyQt5.uic.pyuic', 
    '-x', f'{GUI_FILE_NAME}.ui', 
    '-o', f'{GUI_FILE_NAME}.py'
])
from gui import Ui_MainWindow

class Form(QMainWindow, Ui_MainWindow):
    Class_Variable = 9
 
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.instance_variable = 0

        self.colors = ["red", "green", "blue", "yellow", "pink"]
        self.color_index = 0
 
        self.btnPush.clicked.connect(self.Change_Color)
        self.btnToggle.toggled.connect(self.Toggle_State)
 
        self.Update_State_Label(self.btnToggle.isChecked())
 
 
    def Change_Color(self):
        color = self.colors[self.color_index]
        self.lblColor.setStyleSheet(f"background-color: {color};")
        self.color_index = (self.color_index + 1) % len(self.colors)


    def Toggle_State(self, checked: bool):
        self.btnToggle.setText("ON" if checked else "OFF")
        self.Update_State_Label(checked)
 
 
    def Update_State_Label(self, checked: bool):
        color = "green" if checked else "red"
        self.lblState.setStyleSheet(f"background-color: {color};")

if __name__ == '__main__':
    app = QApplication(sys.argv)
    w = Form()
    w.show()
    sys.exit(app.exec_())
