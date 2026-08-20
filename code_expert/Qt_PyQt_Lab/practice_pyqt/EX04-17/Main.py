import sys, os, subprocess
from PyQt5.QtWidgets import *
from PyQt5.QtCore import Qt, pyqtSignal

MAIN_FILE_NAME = 'main_wnd'
DIALOG_FILE_NAME = 'dialog'

subprocess.run([
    sys.executable,
    '-m', 'PyQt5.uic.pyuic',
    '-x', f'{MAIN_FILE_NAME}.ui',
    '-o', f'{MAIN_FILE_NAME}.py'
])
subprocess.run([
    sys.executable,
    '-m', 'PyQt5.uic.pyuic',
    '-x', f'{DIALOG_FILE_NAME}.ui',
    '-o', f'{DIALOG_FILE_NAME}.py'
])
from main_wnd import Ui_MainWindow
from dialog import Ui_Dialog


class Form(QMainWindow, Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.actionHobby.triggered.connect(self.show_dialog)

    def show_dialog(self):
        # main window의 이름 입력값을 dlgForm 생성자로 전달
        dlg = dlgForm(self, name=self.editName.text())

        dlg.accepted.connect(lambda: self.print_info(dlg.getInfo()))
        # open으로 dialog 보이기: accepted 시그널 사용
        # dlg.accepted.connect(lambda: self.print_info(dlg.getInfo()))
        
        # open으로 dialog 보이기: 사용자 시그널 사용
        dlg.submitted.connect(self.print_info)
        dlg.show()
        
        
        # open으로 dialog 보이기
        # dlg.open()
        
        

    def print_info(self, tinfo):
        nick, hobby, gender = tinfo
        self.lblNick.setText(f"닉네임: {nick}")
        self.lblGender.setText(f"성별: {gender}")
        self.lblHobby.setText(f"취미: {', '.join(hobby)}")


class dlgForm(QDialog, Ui_Dialog):
    submitted = pyqtSignal(tuple)
    
    def __init__(self, parent=None, flag=Qt.Dialog, name=None):
        super().__init__(parent, flag)
        self.setupUi(self)
        if name:
            self.editNick.setText(name)

    def func(self,btn):
        r = self.buttonBox.standardButton(btn)
        if r == QDialogButtonBox.Ok:
            print("OK")
            self.accept()
            self.user_signal.emit(self.getInfo())
        
    def getNick(self):
        return self.editNick.text()

    def getHobby(self):
        lst_hobby = []
        if self.chkHobby1.isChecked():
            lst_hobby.append(self.chkHobby1.text())
        if self.chkHobby2.isChecked():
            lst_hobby.append(self.chkHobby2.text())
        if self.chkHobby3.isChecked():
            lst_hobby.append(self.chkHobby3.text())
        return lst_hobby

    def accept(self):
        self.submitted.emit(self.getInfo())
        super().accept()

    def getGender(self):
        if self.rdoMale.isChecked():
            return self.rdoMale.text()
        elif self.rdoFemale.isChecked():
            return self.rdoFemale.text()
        return ''

    def getInfo(self):
        r = self.getNick(), self.getHobby(), self.getGender()
        return r


if __name__ == '__main__':
    app = QApplication(sys.argv)
    w = Form()
    w.show()
    sys.exit(app.exec_())