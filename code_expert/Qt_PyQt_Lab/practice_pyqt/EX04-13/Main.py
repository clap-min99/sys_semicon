import sys ,subprocess

from PyQt5.QtWidgets import QFileDialog, QMainWindow, QApplication
from PyQt5.QtCore import QFileInfo

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

        self.btnGetOpenFile.clicked.connect(self.open_file)
        self.btnGetSaveFile.clicked.connect(self.save_file)
        
    def open_file(self):
        fname, _ = QFileDialog.getOpenFileName(self, "파일 열기", "", "All Files (*)")
        if not fname:
            return  # 취소 시 아무것도 안 함

        # 방법 1: QFileInfo 사용
        finfo = QFileInfo(fname)
        self.lblOpenFileName.setText(finfo.fileName())

        # 방법 2: split 사용 (둘 중 하나만 쓰면 됨, 비교용으로 같이 적어둠)
        # name = fname.split('/')[-1]
        # self.lblOpenFileName.setText(name)

    def save_file(self):
        fname, _ = QFileDialog.getSaveFileName(self, "파일 저장", "", "All Files (*)")
        if not fname:
            return

        finfo = QFileInfo(fname)
        self.lblSaveFileName.setText(finfo.fileName())
        

if __name__ == '__main__':
    app = QApplication(sys.argv)
    w = Form()
    w.show()
    sys.exit(app.exec_())
