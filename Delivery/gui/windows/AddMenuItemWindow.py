from PyQt5.QtWidgets import (
    QDialog, QVBoxLayout, QHBoxLayout, QLabel,
    QLineEdit, QPushButton
)

class AddMenuItemWindow(QDialog):
    def __init__(self, adapter, parent=None):
        super().__init__(parent)
        self.adapter = adapter

        self.setWindowTitle("Add Menu Item")
        self.setMinimumWidth(350)

        self.id_field = QLineEdit()
        self.name_field = QLineEdit()
        self.desc_field = QLineEdit()
        self.price_field = QLineEdit()

        save_btn = QPushButton("Save")
        cancel_btn = QPushButton("Cancel")

        layout = QVBoxLayout()
        layout.addWidget(QLabel("ID"))
        layout.addWidget(self.id_field)
        layout.addWidget(QLabel("Name"))
        layout.addWidget(self.name_field)
        layout.addWidget(QLabel("Description"))
        layout.addWidget(self.desc_field)
        layout.addWidget(QLabel("Price"))
        layout.addWidget(self.price_field)

        row = QHBoxLayout()
        row.addWidget(save_btn)
        row.addWidget(cancel_btn)

        layout.addLayout(row)
        self.setLayout(layout)

        save_btn.clicked.connect(self.save)
        cancel_btn.clicked.connect(self.reject)

    def save(self):
        mid = int(self.id_field.text())
        name = self.name_field.text()
        desc = self.desc_field.text()
        price = float(self.price_field.text())

        self.adapter.add_menu_item(mid, name, desc, price)
        self.accept()
