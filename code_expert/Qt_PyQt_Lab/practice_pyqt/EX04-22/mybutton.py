from PyQt5.QtWidgets import QPushButton

class myButton(QPushButton):
    def __init__(self,parent = None):
        super().__init__(parent)
        self.cnt = 0
        self.setStyleSheet("background-color:yellow")
        
    def mousePressEvent(self, e):
        self.setStyleSheet("background-color:red")
        self.cnt += 1
        return super().mousePressEvent(e)
    
    def mouseReleaseEvent(self, e):
        self.setStyleSheet("background-color:green")
        return super().mouseReleaseEvent(e)
    
    def get_count(self):
        
        return self.cnt