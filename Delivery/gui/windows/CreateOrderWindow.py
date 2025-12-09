from PyQt5.QtWidgets import (
    QDialog, QVBoxLayout, QHBoxLayout, QLabel, QPushButton,
    QComboBox, QSpinBox, QListWidget
)

class CreateOrderWindow(QDialog):
    def __init__(self, adapter, parent=None):
        super().__init__(parent)
        self.adapter = adapter
        self.cart = []

        self.setWindowTitle("Create Order")
        self.setMinimumWidth(400)

        self.client_box = QComboBox()
        self.courier_box = QComboBox()
        self.menu_box = QComboBox()
        self.qty_box = QSpinBox()
        self.qty_box.setRange(1, 50)

        self.cart_list = QListWidget()

        self.add_btn = QPushButton("Add to Order")
        self.create_btn = QPushButton("Create")
        self.cancel_btn = QPushButton("Cancel")

        form = QVBoxLayout()
        form.addWidget(QLabel("Client"))
        form.addWidget(self.client_box)
        form.addWidget(QLabel("Courier"))
        form.addWidget(self.courier_box)
        form.addWidget(QLabel("Menu Item"))
        form.addWidget(self.menu_box)
        form.addWidget(QLabel("Quantity"))
        form.addWidget(self.qty_box)
        form.addWidget(self.add_btn)
        form.addWidget(QLabel("Items"))
        form.addWidget(self.cart_list)

        bottom = QHBoxLayout()
        bottom.addWidget(self.create_btn)
        bottom.addWidget(self.cancel_btn)

        layout = QVBoxLayout()
        layout.addLayout(form)
        layout.addLayout(bottom)
        self.setLayout(layout)

        self.load_data()

        self.add_btn.clicked.connect(self.add_item)
        self.create_btn.clicked.connect(self.finish)
        self.cancel_btn.clicked.connect(self.reject)

    def load_data(self):
        self.clients = self.adapter.get_clients()
        self.couriers = self.adapter.get_couriers()
        self.menu = self.adapter.get_menu()

        self.client_box.clear()
        for c in self.clients:
            self.client_box.addItem(f"{c.getId()} — {c.getFirstName()} {c.getLastName()}", c.getId())

        self.courier_box.clear()
        for c in self.couriers:
            if c.isAvailable():
                self.courier_box.addItem(f"{c.getId()} — {c.getFirstName()} {c.getLastName()}", c.getId())

        self.menu_box.clear()
        for m in self.menu:
            self.menu_box.addItem(f"{m.getId()} — {m.getName()} ({m.getPrice()})", m.getId())

    def add_item(self):
        menu_id = self.menu_box.currentData()
        qty = self.qty_box.value()

        for m in self.menu:
            if m.getId() == menu_id:
                self.cart.append((menu_id, m.getName(), m.getPrice(), qty))
                self.cart_list.addItem(f"{m.getName()} x{qty} — {m.getPrice() * qty}")
                break

    def finish(self):
        client_id = self.client_box.currentData()
        courier_id = self.courier_box.currentData()

        items = []
        for item in self.cart:
            menu_id, name, price, qty = item
            items.append(self.adapter.create_order_item(menu_id, name, price, qty))

        if not items:
            self.reject()
            return

        self.adapter.create_order_with_items(client_id, items)
        self.accept()
