

from PyQt5.QtWidgets import QWidget, QVBoxLayout, QPushButton, QHBoxLayout, QComboBox, QLineEdit
from widgets.OrderTable import OrderTable
from windows.CreateOrderWindow import CreateOrderWindow
from windows.EditOrderWindow import EditOrderWindow

class OrdersPage(QWidget):
    def __init__(self, adapter):
        super().__init__()
        self.adapter = adapter

        self.table = OrderTable()
        self.create_btn = QPushButton("Create Order")
        self.edit_btn = QPushButton("Edit Status")

        self.sort_box = QComboBox()
        self.sort_box.addItems([
            "Sort by ID",
            "Sort by Client",
            "Sort by Courier",
            "Sort by Total",
            "Sort by Created At"
        ])
        self.sort_box.currentIndexChanged.connect(self.sort_orders)

        self.search_field = QLineEdit()
        self.search_field.setPlaceholderText("Enter ID or Name...")

        self.search_mode = QComboBox()
        self.search_mode.addItems(["Client", "Courier"])

        self.search_btn = QPushButton("Search")
        self.search_btn.clicked.connect(self.do_search)

        top = QHBoxLayout()
        top.addWidget(self.create_btn)
        top.addWidget(self.edit_btn)
        top.addWidget(self.sort_box)
        top.addStretch()

        top.addWidget(self.search_field)
        top.addWidget(self.search_mode)
        top.addWidget(self.search_btn)


        layout = QVBoxLayout()
        layout.addLayout(top)
        layout.addWidget(self.table)
        self.setLayout(layout)

        self.create_btn.clicked.connect(self.open_create_window)
        self.edit_btn.clicked.connect(self.edit_order)

        self.load_data()

    def load_data(self):
        self.orders = self.adapter.get_orders()   
        self.table.update_data(self.orders)

    def sort_orders(self):
        method = None

        if self.sort_box.currentIndex() == 0:
            method = "id"
        elif self.sort_box.currentIndex() == 1:
            method = "client"
        elif self.sort_box.currentIndex() == 2:
            method = "courier"
        elif self.sort_box.currentIndex() == 3:
            method = "total"
        elif self.sort_box.currentIndex() == 4:
            method = "created"

        self.orders = self.adapter.sort_orders(method)
        self.table.update_data(self.orders)

    def open_create_window(self):
        win = CreateOrderWindow(self.adapter, self)
        win.exec_()
        self.load_data()

    def edit_order(self):
        row = self.table.currentRow()
        if row < 0:
            return

        oid = int(self.table.item(row, 0).text())
        order = next((o for o in self.orders if o.getId() == oid), None)

        win = EditOrderWindow(self.adapter, order, self)

        if win.exec_():
            self.load_data()  



    def do_search(self):
        text = self.search_field.text().strip()
        mode = self.search_mode.currentText()

        if text == "":
            self.load_data()
            return

        if text.isdigit():
            if mode == "Client":
                data = self.adapter.get_orders_by_client(int(text))
            else:
                data = self.adapter.get_orders_by_courier(int(text))

            self.table.update_data(data)
            return

        if mode == "Client":
            data = self.adapter.get_orders_by_client_name(text)
        else:
            data = self.adapter.get_orders_by_courier_name(text)

        self.table.update_data(data)
