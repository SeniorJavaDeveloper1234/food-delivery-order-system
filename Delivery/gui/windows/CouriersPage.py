

from PyQt5.QtWidgets import QWidget, QVBoxLayout, QPushButton, QHBoxLayout
from widgets.CourierTable import CourierTable
from windows.AddCourierWindow import AddCourierWindow
from windows.EditCourierWindow import EditCourierWindow

class CouriersPage(QWidget):
    def __init__(self, adapter):
        super().__init__()
        self.adapter = adapter

        self.table = CourierTable()
        self.add_btn = QPushButton("Add Courier")
        self.edit_btn = QPushButton("Edit Courier")

        top = QHBoxLayout()
        top.addWidget(self.add_btn)
        top.addWidget(self.edit_btn)
        top.addStretch()

        layout = QVBoxLayout()
        layout.addLayout(top)
        layout.addWidget(self.table)
        self.setLayout(layout)

        self.add_btn.clicked.connect(self.add_courier)
        self.edit_btn.clicked.connect(self.edit_courier)

        self.load_data()

    def load_data(self):
        data = self.adapter.get_couriers()
        self.table.update_data(data)

    def add_courier(self):
        win = AddCourierWindow(self.adapter, self)
        if win.exec_():
            self.load_data()

    def edit_courier(self):
        row = self.table.currentRow()
        if row < 0:
            return

        cid = int(self.table.item(row, 0).text())
        courier = next((c for c in self.adapter.get_couriers() if c.getId() == cid), None)

        win = EditCourierWindow(self.adapter, courier, self)
        if win.exec_():
            self.load_data()
