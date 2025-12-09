from PyQt5.QtWidgets import QWidget, QVBoxLayout, QPushButton, QHBoxLayout
from widgets.OrderTable import OrderTable
from windows.CreateOrderWindow import CreateOrderWindow
from windows.EditOrderWindow import EditOrderWindow

class OrdersPage(QWidget):
    def __init__(self, adapter):
        super().__init__()
        self.adapter = adapter

        self.table = OrderTable()
        self.refresh_btn = QPushButton("Refresh")
        self.create_btn = QPushButton("Create Order")
        self.edit_btn = QPushButton("Edit Status")

        top = QHBoxLayout()
        top.addWidget(self.refresh_btn)
        top.addWidget(self.create_btn)
        top.addWidget(self.edit_btn)

        layout = QVBoxLayout()
        layout.addLayout(top)
        layout.addWidget(self.table)
        self.setLayout(layout)

        self.refresh_btn.clicked.connect(self.load_data)
        self.create_btn.clicked.connect(self.open_create_window)
        self.edit_btn.clicked.connect(self.edit_order)

        self.load_data()

    def load_data(self):
        data = self.adapter.get_orders()
        self.table.update_data(data)

    def open_create_window(self):
        win = CreateOrderWindow(self.adapter, self)
        win.exec_()
        self.load_data()

    def edit_order(self):
        row = self.table.currentRow()
        if row < 0:
            return

        oid = int(self.table.item(row, 0).text())

        order = None
        for o in self.adapter.get_orders():
            if o.getId() == oid:
                order = o
                break

        win = EditOrderWindow(self.adapter, order, self)
        if win.exec_():
            self.load_data()
