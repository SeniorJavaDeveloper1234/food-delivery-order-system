from PyQt5.QtWidgets import (
    QDialog, QVBoxLayout, QHBoxLayout, QLabel,
    QLineEdit, QPushButton, QMessageBox
)

class AddMenuItemWindow(QDialog):
    def __init__(self, adapter, parent=None):
        super().__init__(parent)
        self.adapter = adapter

        self.setWindowTitle("Add Menu Item")
        self.setMinimumWidth(350)

        self.name_field = QLineEdit()
        self.desc_field = QLineEdit()
        self.price_field = QLineEdit()

        save_btn = QPushButton("Save")
        cancel_btn = QPushButton("Cancel")

        layout = QVBoxLayout()
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

    def show_error(self, text):
        QMessageBox.critical(self, "Error", text)

    def save(self):
        name = self.name_field.text().strip()
        desc = self.desc_field.text().strip()
        price_text = self.price_field.text().strip()

        if not name or not desc or not price_text:
            self.show_error("All fields must be filled.")
            return

        try:
            price = float(price_text)
        except ValueError:
            self.show_error("Price must be a number.")
            return

        if price <= 0:
            self.show_error("Price must be greater than 0.")
            return

        self.adapter.add_menu_item(name, desc, price)

        QMessageBox.information(self, "Success", "Menu item added successfully!")
        self.accept()
