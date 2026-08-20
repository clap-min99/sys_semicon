from PyQt5.QtWidgets import QLabel
from PyQt5.QtGui import QPixmap
from PyQt5.QtCore import Qt, QFileInfo

class MyLabel(QLabel):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setAcceptDrops(True)
        self.setScaledContents(True)

    def getImagePath(self, mimeData):
        if not mimeData.hasUrls(): # 드래그된 데이터에 파일이 없음
            return ""
        # 파일경로 획득.. 1개만 드롭
        filepath = mimeData.urls()[0].toLocalFile()
        #확장자 체크
        ext = QFileInfo(filepath).suffix().lower()
        # cpp
        # ext = QFileInfo(filepath).suffix().toLower()
        if ext == 'png' or ext == 'jpg' or ext == 'bmp':
            return filepath
        else:
            return ""

    def dragEnterEvent(self, e):
        if self.getImagePath(e.mimeData()) !="":
            e.accept()
        else:
            e.ignore()
    def dragLeaveEvent(self, e):
        pass
    def dropEvent(self, e):
        filepath = self.getImagePath(e.mimeData())
        if filepath != "":
            pixmap = QPixmap(filepath)
            self.setPixmap(pixmap)
            e.accept()
        