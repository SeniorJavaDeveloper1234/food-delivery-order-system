from PyQt5.QtWidgets import QWidget, QVBoxLayout, QPushButton, QHBoxLayout
from widgets.MenuTable import MenuTable
from windows.AddMenuItemWindow import AddMenuItemWindow
from windows.EditMenuItemWindow import EditMenuItemWindow

class MenuPage(QWidget):
    def __init__(self, adapter):
        super().__init__()
        self.adapter = adapter

        self.table = MenuTable()
        self.refresh_btn = QPushButton("Refresh")
        self.add_btn = QPushButton("Add Item")
        self.edit_btn = QPushButton("Edit Item")

        top = QHBoxLayout()
        top.addWidget(self.refresh_btn)
        top.addWidget(self.add_btn)
        top.addWidget(self.edit_btn)

        layout = QVBoxLayout()
        layout.addLayout(top)
        layout.addWidget(self.table)
        self.setLayout(layout)

        self.refresh_btn.clicked.connect(self.load_data)
        self.add_btn.clicked.connect(self.add_item)
        self.edit_btn.clicked.connect(self.edit_item)

        self.load_data()

    def load_data(self):
        data = self.adapter.get_menu()
        self.table.update_data(data)

    def add_item(self):
        win = AddMenuItemWindow(self.adapter, self)
        if win.exec_():
            self.load_data()

    def edit_item(self):
        row = self.table.currentRow()
        if row < 0:
            return

        mid = int(self.table.item(row, 0).text())
        item = None

        for m in self.adapter.get_menu():
            if m.getId() == mid:
                item = m
                break

        win = EditMenuItemWindow(self.adapter, item, self)
        if win.exec_():
            self.load_data()
