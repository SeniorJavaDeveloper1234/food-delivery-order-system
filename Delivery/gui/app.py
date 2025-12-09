import sys
from PyQt5.QtWidgets import QApplication
from windows.MainWindow import MainWindow

class App:
    def __init__(self):
        self.app = QApplication(sys.argv)
        self.window = MainWindow()

    def run(self):
        self.window.show()
        sys.exit(self.app.exec_())
