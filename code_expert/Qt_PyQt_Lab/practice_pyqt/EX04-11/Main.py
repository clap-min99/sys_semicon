import sys ,subprocess, re

from PyQt5.QtWidgets import QMainWindow, QApplication

GUI_FILE_NAME = 'gui'
subprocess.run([
    sys.executable,          
    '-m', 'PyQt5.uic.pyuic', 
    '-x', f'{GUI_FILE_NAME}.ui', 
    '-o', f'{GUI_FILE_NAME}.py'
])
from gui import Ui_MainWindow

ALLOWED_EXPR = re.compile(r'^[0-9+\-*/.() ]*$')


class Form(QMainWindow, Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.btnGroupDisp.buttonClicked.connect(self.make_string)
        self.btnGroupOp.buttonClicked.connect(self.operate)
        self.expr = ''
        
    def make_string(self, btn):
        self.expr += btn.text()
        self.lblDisp.setText(self.expr)
        print(self.expr)
    
    def operate(self, btn):
        if btn == self.btnBack:
            self.expr = self.expr[:-1]
            self.lblDisp.setText(self.expr)
            
        elif btn == self.btnC:
            self.expr = ''
            self.lblDisp.setText(self.expr)
            
        elif btn == self.btnResult:
            self.calculate()
            
    def calculate(self):
        if not self.expr:
            return
 
        if not ALLOWED_EXPR.match(self.expr):
            self.expr = ''
            self.lblDisp.setText('Error')
            return
 
        try:
            result = eval(self.expr)
            
        except (SyntaxError, ZeroDivisionError):
            self.expr = ''
            self.lblDisp.setText('Error')
            return
        except Exception:
            self.lblDisp.setText('Error Unknown')
            return
    
        
        self.expr = str(result)
        self.lblDisp.setText(self.expr)
            
if __name__ == '__main__':
    app = QApplication(sys.argv)
    w = Form()
    w.show()
    sys.exit(app.exec_())
